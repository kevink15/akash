import json

with open('input.json') as my_file:
	data = json.load(my_file)


lol=[-1]*8
lol[0]=data["start"]

cnt=0

def Place(r,c):
	for i in range(r):
		if(lol[i]==c):
			return 0
		elif(abs(lol[i]-c)==abs(i-r)):
			return 0
	return 1

def printthisshit():
	global cnt
	cnt=cnt+1
	print cnt
	for i in range(8):
		for j in range(8):
			if(lol[i]==j):
				print(i,j)


def Queen(row):
	for column in range(8):
		if(Place(row,column)):
			lol[row]=column
			if(row==7):
				printthisshit()
			else:
				Queen(row+1)
				
						

Queen(0)

