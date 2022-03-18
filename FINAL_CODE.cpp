#include <bits/stdc++.h>
using namespace std;

struct trienode{
    bool is_word;
    trienode* child[26];

};

trienode* get_new_node()
{
    trienode* temp = new trienode;
    temp->is_word = false;

    for(int i=0;i<26;i++)
    {
        temp->child[i] = NULL;
    }

    return temp;
}

void insert(trienode* root,string key)
{
    trienode* temp = root;
    for(int i=0;i<(int)key.length();i++)
    {
        int ind = int(key[i])-'a';
        if( temp->child[ind] == NULL )
        {
            temp->child[ind] = get_new_node();
        }
        temp = temp->child[ind];
    }

    temp->is_word = true;
}

bool search(trienode* root,string key)
{
    if( root == NULL) return  false;
    trienode* temp = root;

    for(int i=0;i<(int)key.length();i++)
    {
        int ind = int(key[i])-'a';
        if( temp->child[ind] == NULL ) return false;
        temp = temp->child[ind];
    }

    return temp->is_word;

}

trienode* helper(trienode* root,string key,int ind)
{

    if(root==NULL) return NULL;


    bool isempty = true;
    for(int i=0;i<26;i++)
    {
        if(root->child[i] != NULL)
        {
            isempty = false;
            break;
        }
    }

    if(ind == key.length())
    {

        if(isempty==false)
        {
            root->is_word = false;

        }
        else
        {
            delete(root);
            root = NULL;
        }

        return root;

    }
    int pos = int(key[ind])-'a';
    root->child[pos] = helper(root->child[pos],key,ind+1);

    isempty = true;
    for(int i=0;i<26;i++)
    {
        if(root->child[i] != NULL)
        {
            isempty = false;
            break;
        }
    }



    if( isempty && root->is_word == false )
    {
        delete(root);
        root = NULL;
    }

    return root;
}


trienode* delete_key(trienode* root , string key)
{

    if(root == NULL) return root;
    if(key == "") return root;

     root = helper( root,key,0 );
    return root;
}

void find_all_words( trienode* root,string key,vector<string>&all_words)
{
	if(root==NULL) return ;
	trienode* temp = root;

     for(int i=0;i<(int)key.size();i++)
     {
     	int ind = int(key[i])-'a';
     	if( temp->child[ind] == NULL ) return ;

     	temp = temp->child[ind];
     }


     queue<pair<trienode*,string> > q;
     q.push(make_pair(temp,key));
     string this_word;
     while(!q.empty())
     {
     	temp = q.front().first;
     	this_word = q.front().second;

     	if(temp->is_word) all_words.push_back( this_word );
     	q.pop();
     	for(int i=0;i<26;i++)
     	{
     		if( temp->child[i] !=NULL )
     		{
     			q.push( make_pair( temp->child[i] , this_word+char(i+int('a')) ) );
     		}
     	}
     }

}

void auto_complete(trienode* root, string key)
{
	if(key.size() == 0) return ;
	vector<string> all_words;

	find_all_words(root,key,all_words);
	if( all_words.size() == 0  )
	{
		cout<<"There are no suggestions for the word you have given !!"<<'\n';
		return ;
	}

	cout<<"There are "<<all_words.size()<<" suggestions for the word you have entered \n "<<key<<'\n';
	for(int i=0;i<(int)all_words.size();i++){
		cout<<all_words[i]<<endl;
	}

	return ;
}

int main()
{

    while(1)
    {
     char chr;
     system("CLS");
	 system("color F0");
	 fstream my_file;
	 my_file.open("words.txt",ios::in);
	 if(!my_file)
     {
        cout<<"Error in opening file!!!";
     }

    else
    {
	vector<string> dict;
	string key;

	while (my_file >> key) {

	    dict.push_back(key);
	}
	trienode* root = get_new_node();
	for(int i=0;i<dict.size();i++)
	{
	   insert(root,dict[i]);
     }
     cout<<"\n\n\t\t\t\tAUTO SUGGESSION USING TRIE ";
    cout<<"\n\nEnter the word you want suggessions for :"<<'\n';
    cin>>key;
    char arr[key.length()+1];
    strcpy(arr,key.c_str());

    for (int i =0;i<key.length();i++)
     {
        if (isdigit(arr[i]) == 0)
           {
               continue;
            }
         else{
            cout<<"\tINVALID INPUT  DIGITS NOT ALLOWED !!! ";
            goto end ;
           }
    }

    for (int i = 0; i < key.length(); i++)
  	{
  		key[i] = tolower(key[i]);
  	}
    auto_complete(root,key);
    }
    end:
     cout<<"\n\nEnter q to exit and any other character to continue : ";
     cin>>chr;
     if(chr=='q')
        break;

    }

	return 0;
}
