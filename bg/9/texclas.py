from math import log
from math import sqrt
from collections import Counter
from operator import itemgetter

def tf(term, document):
	return document.count(term)

def idf(term, allDocuments):
	numofdocswithterm=0
	for x in allDocuments:
		if term in x:
			numofdocswithterm=numofdocswithterm+1

	if numofdocswithterm>0:
		return round(log((float(len(allDocuments))/numofdocswithterm),2),3)
	else:
		return 0

def tfidf(term, document):
	return tf(term, document)*idf(term, terms)

def cosinesimilarity(doc, q, d):
	a=0
	for x in d:
		a=a+tfidf(x, doc)*tfidf(x, q)
	b=lengthof(doc, d)*lengthof(doc, q)

	if not b:
		return 0
	else:
		return round(a/b, 3)

def lengthof(document, d):
	val=0
	for x in d:
		val=val+pow((tfidf(x, document)),2)
	return sqrt(val)


f=[]		#list containing file contents
terms=[]	#contains all non-unique terms
fin_terms=[]	#contains unique terms

docs=['doc1.txt','doc2.txt','doc3.txt','doc4.txt','doc5.txt','doc6.txt']		#list of documents to compare queried document to
dataset=[ ['doc1.txt','science'], ['doc2.txt','science'], ['doc3.txt','science'], ['doc4.txt','entertainment'], ['doc5.txt','entertainment'], ['doc6.txt','entertainment'] ] #list of documents along with the corresponding class

testf=raw_input('Enter the name of the query document.\n')
q=open(testf, 'r').readline().lower()		#this is the document we're trying to label by giving it a class based on labels of labeled documents

for x in docs:
	f.append(open(x, 'r').read())	#reading all the words in all documents into a list f

for x in f:
	terms.append(x.lower().rsplit('\n'))	#cleaning contents of f by removing newlines

for x in terms:
	fin_terms=fin_terms+x	

fin_terms=set(fin_terms)	#set(fin_terms) will ensure that each term occurs only once
fin_terms=list(fin_terms)	#convert(fin_terms) back to a list as we need to do list manipulations

cnt=0
for x in terms:
	dataset[cnt]=dataset[cnt]+[cosinesimilarity(q, x, fin_terms)]	#this will append a third dimension to the dataset entity. now dataset will have document name, class, associated cosine value
	cnt=cnt+1

k=3	#k is the number of closest neighbors for the queried documents. we're going to see which documents have the highest cosine similarity value to our queried document. then out of the three closest documents, we're going to assign the majority class to the queried document

sorted_dataset=sorted(dataset, key=itemgetter(2), reverse=True)	#sort in terms of cosin similarity value. higher value means closer to queried document

top_k=sorted_dataset[:k]	#this will keep only top three documents with higest cosine value

top_k[:] = (x for x in top_k if x[2]!=0)	#will ignore those which have cosine value of 0

if len(top_k)==0:	#if all the documents have cosine similarity 0, then there's no match to queried doc
	print ("Queried document doesn't match!")
else:
	class_counts = Counter(category for (document, category, value) in top_k)	#count the number of times each class occurs in the k neighbors
	print (class_counts)

	classification = max(class_counts, key=lambda cls:class_counts[cls])	#max will determine the majority class
	print("Class of queried document is:")
	print(classification)






