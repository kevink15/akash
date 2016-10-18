print("Fill up parse table:  ")
n=input("enter number of states: ")
nterm=input("enter number of terminals:  ")
term=[]
print("Enter Terminal Symbols:   ")
for i in range(nterm):
  nt=raw_input()
  term.append(nt)

print("Terminal Symbols are as given:  ")
print(term)

nnterm=input("enter number of Non-Terminals:  ")
non_term=[]
print("Enter Non-Terminal Symbols:   ")
for i in range(nnterm):
  nt=raw_input()
  non_term.append(nt)

print("Terminal Symbols are as given:  ")
print(non_term)

nprod=input("Enter Number of productions:  ")
lsprod=[]
rsprod=[]
for i in range(nprod):
  lsprod.append(raw_input("enter Left side of production number "+str(i)+"   "))
  rsprod.append(raw_input("enter Right side of production number "+str(i)+"   "))

print("Grammar Productions are as follows:   ")
for i in range(nprod):
   print(lsprod[i]+" -> "+rsprod[i])

action=[["Error" for x in range(nterm)] for x in range(n)]
nstate=[[0 for x in range(nterm)] for x in range(n)]
for i in range(n):
  for j in range(nterm):
    action[i][j]=raw_input("Enter Action for State "+str(i)+" on input symbol "+term[j]+"  ")
    if(action[i][j]!="Error" and action[i][j]!="Accept"):
       nstate[i][j]=input("Enter next state for State "+str(i)+" on input symbol "+term[j]+" ")

print("\n")
goto=[[0 for x in range(nnterm)] for x in range(n)]
for i in range(n):
  for j in range(nnterm):
     goto[i][j]=input("Enter goto for State "+str(i)+" and Non Terminal "+non_term[j]+" ")

print("Action Table:  ")
for i in range(n):
  print("")
  for j in range(nterm):
     print(action[i][j]+str(nstate[i][j])+"   "),
print("")
print("Goto Table:    ")
for i in range(n):
  print(" ")
  for j in range(nnterm):
    print(str(goto[i][j])+"   "),

while True:
  print("\nEnter input String:  "),
  istr=raw_input()

  iptr=0

  stack=['$',0]
  while True:
    print("Stack :"),
    print(stack)
    stop=stack[len(stack)-1]
    isym=istr[iptr]
    isindex=term.index(isym)
    ac=action[stop][isindex]
    print("Action for stop="+str(stop)+" and input symbol index   "+str(isindex)+" is "+action[stop][isindex])
    if(ac=="Error"):
       print("Syntax Error!!!")
       break
    elif(ac=="Accept"):
       print("Correct Syntax!!")
       break
    elif(ac=="s"):
       stack.append(isym)
       stack.append(nstate[stop][isindex])
       iptr=iptr+1
    else:
       rrule=nstate[stop][isindex]
       print("Reduce using rule  "+lsprod[rrule-1]+"  ->  "+rsprod[rrule-1])
       for i in range(2*len(rsprod[rrule-1])):
           stack.pop()
       print(stack)
       stack.append(lsprod[rrule-1])
       pstate=stack[len(stack)-2]
       ntindex=non_term.index(lsprod[rrule-1])
       nst=goto[pstate][ntindex]
       stack.append(nst)
       print(stack)
