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
int sum = 0;//����ؼ������� 
int fswitch = -1;//�ж�switch�����м���case 
int casenum[1500] = { 0 };//�洢ÿ��switch����case������ 
string ifel[1500];
int findif = 0, findelse = 0, top = 0, cntifelse = 0, cntif_else = 0;
char s1[500];
void findswitch(int i)
{
	if (i == 25)//��switch 
		fswitch++;
	if (i == 2)//��ÿ��switch������ŵ�case���� 
		casenum[fswitch]++;
}
void findifelse(int i)
{
	if (i == 14)//i=14ʱΪif 
		findif = 1;
	if (i == 9)//i=9ʱΪelse 
		findelse = 1;
}
void judgeifelse()
{
	int i;
	if (findif == 1 && findelse == 0)//һ��ֻ��if 
	{
		ifel[top] = "if"; top++;//if��ջ 
	}
	else if (findif == 1 && findelse == 1)//һ����ifelse 
	{
		ifel[top] = "if_else"; top++;//��ջ 
	}
	else if (findif == 0 && findelse == 1)//����else 
	{
		if (ifel[top - 1] == "if")//�ж�if-else�ṹ 
		{
			top--;
			cntifelse++;
		}
		else
		{
			for (i = top - 1; ifel[i] != "if"; i--)//�ж�if-if_else-else�ṹ 
			{
				;
			}
			cntif_else++;
			top = i;
		}
	}
	findif = 0; findelse = 0;//���½�����һ�е��ж� 
}
void findstring(string s)
{
	int i;
	while (1)
	{
		gets_s(s1);//����һ�д��� 
		s = s1;
		if (s.length()<=0)//�ж��Ƿ�Ϊ�� 
		break;
		for (i = 0; i < 32; i++)//ͳ�ƹؼ�����Ҫѭ�� 
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
	for (i = 0; i < 32; i++)//����ؼ��������� 
	{
		sum += a[i].num;
	}
}
void printstr(int level)
{
	int i;
	cout << "total num: " << sum << endl;//��ؼ������� 
	if (level > 1)
	{
		cout << "switch num: " << fswitch + 1 << endl;//fswitch��-1��ʼ����
		cout << "case num: ";
		for (i = 0; i <= fswitch; i++)
		{
			cout << casenum[i] << " ";
		}
		if (fswitch == -1)//������ʱ���0 
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
	gets_s(road);//�����ļ�·�� 
	cin >> level;
	FILE* fp = freopen(road, "r",stdin);
	if (fp == NULL)//�Ҳ����򷵻�NULL 
	{
		cout << "Not Fount" << endl;
		return 0;
	}
	string s;
	int i, j;
	findstring(s);
	printstr(level);
}
