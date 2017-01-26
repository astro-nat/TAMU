#include<iostream>
#include<conio>
#include<stdio>

int main( )
{
	clrscr( );
	char str[80];
	int temp;
	cout<<"Enter string :";
	gets(str);
	
	for(int l=0;str[l]!='\0';l++);    //finding length of string

	for(int i=0,j=l-1;i<l/2;i++,j--)
	{
		temp=str[i];
		str[i]=str[j];
		str[j]=temp;		
	}

	cout<<"Reverse String is\n"<<str;
	
	getch();
	return 0;
}