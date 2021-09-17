#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<stdio.h>
using namespace std;
struct cnt
{
	string name;
	int num;
};
struct cnt a[32] = { "auto", 0,"break",0,"case",0,"char",0,"const", 0,"continue",0,"default",0,"do", 0,"double",0,"else",0,"enum",0,"float",0,"for",0,"goto",0,"if",0,"int",0,"long",0,"register",0, "while", 0,"reuturn",0,"short",0,"signed",0,"sizeof",0,"static", 0,"struct",0,"switch",0,"typedef",0,"union",0,"unsigned",0,"void", 0 ,"volatile",0,"while", 0 };
int sum = 0;//求出关键字总数 
int fswitch = -1;//判断switch后面有几个case 
int casenum[1500] = { 0 };//存储每个switch后面case的数量 
string ifel[1500];
int findif = 0, findelse = 0, top = 0, cntifelse = 0, cntif_else = 0;
char s1[500];
void findswitch(int i)
{
	if (i == 25)//找switch 
		fswitch++;
	if (i == 2)//找每个switch后面跟着的case数量 
		casenum[fswitch]++;
}
void findifelse(int i)
{
	if (i == 14)//i=14时为if 
		findif = 1;
	if (i == 9)//i=9时为else 
		findelse = 1;
}
void judgeifelse()
{
	int i;
	if (findif == 1 && findelse == 0)//一行只有if 
	{
		ifel[top] = "if"; top++;//if入栈 
	}
	else if (findif == 1 && findelse == 1)//一行有ifelse 
	{
		ifel[top] = "if_else"; top++;//入栈 
	}
	else if (findif == 0 && findelse == 1)//出现else 
	{
		if (ifel[top - 1] == "if")//判断if-else结构 
		{
			top--;
			cntifelse++;
		}
		else
		{
			for (i = top - 1; ifel[i] != "if"; i--)//判断if-if_else-else结构 
			{
				;
			}
			cntif_else++;
			top = i;
		}
	}
	findif = 0; findelse = 0;//重新进行新一行的判断 
}
void findstring(string s)
{
	int i;
	while (1)
	{
		gets_s(s1);//读入一行代码 
		s = s1;
		if (s.length()<=0)//判断是否为空 
		break;
		for (i = 0; i < 32; i++)//统计关键字主要循环 
		{
			if (s.find(a[i].name) != -1)
			{
				a[i].num++;
				findswitch(i);
				findifelse(i);
			}
		}
		judgeifelse();
	}
	sum = 0;
	for (i = 0; i < 32; i++)//计算关键字总字数 
	{
		sum += a[i].num;
	}
}
void printstr(int level)
{
	int i;
	cout << "total num: " << sum << endl;//求关键字总数 
	if (level > 1)
	{
		cout << "switch num: " << fswitch + 1 << endl;//fswitch从-1开始计数
		cout << "case num: ";
		for (i = 0; i <= fswitch; i++)
		{
			cout << casenum[i] << " ";
		}
		if (fswitch == -1)//不存在时输出0 
		cout << "0";
		cout<<endl;
		if (level > 2)
		{
			cout << "if-else num: " << cntifelse << endl;
			if (level > 3)
				cout << "if-elseif-else num: " << cntif_else << endl;
		}
	}
}
int main()
{
	char road[500];
	int level;
	gets_s(road);//读入文件路径 
	cin >> level;
	FILE* fp = freopen(road, "r",stdin);
	if (fp == NULL)//找不到则返回NULL 
	{
		cout << "Not Fount" << endl;
		return 0;
	}
	string s;
	int i, j;
	findstring(s);
	printstr(level);
}
