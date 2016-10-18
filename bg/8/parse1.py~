import xml.etree.ElementTree as ET

# XML is just a tag heirarchy.
tree = ET.parse('parsing_table.xml')
root = tree.getroot()

# all available terminals and non-terminals in the grammar.
term = []
non_term = []

# whatever is on the LHS and RHS of the production.
lsprod = []
rsprod = []

# no of states
n = 0

# traverse every node and populate it's contents into program variables. Can't reach into the XML file everytime 
# we need something
for child in root:
   if(child.tag == "states"):
   	n = int(child.text)
   elif(child.tag == "term"):
   	term.append(child.text)
   elif(child.tag == "nterm"):
   	non_term.append(child.text)
   elif(child.tag == "productions"):
   	for ch in child:
   		lsprod.append(ch[0].text)
   		rsprod.append(ch[1].text)
   elif(child.tag == "actiontable"):
   	action=[[] for x in range(n)]
   	i=0
   	for ch in child:
   		for c in ch:
   			action[i].append(c.text)
   		i=i+1
   elif(child.tag=="gototable"):
   	goto=[[] for x in range(n)] 
   	i=0
   	for ch in child:
   		for c in ch:
   			goto[i].append(c.text)
   		i=i+1


nterm=len(term)
nnterm=len(non_term)
nprod=len(lsprod)

print("Terminals:    "),;print(term)
print("Non Terminals:    "),;print(non_term)

print("Grammar Productions are as follows:   ")
for i in range(nprod):
   print(lsprod[i]+" -> "+rsprod[i])


print("\nAction Table:  ")
for i in range(n):
  print("")
  for j in range(nterm):
  	print(action[i][j]+"   "),
print("")
print("Goto Table:    ")
for i in range(n):
  print(" ")
  for j in range(nnterm):
  	print(str(goto[i][j])+"   "),

while True:
	print("\nEnter input String:  "),
	istr=input()
	iptr=0

	'''
	Terminals:     ['a', 'b', '$']

	Non Terminals:     ['S', 'A']

	Grammar Productions are as follows:   
	S -> AS
	S -> b
	A -> SA
	A -> a

	Action Table:  

	s5    s3    Error    
	Error    Error    Accept    
	s5    s3    Error    
	r2    r2    r2    
	s5    Error    Error    
	r4    r4    Error    
	r1    r1    r1    
	r3    r3    Error 

	Goto Table:    
	 
	1    2     
	0    0     
	6    2     
	0    0     
	4    7     
	0    0     
	0    0     
	0    0 
	'''


# the actual logic. till now everything was unnecessarily tedious

  # stack[0] is seen as bottom
	stack=['$',0]
	done = False

	while True:

		print("Stack :")
		print(stack)
		# last element in list is stack top
		stack_top = stack[len(stack)-1]

		# pointer has consumed all input
		if iptr >= len(istr):
			done = True
		else:
			# symbol loaded from input into isym
			isym = istr[iptr]

		# index of symbol in the terminal list
		input_sym_index = term.index(isym)
		#  get the action from the action table
		ac = action[stack_top][input_sym_index]

		print("Action for stack_top="+str(stack_top)+" and input symbol index   "+str(input_sym_index)+" is "+ac)
		
		if(ac == "Error"):
		   print("Syntax Error!!!")
		   break
		elif(done or ac == "Accept"):
		   print("Correct Syntax!!")
		   break
		#shifting onto the stack,append the symbol read and the state number
		elif("s" in ac):
			#append the read symbol onto the stack
		   stack.append(isym)
		   ns=ac.replace("s","")
		   #append the state number onto the stack
		   stack.append(int(ns))
		   #increment the pointer
		   iptr=iptr+1
		#replace the element 
		elif("r" in ac):
			#get the state number from ac
		   rrule=int(ac.replace("r",""))
		   print(rrule)
		   #print the production rule that can be used for reduction
		   print("Reduce using rule  "+lsprod[rrule-1]+"  ->  "+rsprod[rrule-1])
		   #this is used for removing the reduced symbols from the stack. '2' signifies the symbol as well as the state associated with it
		   for i in range(2*len(rsprod[rrule-1])):
			   stack.pop()
		   print(stack)
		   #append the non-terminal to the stack
		   stack.append(lsprod[rrule-1])
		   #find the topmost state of the stack
		   pstate=stack[len(stack)-2]
		   print (pstate)
		   #find the index of the non-terminal which replaced the read symbol
		   ntindex=non_term.index(lsprod[rrule-1])
		   print(ntindex)
		   #find the goto state
		   nst=goto[pstate][ntindex]
		   #append the goto state to the stack_top
		   stack.append(int(nst))
		   print(stack)

