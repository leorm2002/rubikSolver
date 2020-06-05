import imutils
import os
import cv2
import numpy as np
import kociemba
import time
import colorScannerModule
import serial
import serial.tools.list_ports as port_list

ser = serial.Serial()
def crop(f):
	""" Function that crop image to make it square """
	h, w = f.shape[:2]  #get original dimension of image

	#cropping it to make it square
	if h>= w:
		f = f[0:w,0:w]
	else:
		f = f[0:h,0:h]
	return f

def drawgrid(f):
	""" Funzione che disegna una griglia quadrata sull'immagine data """
	n = 5
	h, w = f.shape[:2]
	sz = h // n 
	border = 1 * sz
	for y in range(border, h - border, sz):
		for x in range(border, w - border, sz):
			cv2.rectangle(f, (x, y), (x + sz, y + sz), (0, 0, 0), 1)  # plot small squares in black and white
			cv2.rectangle(f, (x - 1, y - 1), (x + 1 + sz, y + 1 + sz), (255, 255, 255), 1)
	return f

def scanFaces(cap):
	# Ordine scansione Top, right, front, down, left, back
	faceCenterColor = []
	ordine =  ["U","R","F","D","L","B"]
	comandi = ["up","right","front","down","left","bottom"]
	colors = [] #array con tutti i colori
	numeroFaccia = 0 # numero faccia scansionata corrente
	print("Mostra faccia "+ ordine[numeroFaccia]+" e premi invio")
	while True:
		_,frame  = cap.read() #Aquisizione frame corrente
		frame = imutils.rotate(frame,180)#rotazione immagine
		frame = crop(frame)  #Crop frame a quadrato
		cv2.imshow("Frame",drawgrid(frame)) #mostro immagine
		key = cv2.waitKey(1)
		if key == 27:
			break
		if key == 13: #se premuto invio
			waitUntil("ready")
			ser.write(comandi[numeroFaccia])
			waitUntil("done")
			msg = colorScannerModule.scanFaccia(cap)
			ser.write("done")
			for c in msg:
				colors.append(c)
			faceCenterColor.append(msg[4])	#aggiungo la faccia centrale nell'elnco dei colori centrali per sapere poi i colori delle varie facce
			print(msg)
			

			if(numeroFaccia == 5):
				break
			numeroFaccia +=1
			#gira faccia
			print("Mostra faccia "+ ordine[numeroFaccia]+" e premi invio")
		
	#conversione da colore a posizione colore della faccia secondo cube string notation
	csn = "" #elemento in cube string notation da returnare
	for color in colors:
		for i in range(len(ordine)):
			if color == faceCenterColor[i]:
				csn += ordine[i]

	return(csn)

def main():
	#ports = list(port_list.comports())
	#for p in ports:
	#	print(p)
	#ser.baudrate = 9600
	#porta = input("Inserisci porta: ")
	#ser.port = porta
	#ser.open()
	cap = cv2.VideoCapture("http://192.168.1.252:8080/video") #inizialiazzazione webcam
	csn = scanFaces(cap) #scansione faccia, return cube notation
	moves_in_string = kociemba.solve(csn) #calcolo e stamp soluzione stampa
	list_of_moves = movesSplit(moves_in_string)
	for move in list_of_moves:
		ser.write(move)
		waitUntil("ready")
	print("Risolto")

def movesSplit(moves):
	print(moves)
	movesExtend =  []
	for i in range(len(moves)):
		try:
			if(moves[i][1]=="2"):
				movesExtend.append(moves[i][0])
				movesExtend.append(moves[i][0])
				
			else:
				movesExtend.append(moves[i])
		except:
			pass
	return (movesExtend)
def waitUntil(parola):
	while True:
		recieved = (ser.readline().decode()).rstrip()
		if recieved == parola:
			return
		

if __name__ == "__main__":
	main()