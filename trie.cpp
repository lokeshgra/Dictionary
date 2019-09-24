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
bool is_alpha(string word){
	
	for(int i=0;i<word.size();i++){
		if(word[i]<'a' || word[i]>'z')
			return false;
	}
	return true;
}
void insert(node *root,string key,string str)
{

	node *temp=root;
	for(int i=0;i<key.length();i++)
	{
		int index=key[i]-'a';
		if(!(temp->child[index]))		
	     temp->child[index]=getnode();
	    temp=temp->child[index];
	}
	temp->meaning= str;
	temp->word=key;
	temp->eof=true;
	
}
bool search1(node *root,string key)
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
int min(int x,int y)
{
	if(x<y)
	return x;
	else
	return y;
}
int minelement(int *row,int size)
{
	int m=row[0];
	for(int i=0;i<size;i++)
	{
		if(row[i]<m)
		m=row[i];
	}
	return m;
}
void searchrec(node *temp, char letter, string word, int *previousrow, string result[], int dist, int &count) 
{
	int size = word.length()+1;
    int *currentrow = new int[size];
    currentrow[0] = previousrow[0] + 1;
    int insertcost,deletecost,replacecost;
    for(int i=1;i<size;i++)
    {
    	insertcost=currentrow[i-1]+1;
    	deletecost=previousrow[i]+1;
    	if(word[i-1]==letter)
    	{
    		replacecost=previousrow[i-1];
		}
		else
		replacecost=previousrow[i-1]+1;
		currentrow[i]=min(min(insertcost,deletecost),replacecost);
	}
	if(currentrow[size-1]==dist&&temp->eof)
	{
		result[count++]=temp->word;
	}
	if(minelement(currentrow,size)<=dist)
	{
		for(int i=0;i<alfa;i++)
		{
			if(temp->child[i])
			{
				searchrec(temp->child[i],i+'a',word,currentrow,result,dist,count);
			}
		}
	}

}
void search(node *root,string word,int dist,string result[],int &count)
{
	int size=word.length();
	int *currentrow = new int[size+1];
	for(int i=0;i<=size;i++)
	{
		currentrow[i]=i;
	}
	for(int i=0;i<alfa;i++)
	{
		if(root->child[i])
		{
			searchrec(root->child[i], i+'a', word, currentrow, result, dist, count);
		}
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

		if(is_alpha(word))
		insert(root, word,meaning);

		do{
			fin.get(ch);
		}while(ch == ' ' || ch == '\n' ||  ch == '\t');
		
		if(ch ==',' )
			continue;
		else if( ch =='}' )
			{
				
				break;
			}
	}
	fin.close();
}
int main()
{
	
	store(); 
	string word;
	cin>>word;
	if(!search1(root,word))
	{
		int count=0;
		int dist=0;
		string result[1000];
		while(count<10){
				dist++;
				
				search(root,word,dist,result,count);
				
			}
			for(int i=0;i<10;i++)
				cout<<result[i]<<endl;		
	}
	return 0;
}
