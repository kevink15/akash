#include <iostream>
#include <string.h>
#include <sstream>

using namespace std;

class stack{
	char data[20][3];
	int top;

public:
	stack(){
		top=-1;
	}
	void push(char a[3]){
		strcpy(data[++top],a);
	}
	char* pop(){
		return data[top--];
	}
	char* return_top(){
		return data[top];
	}
	bool isEmpty(){
		if(top==-1){return true;}
		else {return false;}
	}
	void print_stack(){
		for(int i=top;i>=0;i--){
			cout<<data[i]<<" , ";
		}
	}
};


stack reg_stack;
stack temp_stack;

class node{

public:
	char data;
	node* left;
	node* right;
	bool leftchild;
	int label;

	node(){
		data=' ';
		left=NULL;
		right=NULL;
		leftchild=true;
		label=0;
	}

    node(char d,bool l){
    	data=d;
    	left=NULL;
    	right=NULL;
    	leftchild=l;
    	label=0;
    }
};

void accept_dag(node* t){
	//first the left subtree is created then the right subtree
		cout<<" Enter data for node:  ";
		cin>>t->data;
		//if it is an operator accept the operands
		if(t->data=='+'||t->data=='-'||t->data=='*'||t->data=='/'){
			cout<<"\nEnter left child of "<<t->data;
			//create a new left child node
			node* l=new node(' ',true);
			t->left=l;
			accept_dag(l);
			//create the right child of that node
			cout<<"\nEnter right child of "<<t->data;
			node* l1=new node(' ',false);
			t->right=l1;
			accept_dag(l1);


		}


}

void labelling(node* t){
	//labelling is done to ensure partial ordering;each label corresponds to an element in the set
	//labels basically show the path in the DAG. if l1>l2:there is a path from l1->l2. if l1 = l2 then parent has label l3 = l1+1 as it has to be unique,if l3=l1,then there would be a cycle l1->l2->l3
	if(t!=NULL){
		labelling(t->left); //left subtree is labelled first
		labelling(t->right);//followed by the right subtree

		if(t->left==NULL&&t->right==NULL){   //for leaf
			if(t->leftchild==true){t->label=1;}  //left leaf is labelled as 1
			else {t->label=0;}                   //right leaf is labelled as 0
		}
		else{
			int l1=t->left->label;//find the label of the left child
			int l2=t->right->label;//find the label if the right child
			if(l1==l2){
				t->label=l1+1;//if the labels are equal,parent label increments by 1
			}
			else{
				t->label=(l1>l2?l1:l2);//if not equal then the greater of the child labels is taken by the parent
			}
		}
	}
}
void inorder(node* t){
	//inorder is left->root->right
	if(t!=NULL){
		inorder(t->left);
		cout<<t->data<<" :"<<t->label<<" ,  ";
		inorder(t->right);
	}
}

void initialize_stacks(){
	        int k;
			cout<<"\n Enter Size of reg_stack: ";
		    cin>>k;
		    //this function basically names the regular and the temporary registers by using the stringstream class to handle the integer value as string
		    for(int i=0;i<k;i++){
		    	//3 because a[0] is R/t[0] is t,a[1]/t[1] will contain the integer number and a[2]/t[2] is going to be the null termination character as c_str()returns a pointer with null-terminated character.
		    	char a[3]="R";
		    	char t[3]="t";
		    	int l=k-i-1;
		    	//create a stringstream object strs
		    	stringstream strs;strs<<l;
		    	//concatenates a,str()returns the contents of the buffer in string type,c_str() returns a pointer to an array that contains the null-terminated value of the string
		    	strcat(a,strs.str().c_str());
		    	//push the concatenated value to the regular stack
		    	reg_stack.push(a);
		    	//push the string value to the temporary stack.
		    	temp_stack.push(strcat(t,strs.str().c_str()));
		    }
	    cout<<"\nRegister Stack :";
	    reg_stack.print_stack();
	    cout<<"\nTemp Variables Stack :";
	    temp_stack.print_stack();
}

void swap(stack s){
	char* a=s.pop();
	char* b=s.pop();
	s.push(b);
	s.push(a);
}

char* op(char o){
	if(o=='+') {return (char*)"ADD";}
	else if(o=='-') {return (char*)"SUB";}
	else if(o=='*') {return (char*)"MUL";}
	else {return (char*)"DIV";}
}
void Gen_code(node* n){
    if(n->left==NULL&&n->right==NULL&&n->leftchild==true){    //for left child
    	cout<<"MOV  "<<n->data<<" , "<<reg_stack.return_top()<<"\n";
    }
    else{
    	node* n1=n->left;
    	node* n2=n->right;

    	if(n2->label==0){//right child present then start with the left child as if there is an operator first operand is going to be the left child,and we have to check if it is an operator by checking for the right child
    		Gen_code(n1);
    		cout<<op(n->data)<<" "<<n2->data<<" , "<<reg_stack.return_top()<<"\n";
    	}

    	else if(n1->label<n2->label){//left child label is less than right child label
    		swap(reg_stack);//swap the top element with the second top element
    		Gen_code(n2);
    		char* r=reg_stack.pop();//pop the right child so that left child can be evaluated
    		Gen_code(n1);
    		cout<<op(n->data)<<"  "<<r<<" , "<<reg_stack.return_top()<<"\n";
    		reg_stack.push(r);//push the popped right child back to stack
    		swap(reg_stack);//swap them again to get the original stack
    	}

    	else if(n2->label<n1->label){//first left ,then right child
    		Gen_code(n1);
    		char* r=reg_stack.pop();
    		Gen_code(n2);
    		cout<<op(n->data)<<"  "<<r<<" , "<<reg_stack.return_top()<<"\n";
    		reg_stack.push(r);
    	}
    	else{
    		Gen_code(n2);//for intermediate nodes
    		char* t=temp_stack.pop();
    		cout<<"MOV  "<<reg_stack.return_top()<<"  ,  "<<t<<"\n";//second topmost element
    		Gen_code(n1);
    		temp_stack.push(t);//get original stack
    		cout<<op(n->data)<<"  "<<t<<" , "<<reg_stack.return_top()<<"\n";
    	}
    }

}

int main() {
	node* root=NULL;
	root=new node();
	cout<<"\nStarting with the root node enter data: \n";
	accept_dag(root);

	labelling(root);

	cout<<"\nEntered Tree with labels is: \n";
	inorder(root);
	initialize_stacks();
	cout<<"\n\nGenerated Code is:\n****************************************\n\n";
	Gen_code(root);
	cout<<"\n\n****************************************";
	cout<<"\nFinal result is stored in register:  "<<reg_stack.return_top();
	return 0;
}