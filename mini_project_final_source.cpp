#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;
bool check_scratch(char []);
bool check_stopwords(char []);
void isduplicate(char []);
void resetword(char []);
void to_lower_case(char []);
int getlength(char []);
bool comparison(char[] , char[]);
void get_count(char [], int &, int &, int &);
void output(int, int, int, float, float);
void check_sentence();
void word_dictionary();
void write_file(char [],int);
void intro();
int recordcount=0;
int main()
{
	cout<<endl<<endl<<endl<<endl;
	intro();
	cin.get();
	system("cls");
	char choice='\0';
	cout<<"Press 1 to check a sentence"<<endl<<"press 2 to make dictionary from file"<<endl<<"Press 3 to exit"<<endl<<"Enter your choice :";
	cin>>choice;
	do
	{
		if(choice=='1')
			check_sentence();
		else if(choice=='2')
			word_dictionary();
		else if(choice=='3')
			exit(1);
		else
			cout<<"Enter a valid choice"<<endl;
		system("cls");
		cout<<"Press 1 to check a sentence"<<endl<<"press 2 to make dictionary from file"<<endl<<"Press 3 to exit"<<endl<<"Enter your choice :";
		cin>>choice;
	}while(choice!=3);
	
	return 0;
}
void check_sentence(){
	int count=0,count1=0,count2=0;
	int t_count=0,t_count1=0,t_count2=0;
	float n_count1=0.0,n_count2=0.0;
	char sentence[500]={'\0'};
	cout<<"Please enter a sentence :";
	cin.ignore();
	cin.getline(sentence,499);
	cout<<"Computing results....Please wait...!!!"<<endl;
	char word[20]={'\0'};
	for(int i=0;sentence[i]!='\0';i++)
	{
		for(int j=0;sentence[i]!=' ' && sentence[i]!='.' && sentence[i];j++,i++)
		{
			word[j]=sentence[i];
		}
		if(check_scratch(word))
		{
			to_lower_case(word);
			if(check_stopwords(word))
			{
				get_count(word ,t_count,t_count1,t_count2);
			}

		}
		resetword(word);
	}
	n_count1=float(t_count1)/float(t_count);
	n_count2=float(t_count2)/float(t_count);
	output(t_count,t_count1,t_count2,n_count1,n_count2);
}
bool check_scratch(char word[]){
	bool flag=0;
	for(int i=0;word[i]!='\0';i++)
	{
		if((word[i]>='a' && word[i]<='z' || word[i]>='A' && word[i]<='Z'))
		{
			flag=1;
		}
		else
		{
			flag=0;
			break;
		}
	}
	return flag;
}
bool check_stopwords(char word[]){
	char word1[20]={'\0'};
	ifstream inFile;
	inFile.open("stopwords.txt",ios::in);
	inFile>>word1;
	while(!inFile.eof())
	{
		if(getlength(word)==getlength(word1))
		{
			if(comparison(word,word1))
			{
				return 0;
			}
		}
		inFile>>word1;
	}
	inFile.close();
	return 1;
}
int getlength(char word[]){
	int i=0;
	while(word[i]!='\0')
	{
		i++;
	}
	return i;
}
bool comparison(char word[], char word1[]){
	for(int i=0;word[i]!='\0';i++)
	{
		if(word[i]!=word1[i])
		{
			return 0;
		}
	}
	return 1;
}
void to_lower_case(char word[]){
	for(int i=0;word[i]!='\0';i++)
	{
		if(word[i]>='A' && word[i]<='Z')
		{
			word[i]=word[i]+32;
		}
	}
}
void resetword(char word[]){
	for(int i=0;word[i]!='\0';i++)
	{
		word[i]='\0';
	}
}
void get_count(char word[],int &a, int &b, int &c){
	char word1[1000]={'\0'};
	int count=0,count1=0,count2=0;
	ifstream inFile;
	inFile.open("dictionary.txt",ios::in);
	while(!inFile.eof())
	{
		inFile>>word1>>count>>count1>>count2;
		if(getlength(word)==getlength(word1))
		{
			if(comparison(word,word1))
			{
				a+=count;
				b+=count1;
				c+=count2;
			}
		}
		resetword(word1);
	}
	inFile.close();
}
void output(int t_count, int t_count1, int t_count2, float n_count1, float n_count2){
	system("cls");
	cout<<"\t\t\t::Without Normalization::"<<endl;
	cout<<"==================================================================="<<endl;
	cout<<setw(22)<<"Total count :"<<setw(12)<<t_count<<endl;
	cout<<setw(20)<<"Total Positive Count :"<<setw(12)<<t_count1<<endl;
	cout<<setw(20)<<"Total Negative Count :"<<setw(12)<<t_count2<<endl;
	if(t_count1>t_count2)
	{
		cout<<setw(20)<<"Result :"<<setw(15)<<"Your sentence is POSITIVE...!!"<<endl;
	}
	else
	{
		cout<<setw(20)<<"Result :"<<setw(15)<<"Your sentence is NEGATIVE...!!"<<endl;
	}
	cout<<endl<<endl<<endl;
	cout<<"\t\t\t ::With Normalization::"<<endl;
	cout<<"==================================================================="<<endl;
	cout<<setw(22)<<"Total count :"<<setw(12)<<t_count<<endl;
	cout<<setw(20)<<"Total Positive Count :"<<setw(12)<<n_count1<<endl;
	cout<<setw(20)<<"Total Negative Count :"<<setw(12)<<n_count2<<endl;
	if(t_count1>t_count2)
	{
		cout<<setw(20)<<"Result :"<<setw(15)<<"Your sentence is POSITIVE...!!"<<endl;
	}
	else
	{
		cout<<setw(20)<<"Result :"<<setw(15)<<"Your sentence is NEGATIVE...!!"<<endl;
	}
	cin.get();
}
void word_dictionary(){
	char sentence[1000]={'\0'};
	char word[100]={'\0'};
	int type=0;
	ifstream inFile;
	inFile.open("rawdata.txt",ios::in);
	inFile>>type;
	inFile.ignore(3);
	inFile.getline(sentence,999);
	while(!inFile.eof())
	{
		for(int i=0; sentence[i]!='\0';i++)
		{
			for(int j=0;sentence[i]!=' ' && sentence[i]!='\0';i++,j++)
			{
				word[j]=sentence[i];
			}
			if(check_scratch(word))
			{
				to_lower_case(word);
				if(check_stopwords(word))
				{	
					write_file(word,type);
				}
			}
			resetword(word);
		}
		resetword(sentence);
		inFile>>type;
		inFile.ignore(3);
		inFile.getline(sentence,999);
	}
	inFile.close();
}
void write_file(char word[],int type)
{
	char word1[1000]={'\0'};
	int totalcount=0;
	int positive=0;
	int negative=0;

	
	if(recordcount==0)
	{
		ofstream outFile;
		recordcount++;
		totalcount++;
		outFile.open("output.txt",ios::out);
		outFile<<word<<" ";
		if(type==0)
		{
			negative++;
			outFile<<totalcount<<" "<<positive<<" "<<negative<<endl;
		}
		else
		{
			positive++;
			outFile<<totalcount<<" "<<positive<<" "<<negative<<endl;
		}
		outFile.close();
	}
	else
	{
		ofstream outFile;
		ifstream inFile;
		inFile.open("output.txt",ios::in);
		outFile.open("temp.txt",ios::out);
		bool flag=0;
		inFile>>word1;
		inFile.ignore();
		inFile>>totalcount>>positive>>negative;
		while(!inFile.eof())
		{
			int i=0;
			while(word[i]!='\0' && word1[i]!='\0')
			{
				if(word[i]!=word1[i])
				{
					break;
				}
				i++;
			}
			if(word[i]=='\0' && word1[i]=='\0')
			{
				flag=1;
				totalcount++;
				if(type==0)
				{
					negative++;
				}
				else
				{
					positive++;
				}
				outFile<<word<<" "<<totalcount<<" "<<positive<<" "<<negative<<endl;
			}
			else
			{
				outFile<<word1<<" "<<totalcount<<" "<<positive<<" "<<negative<<endl;
			}
			inFile>>word1;
			inFile.ignore();
			inFile>>totalcount>>positive>>negative;	
		}
		if(flag!=1)
		{
			totalcount=1;
			positive=0;
			negative=0;
			if(type==0)
			{
				negative++;
			}
			else
			{
				positive++;
			}
			outFile<<word<<" "<<totalcount<<" "<<positive<<" "<<negative<<endl;
		
		}	
		for(int i=0;word1[i]!='\0';i++)
		{
			word1[i]='\0';
		}
		inFile.close();
		outFile.close();
		outFile.open("output.txt",ios::out);
		inFile.open("temp.txt",ios::in);
		inFile>>word1;
		inFile.ignore();
		inFile>>totalcount>>positive>>negative;
		while(!inFile.eof())
		{
			outFile<<word1<<" "<<totalcount<<" "<<positive<<" "<<negative<<endl;
			inFile>>word1;
			inFile.ignore();
			inFile>>totalcount>>positive>>negative;
		}
		inFile.close();
		outFile.close();
	}
}
void intro(){
	cout<<"MM   MM  IIIIIII  NN    N  IIIIIII        PPPP   RRRRR    OOOOO      JJJJJJJJ  EEEEEE   CCCCCCC TTTTTTT     1"<<endl;
	cout<<"M M M M     I     N N   N     I           P   P  R    R  O     O         J     E       C           T      1 1"<<endl;
	cout<<"M  M  M     I     N  N  N     I      ===  PPPP   RRRRR  O       O    J   J     EEEEEE  C           T  ===   1"<<endl;
	cout<<"M     M     I     N   N N     I           P      RR      O     O     J   J     E       C           T        1"<<endl;
	cout<<"M     M  IIIIIII  N    NN  IIIIIII        P      R  R     OOOOO       JJJ      EEEEEE   CCCCCCC    T      11111"<<endl;
	cout<<"\t\t\tName : Muhammad Hamza"<<endl;
	cout<<"\t\t\tReg# : L1S16BSCS0063"<<endl;
	cout<<"\t\t\tSec  : B"<<endl;
}
