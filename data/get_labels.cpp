#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string.h>
#include<stdlib.h>

using namespace std;

class image
{
public:
	char name[10];
	int x,y,w,h;
	image(char line[50]);
};
image::image(char line[50])
{
	int x1,y1,x2,y2;
	int c=0,d=0;
	char temp[10];
	for(int i=0;line[i]!='\0';i++)
	{
		if(line[i]==';')
		{
			temp[d]='\0';
			if(c==0)
				strcpy(name,temp);
			if(c==1)
				x1=atoi(temp);
			if(c==2)
				y1=atoi(temp);
			if(c==3)
				x2=atoi(temp);
			if(c==4)
				y2=atoi(temp);
			if(c==5)
				break;
			c++;
			d=0;
		}
		else
		{
			temp[d++]=line[i];
		}
	}
	x=(x1+x2)/2;
	y=(y1+y2)/2;
	w=x2-x1;
	h=y2-y1;
}

void new_file(char line[],int flag)
{
	if(flag==0)
	{
		image I(line);
		ofstream fout,fout2;
		char name[50];
		for(int i=0;i<6;i++)
			name[i]=I.name[i];
		name[6]='\0';
		strcat(name,"txt");
		fout.open(name);
		fout2.open("../train.txt",ios::app);
		fout2<<"data/obj/"<<name<<'\n';
		fout<<0<<' '<<float(I.x/1360.0)<<' '<<float(I.y/800.0)<<' '<<float(I.w/1360.0)<<' '<<float(I.h/800.0)<<'\n';
		fout.close();
		fout2.close();
	}
	else
	{
		image I(line);
		ofstream fout;
		char name[50];
		for(int i=0;i<6;i++)
			name[i]=I.name[i];
		name[6]='\0';	
		strcat(name,"txt");
		fout.open(name,ios::app);
		fout<<0<<' '<<float(I.x/1360.0)<<' '<<float(I.y/800.0)<<' '<<float(I.w/1360.0)<<' '<<float(I.h/800.0)<<'\n';
		fout.close();
	}
}

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("/home/sanskar/DL/Traffic_sign/dataset_old/gt.txt");
	if(!fin)
		cout<<"error";
	char line[50],prev[50];
 	jmp:
 	fin.getline(line,50,'\n');
 	if(!fin)
 	{
 		cout<<"End of file";
 		return 0;
 	}
 	image temp(line);
 	if(strcmp(temp.name,prev)==0)
 		new_file(line,1);
 	else
 		new_file(line,0);
 	strcpy(prev,temp.name);
 	goto jmp;


	fin.close();
	return 0;
}