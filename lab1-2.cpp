#include<stdio.h>
#include<string.h>
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	int count_keyword=0;//the number of keyword
	int count_switch=0;//the number of switch
	int count_switch_case[100]={0};//to store the number of case in each switch
	int count_if_else=0;//the number of if-else structure
	int count_if_elseif_else=0;//the number of if-elseif-else structure
	int flag[100]={0};
	int level;
	string line;
	string filename;
	ifstream inFile;
	cout<<"Please input the file name: ";
	cin>>filename;
	cout<<"Please input the level: ";
	cin>>level;
	inFile.open(filename.c_str());
	//test if the file opens
	if(!inFile.is_open())
	{
		cout<<"The file was not successfully opened"<<endl;
		return 0;
	}
	string keyword[32]={"void","char","int","float","double","short","long","signed","unsigned",
		"struct","union","enum","typedef","sizeof","auto","static","register","extern","const","volatile",
		"return","continue","break","goto","if","else","switch","case","default","for","do","while"};

	//basic requirment
	string set[100];//to store the strings in the code read
	int num=0;
	while(getline(inFile,line))
	{
		int i=0,j=0;
		string a;
		for(i=0;i<int(line.length());i++)
		{
			if(line[i]>='a'&&line[i]<='z')//if the i position is a letter
			{
				for(j=i;line[j]>='a'&&line[j]<='z';j++);
				a=line.substr(i,j-i);
				set[num]=a;				
				num++;
				if(set[num-1]=="else"&&line[j]==' ')
					flag[num-1]=1;
				for(int k=0;k<32;k++)
				{
					if(a==keyword[k])
					{
						count_keyword++;
						break;
					}
				}
				i=j;
			}
			else
			{
				j=i;
			} 
		}
	}
	cout<<"total num: "<<count_keyword<<endl;
	
	//Advanced requirement
	for(int i=0;i<num;i++)
	{
		if(set[i]=="switch")
		{
			count_switch++;
			for(int j=i+1;j<num;j++)
			{
				if(set[j]=="case")
					count_switch_case[count_switch]++;	
				else if(set[j]=="switch")
				{
					i=j-1;
					break;
				}				
			}
		}
	}
	if(level>=2)
	{
		cout<<"switch num: "<<count_switch<<endl;
		cout<<"case num: ";
		for(int i=1;i<=count_switch;i++)
			cout<<count_switch_case[i]<<" ";
		cout<<endl;
	}

	//Uplifting requirement & Ultimate requirement
	int i,j,m;
	int count_elseif=0;//to calculate the number of elseif
	for(i=0;i<num;i++)
	{
		if(set[i]=="else"&&flag[i]==0)//find else not in else-if
		{
			for(j=i;j>=0;j--)//Each timelook for the matching if from the current else position
			{
				if(set[j]=="if"&&count_elseif==0)//find if and not elseif between them
				{
					count_if_else++;//if-else structure
					set[i]=" "; 
					set[j]=" ";
					break;
				}
				else if(set[j]=="if"&&count_elseif!=0)//elseif between them
				{
					count_if_elseif_else++;//if_elseif_else structure
					for(m=i;m<=j;m++)
					{
						if(set[m]=="else"&&flag[m]==1)
							count_elseif--;
						set[m]=" ";
					}
					break;
				}
				else if(set[j]=="else"&&flag[j]==1)
					count_elseif++;
			}
		}
	}
	if(level>=3)
	{
		cout<<"if-else num: "<<count_if_else<<endl;
	}
	if(level==4)
	{
		cout<<"if-elseif-else num:"<<count_if_elseif_else<<endl;
	}

	
	return 0;
}

