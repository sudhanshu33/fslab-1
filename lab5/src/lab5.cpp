//============================================================================
// Name        : lab5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#include<sstream>
#include<sys/types.h>
#include<unistd.h>
using namespace std;
class student{
    string name;
    string usn;
    string branch;
    int sem;
    string buffer;
public:
    string read();
    string pack();
};
class file{
    string name;
    string usn;
    string branch;
    int sem;
    string buffer;
public:
    int pos;
    void write(string);
    void unpack(int);
    //int search(string);
    void del(int);
};
class indf{
public:
    int pos;
    void insert(string,int);
    int search(string);
    void rem(string);
    void indrem(string);
    void updat(int);
};
string student::read()
{
    cin.clear();
    cin.ignore(255,'\n');
    cout<<"enter the name :"<<endl;
    getline(cin,name);
    cout<<"enter the usn :"<<endl;
    cin>>usn;
    cin.clear();
    cin.ignore(255,'\n');
    cout<<"enter the branch :"<<endl;
    getline(cin,branch);
    cout<<"enter the semester :"<<endl;
    cin>>sem;
    cin.clear();
    cin.ignore(255,'\n');
    cout<<endl;
    return usn;
}
string student::pack()
{
    string sem1;
    string temp;
    stringstream out;
    out<<sem;
    sem1=out.str();
    int i;
    temp=usn+'|'+name+'|'+branch+'|'+sem1;
    for(i=temp.size();i<100;i++)
    {
    	temp+='$';
    }
    cout<<temp<<endl;
    buffer=temp;
    return buffer;
}
void file :: write(string buf)
{
    fstream fp1;
    //char flname[max];
    //cout<<"enter the file name to write the read record"<<endl;
    //cin>>flname;
    fp1.open("data.txt",ios::out|ios::app);
    fp1<<buf;
    fp1<<endl;
    int sz=buf.size();
    int loc=fp1.tellp();
    pos=loc-sz;
    fp1.close();
}
void indf::insert(string key,int pos)
{
    fstream fp1;
    fp1.open("inde.txt",ios::out|ios::app);
    string pos1;
    string temp;
    stringstream out;
    out<<pos;
    pos1=out.str();
    int i;
    temp=key+'|'+pos1;
    for(i=temp.size();i<50;i++)
    {
    	temp+='$';
    }
    fp1<<temp;
    fp1<<endl;
    fp1.close();
}
int indf::search(string key)
{
   // cout<<"inside search"<<endl;
    fstream fp1;
    string buffer,unkey,unpos,s;
    int i;
    fp1.open("inde.txt",ios::in);
    while(!fp1.eof())
    {
     //   cout<<"*"<<endl;
	getline(fp1,buffer);
        int k=key.size();
        string sub=buffer.substr(0,k);
        //cout<<"sub string is : "<<sub<<endl;
        if(key==sub)
        {
       //     cout<<"almost found"<<endl;
            while(buffer[i]!='|')
            {
		unkey+=buffer[i];
		i++;
            }
            i++;
            while(buffer[i]!='$')
            {
		unpos+=buffer[i];
		i++;
            }
         //   cout<<"done unpacking"<<endl;
            s=unpos;
            stringstream convert(s);
            convert>>pos;
            cout<<"position in file : "<<pos<<endl;
           // cout<<"out of search"<<endl;
            return 0;
        }
        else
        {
            cout<<"record not found"<<endl;
            
        }
    }
    return -1;
      //cout<<"out of search"<<endl;
}
void file::unpack(int pos1)
{
    fstream fp1;
    string buffer;
    fp1.open("data.txt",ios::in);
    fp1.seekp(pos1,ios::beg);
    getline(fp1,buffer);
    string s;
    int i=0;
    cout<<endl<<endl;
    usn.erase();
    while(buffer[i]!='|')
    {
	usn+=buffer[i];
	i++;
    }
    i++;
    name.erase();
    while(buffer[i]!='|')
    {
	name+=buffer[i];
	i++;
    }
    i++;
    branch.erase();
    while(buffer[i]!='|')
    {
	branch+=buffer[i];
	i++;
    }
    i++;
    sem=0;
    while(buffer[i]!='$')
    {
	s=buffer[i];
	stringstream convert(s);
	convert>>sem;
	i++;
    }
    cout<<"usn is : "<<usn<<endl;
    cout<<"name is : "<<name<<endl;
    cout<<"branch is : "<<branch<<endl;
    cout<<"sem is : "<<sem<<endl;
}
void indf::rem(string key)
{
   //cout<<"started to remove record"<<endl; 
   //cout<<"back to remove"<<endl;
   string buffer,usn1;
   indf f;
   int i=pos;
   int j=0,l,siz1=0,loc1=0,pos1=0;
   cout<<"value of pos in rem function : "<<i<<endl;  
   fstream fp1,fp2,fp3;
   fp1.open("data.txt",ios::in);
   fp2.open("tempdata.txt",ios::out);
   fp2.close();
   fp2.open("tempdata.txt",ios::out|ios::app);
   l=0;
   while(!fp1.eof())
   {
   getline(fp1,buffer);
   l++;
   //cout<<"value of l is : "<<l<<endl;
   j=fp1.tellp();
   j=j-buffer.size();
   /*cout<<"value of i : "<<i<<endl<<"value of j : "<<j<<endl;*/
   if(j==i)
   {
       //cout<<"inside if"<<endl;
       continue;
   }
   else
   {
       //fp2.seekp(0,ios::beg);
       //int t=fp2.tellp();
      // cout<<"inside else at pos : "<<t<<endl;
       fp2<<buffer;
       fp2<<endl;
   }
   }
   l=l-2;
   //cout<<"value of l is : "<<l<<endl;
   fp1.close();
   fp2.close();
   fp1.open("data.txt",ios::out);
   fp1.close();
   fp1.open("data.txt",ios::out|ios::app);
   fp2.open("tempdata.txt",ios::in);
   fp3.open("inde.txt",ios::out);
   fp3.close();
   while(!fp2.eof())
   {
       i=0;
       if(l==0)
           break;
       getline(fp2,buffer);
       fp1<<buffer;
       fp1<<endl;
       l--;
       usn1.clear();
       while(buffer[i]!='|')
    {
	usn1+=buffer[i];
	i++;
    }
       siz1=buffer.size();
       loc1=fp1.tellp();
       pos1=loc1-siz1;
       f.insert(usn1,pos1);
       }
  // indrem(key);
  // cout<<"back to rem function"<<endl;
   fp1.close();
  // cout<<"fp1 closed"<<endl;
   fp2.close();
}
/*void indf :: indrem(string key)
{
    int l=0;
    fstream fp1,fp2;
    string buffer;
    fp1.open("inde.txt",ios::in);
    fp2.open("tempinde.txt",ios::out);
    fp2.close();
    fp2.open("tempinde.txt",ios::out|ios::app);
    while(!fp1.eof())
    {
        getline(fp1,buffer);
        l++;
        int k=key.size();
        string sub=buffer.substr(0,k);
        if(key==sub)
        {
           continue; 
        }
        else
        {
           fp2<<buffer;
           fp2<<endl;
        }
    }
    l=l-2;
    fp1.close();
    fp2.close();
    //cout<<"still remove"<<endl;
    fp1.open("inde.txt",ios::out);
    fp1.close();
    fp1.open("inde.txt",ios::out|ios::app);
    fp2.open("tempinde.txt",ios::in);
    while(!fp2.eof())
    {
        if(l==0)
            break;
        getline(fp2,buffer);
        fp1<<buffer;
        fp1<<endl;
        l--;
    }
    fp1.close();
   // cout<<"fp1 close"<<endl;
    fp2.close();
}*/
int main()
{
    int choice,i,k;
    string buffer,key;
    student s;
    file f;
    indf ind;
    while(1)
    {
    cout<<"1) add\n2) search\n3)delete\n------------\nEnter your choice : ";
    cin>>choice;
    cout<<endl;
    switch(choice)
    {
        case 1:
        {
           key=s.read();
           buffer=s.pack();
           f.write(buffer);
           i=f.pos;
           ind.insert(key,i);
        }
        break;
        case 2:
        {
            cout<<"enter the usn to be searched :";
            cin>>key;
            k=ind.search(key);
            i=ind.pos;
            i=i-1;
            f.unpack(i);
        }
        break;
        case 3:
        {
            cout<<"enter the usn to be removed : ";
            cin>>key;
            cout<<endl;
            k=ind.search(key);
            if(k==-1)
                exit(0);
            ind.rem(key);
        }
        break;
        default : cout<<"invalid option"<<endl;
    }
    cout<<"enter 0 to exit else 1 to continue : ";
    cin>>choice;
    if(choice == 0)
        exit(0);
    else
        continue;
    }
}
