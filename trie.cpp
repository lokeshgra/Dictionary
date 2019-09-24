#include<bits/stdc++.h>
using namespace std;
#define alfa 26
struct node
{
	node *child[alfa];
	string word;
	string meaning;
	bool eof;
};
node* getnode()
{
	node *newnode = new node;
	newnode->eof=false;
	newnode->meaning="";
	newnode->word="";
	for (int i = 0; i < alfa; i++)
        newnode->child[i] = NULL;
	return newnode;
}
void insert(node *root,string key,string str)
{
//	cout<<"IN Insert function\n";
//	if(root)
//		cout<<"Root exists\n";
//	cout<<key<<" "<<str<<"\n";
	node *temp=root;
	for(int i=0;i<key.length();i++)
	{
		int index=key[i]-'a';
//		if(temp->child[index]){
//			cout<<key[i]<<" "<<"Child exisits\n";
//		}
		if(!(temp->child[index]))		
	     temp->child[index]=getnode();
	    temp=temp->child[index];
	}
	temp->meaning= str;
	temp->word=key;
	temp->eof=true;
	
}
bool search(node *root,string key)
{
	node *temp=root;
	if(!temp)return false;
	for(int i=0;i<key.length();i++)
	{
		int index=key[i]-'a';
		if(!temp->child[index])
		return false;
	  temp=temp->child[index];	
	}
	 if(temp&&temp->eof)
	 {
	 	cout<<temp->meaning<<endl;
	 	return true;
	 }
	 else return false;
}
bool islastnode(node *root)
{
	for(int i=0;i<alfa;i++)
	{
		if(root->child[i])
		return 0;
	}
	return 1;
}
void suggest(node *root,string query)
{
	if(root->eof)
	{
		cout<<query<<endl;
	}
	if(islastnode(root))
	return;
	for(int i=0;i<alfa;i++)
	{
		if(root->child[i])
		{
			query.push_back('a'+i);
			suggest(root->child[i],query);
		}
	}
}
int autosuggest(node * root,string query)
{
	node *temp=root;
	int i;
	int n=query.length();
	for(i=0;i<n;i++)
	{
		int index=query[i]-'a';
		if(!temp->child[index])
		return 0;
		temp=temp->child[index];
	}
	bool isword=temp->eof;
	bool islast=islastnode(temp);
	if(isword&&islast)
	{
		cout<<query<<endl;
		return -1;
	}
	if(!islast)
	{
		//string prefix=query;
		suggest(temp,query);
		return 1;
	}
	
}
node *root=getnode();
void store()
{
	ifstream fin;
	fin.open("dictionary");
	string word;
	string meaning;
	if(!fin)
	{
		cout<<"file not open\n";
		exit(0);
	}
	char ch;
	while(fin.get()!='{');
	
	while(true)
	{
	
		while(fin.get()!='"');
		
		getline(fin,word,'"');
		
		while(fin.get()!='"');
		meaning="";
		while(true)
		{
			fin.get(ch);
			if(ch=='"')
			{
				if(meaning.at(meaning.size()-1)=='\\')
				{
					meaning=meaning.substr(0,meaning.size()-1);
					meaning+=ch;
				}
				else
				break;
			}
			else
			meaning+=ch;	
		}
//		cout<<word<<" "<<meaning<<"\n";
		insert(root, word,meaning);
//		cout<<"HI\n";
		do{
			fin.get(ch);
		}while(ch == ' ' || ch == '\n' ||  ch == '\t');
		cout<<word<<endl;
		if(ch ==',' )
			continue;
		else if( ch =='}' )
			{
				//cout<<"lokesh";
				break;
			}
	}
	fin.close();
}
int main()
{
	cout<<"hello";
	store(); 
	cout<<"hello";
	  //cout<<search(root,"self")<<endl;
//    cout<<search(root,"the")<<endl;
//   int co=autosuggest(root,"the");
//    if(co==-1)
//    cout<<"no other string found\n";
//    else if(!co)
//    cout<<"no string found\n";
	return 0;
}
