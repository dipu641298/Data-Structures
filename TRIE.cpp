#include<bits/stdc++.h>
using namespace std;
#define FASTER ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

struct node{
    bool isEnd;
    int prefixCnt;
    struct node* child[30];
}*head;

void init()
{
    head = new node();
    head->prefixCnt = 0;
    head->isEnd = false;

}

void trie_insert(string s)
{
    node* current = head;
    current->prefixCnt++;
    for(int i=0; i<s.size(); i++){
        int letter = s[i]-'a';
        if(current->child[letter]==NULL){
            current->child[letter] = new node();
        }
        current->child[letter]->prefixCnt++;
        current = current->child[letter];
    }
    current->isEnd = true;
}

bool trie_search(string s)
{
    node* current = head;
    for(int i=0; i<s.size(); i++){
        if(current->child[s[i]-'a']==NULL){return false;}
        current = current->child[s[i]-'a'];
    }
    return current->isEnd;
}

bool trie_delete(string s)
{
    node* current = head;
    for(int i=0; i<s.size(); i++){
        if(current->child[s[i]-'a']==NULL){return false;}
        current = current->child[s[i]-'a'];
    }
    if(current->isEnd){
        current->prefixCnt--;
        if(current->prefixCnt==0){
            current->isEnd = false;
        }
        return true;
    }
}

int wordsWithPrefix(string s)
{
    node* current = head;
    for(int i=0; i<s.size(); i++){
        if(current->child[s[i]-'a']==NULL){return 0;}
        current = current->child[s[i]-'a'];
    }
    return current->prefixCnt;
}

int main()
{
    FASTER
    int q,type;
    cin >> q;
    string s;
    init();
    for(int i=0; i<q; i++){
        cin >> type >> s;
        if(type==1){trie_insert(s);}
        else if(type==2){
            bool x = trie_search(s);
            if(x){cout << "Found in the trie" << endl;}
            else{cout << "Not found in the trie" << endl;}
        }
        else if(type==3){
            bool x = trie_delete(s);
            if(x){cout << "Deleted from the trie" << endl;}
            else{cout << "Not found in the trie" << endl;}
        }
    }

    return 0;
}
