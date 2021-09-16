#include<iostream>
#include<string.h>
#include<fstream>
#include<stdio.h>
using namespace std;
struct cnt
{
	string name;
	int num;
};
struct cnt a[32]={ "auto", 0,"break",0,"case",0,"char",0,"const", 0,"continue",0,"default",0,"do", 0,"double",0,"else",0,"enum",0,"float",0,"for",0,"goto",0,"if",0,"int",0,"long",0,"register",0, "while", 0,"reuturn",0,"short",0,"signed",0,"sizeof",0,"static", 0,"struct",0,"switch",0,"typedef",0,"union",0,"unsigned",0,"void", 0 ,"volatile",0,"while", 0};
int sum=0;//求出关键字总数 
int fswitch=-1;//判断switch后面有几个case 
int casenum[1500]={0};//存储每个switch后面case的数量 
string ifel[1500]; 
int findif=0,findelse=0,top=0,cntifelse=0,cntif_else=0;
void findswitch(int i)
{
	if(i==25)//找switch 
	fswitch++;
	if(i==2)//找每个switch后面跟着的case数量 
	casenum[fswitch]++;
}
void findifelse(int i)
{
	if(i==14)
	findif=1;
	if(i==9)
	findelse=1;
}
void judgeifelse()
{
	int i;
	if(findif==1&&findelse==0)
	{
		ifel[top]="if"; top++;
	}
	else if(findif==1&&findelse==1)
	{
		ifel[top]="if_else"; top++;
	}
	else if(findif==0&&findelse==1)
	{
		if(ifel[top-1]=="if")
		{
			top--;
			cntifelse++;
		}
		else
		{
			for(i=top-1;ifel[i]!="if";i--)
			{;}
			cntif_else++;
			top=i;
		}
	}
	findif=0; findelse=0;
}
void findstring(string s)
{
	int i;
	while(getline(cin,s)!=NULL)
	{
		for(i=0;i<32;i++)
		{
			if(s.find(a[i].name)!=-1)
			{
				a[i].num++;
				findswitch(i);
				findifelse(i);	
			}
		}
		judgeifelse();
	}
	sum=0;
	for(i=0;i<32;i++)
	{
		sum+=a[i].num;
	}
}
void printstr(int level)
{
	int i;
	cout<<"total num: "<<sum<<endl;//求关键字总数 
	if(level>1)
	{
		cout<<"switch num: "<<fswitch+1<<endl;//fswitch从-1开始计数
		cout<<"case num: ";
		for(i=0;i<=fswitch;i++)
		{
			cout<<casenum[i]<<" ";
		}
		cout<<endl; 
		if(level>2)
		{
			cout<<"if-else num: "<<cntifelse<<endl;
			if(level>3)
			cout<<"if-elseif-else num: "<<cntif_else<<endl;
    	}
    }
}
int main()
{
	char road[500];
	int level;
	cin>>road;
	cin>>level;
	FILE *fp=freopen(road,"r",stdin);
	if(fp==NULL)
	{
		cout<<"Not Fount"<<endl;
		return 0;
	}
	string s;
	int i,j;
	findstring(s);
	printstr(level);
}
