#include<iostream>
#include <string.h>
using namespace std;
int main()
{
    int i,j,l;
  //  int tsc=12;
    char gen[12]={'F','M','F','F','F','M','F','M','M','F','M','F'};
    float h[12]={1.6f,2.0f,1.9f,1.88f,1.7f,1.85f,1.6f,1.7f,2.2f,1.8f,1.95f,1.9f};
    char op[12][10]={"short","tall","medium","medium","short","medium","short","short","tall","medium","medium","medium"};
   //      number of words, no of letters
    cout<<"\n Initial Set:";
    cout<<"\nGender\tHeight\tOutput";
    for(i=0;i<12;i++)
    {
        cout<<"\n"<<gen[i]<<"\t"<<h[i]<<"\t"<<op[i];
    }
 
    float nh;
    char ng;
    cout<<"\n Enter tuple to be processed (Height,Gender) :";
    cin>>nh>>ng;
 
    int t;
    cout<<"\n Enter threshold:";
    cin>>t;
 
    float d[12][2],k;
 
    //calculating distance to each value in training set
    for(i=0;i<12;i++)
    {
        d[i][0]=i;
        k=h[i]-nh;
        if(k<0)
        {
            d[i][1]=-k;
        }
        else
        {
            d[i][1]=k;
        }
    }
 
    //Sorting
    for(i=0;i<11;i++)
    {
        for(j=0;j<11;j++)
        {
            if(d[j][1]>d[j+1][1])
            {
                k=d[j][1];
                d[j][1]=d[j+1][1];
                d[j+1][1]=k;
 
                l=d[j][0];
                d[j][0]=d[j+1][0];
                d[j+1][0]=l;
            }
        }
    }
 
    int nos=0;  //no of shorts
    int nom=0;  //no of mediums
    int not1=0;  //no of talls
 
    cout<<"\nGender\tHeight\tOutput\n";
    for(i=0;i<t;i++)
    {
        l=d[i][0];
        cout<<gen[l]<<"\t"<<h[l]<<"\t"<<op[l]<<"\n";
        if(strcmp(op[l],"short")==0)
        {
            nos++;
        }
        if(strcmp(op[l],"medium")==0)
        {
            nom++;
        }
        if(strcmp(op[l],"tall")==0)
        {
            not1++;
        }
    }
 
    cout<<"\n No of shorts:"<<nos;
    cout<<"\n No of medium:"<<nom;
    cout<<"\n No of tall:"<<not1;
 
    if(nos>nom&&nos>not1)
    {
        cout<<"\n New Tuple is classified as Short";
    }	
 
    if(nom>nos&&nom>not1)
    {
        cout<<"\n New Tuple is classified as Medium";
    }
 
    if(not1>nom&&not1>nos)
    {
        cout<<"\n New Tuple is classified as Tall";
    }
 
 return 0;
    //getch();
}
 
/* OUTPUT
 
 
 Initial Set:
Gender  Height  Output
F       1.6     short
M       2       tall
F       1.9     medium
F       1.88    medium
F       1.7     short
M       1.85    medium
F       1.6     short
M       1.7     short
M       2.2     tall
F       1.8     medium
M       1.95    medium
F       1.9     medium
 Enter tuple to be processed (Height,Gender) :1.7 M
 
 Enter threshold:5
 
Gender  Height  Output
F       1.7     short
M       1.7     short
F       1.8     medium
F       1.6     short
F       1.6     short
 
 No of shorts:4
 No of medium:1
 No of tall:0
 New Tuple is classified as Short
 
*/
