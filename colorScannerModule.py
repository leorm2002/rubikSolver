import imutils
import cv2
import numpy as np
import time
 
def replaceColorWithFaces(colors,colorDict,letterList):
	""" Funzione che dato un elenco di colori e un dizionario lettera faccia:colore sostituisce i colori con le lettere """
	for i in range(len(colors)):
		for letter in letterList:
			if colors[i] == colorDict[letter]:
				colors[i] = letter
	return colors

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

def getFaceColorsList(cap):
	""" Funzione che fa 20 scatti al cubo e restituisce una lista di liste contenente i colori di ogni cubo """
	lista = [[],[],[],[],[],[],[],[],[]] #lista di liste ogni lista contiene 20 scansioni
	for i in range(20):
		_,frame  = cap.read() 
		frame =imutils.rotate(frame,180)
		frame = crop(frame)  #Crop frame a quadrato
		colors = scanFrame(frame)
		for i in range(0,9,1):
			lista[i].append(colors[i])
	return lista

def scanFrame(frame):
	lista  = []
	lato = frame.shape[0]//5

	for x in range(1,4,1):
		for y in range(1,4,1):
			X = int(x*lato+lato/2)
			Y =int(y*lato+lato/2)
			bgr = frame[X,Y]
			color = bgrToColor(bgr)		
			lista.append(color)
	return(lista)
	
def most_frequent(lista): 
	""" Funzione che restituisce lelemrneto più ricorrente in una lista """
	counter = 0
	color= lista[0] 
	
	for i in lista: 
		curr_frequency = lista.count(i) 
		if(curr_frequency> counter): 
			counter = curr_frequency 
			color = i 

	if(color == "not found"):
		list2 = []

		for i in lista:
			if(i != "not found"):
				list2.append(i)

		if(len(list2)==0):
			return("ERROR")
		else:
			return(most_frequent(list2))
	return color 

def bgrToColor(bgr):
	""" Funzione che dato un valore  bgr restituisce il colore"""
	bgr = np.uint8([[[bgr[0],bgr[1],bgr[2]]]])
	hsv = (cv2.cvtColor(bgr,cv2.COLOR_BGR2HSV))[0][0][0]
	


	if(((hsv>90)&(hsv<111))):
		return "blu"
	elif(((hsv>4)&(hsv<15))):
		return "arancione"
	elif(((hsv>160)&(hsv<190)) | (hsv<3)):
		return "rosso"
	elif(((hsv>50)&(hsv<70))):
		return "verde"
	elif(((hsv>25)&(hsv<35))):
		return "giallo"
	elif(((hsv>10)&(hsv<25))):
		return "bianco"
	else:
		return "not found"

def scanFaccia(cap): 
	
	""" Funzione che esegue scansione faccia """
	good = False #se la lista è buona
	while(not good):
		i = 1
		elencoColori=[]
		lista = getFaceColorsList(cap)
		for l in lista:
			c = most_frequent(l)
			if c == "ERROR":
				break
			elencoColori.append(c)
			if(i==9):
				good = True
			i+=1
	for colore in elencoColori:
		print(colore)
	return elencoColori
	

