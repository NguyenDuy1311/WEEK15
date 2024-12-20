#include<iostream>

using namespace std;


struct Node 
{
    int chapter; 
    int page; 
    int sec; 
    int subs; 
    Node* L; 
    Node* R;

    Node(int c, int p, int s, int sub)
    {
        chapter = c;
        page = p;
        sec = s;
        subs = sub;
        L = NULL;
        R = NULL;
    }
};

int IS_EMPTY(Node* root)
{
    return root == NULL;
}

Node* MAKE_Node(int c, int p, int s, int subs)
{
    Node* ptr = new Node(c, p, s, subs);
    return ptr;
}

Node* INSERT(Node* root, int c, int p, int s, int subs) 
{
    if (root == NULL) return MAKE_Node(c, p, s, subs);

    if (c < root->chapter) root->L = INSERT(root->L, c, p, s, subs);
    else if (c > root->chapter) root->R = INSERT(root->R, c, p, s, subs);

    return root;
}

void NUM_OF_CHAP(Node* root)
{
    if(IS_EMPTY(root)) cout << "0 chapters";
    if(IS_EMPTY(root->R))
    {
        if(root->chapter == 1) cout << "1 chapter";
        else cout << root->chapter << " chapters";
    }
    else NUM_OF_CHAP(root->R);
}

int MAX_LEN(Node* root, int &longest_chap)
{
    if(IS_EMPTY(root)) return 0;

    int max = 0;
    if(root->page > max) 
    {
        max = root->page;
        longest_chap = root->chapter;
    }
    MAX_LEN(root->L, longest_chap);
    MAX_LEN(root->R, longest_chap);

    return longest_chap;
}

void FIND(Node* root, int chapter)
{
    if(IS_EMPTY(root)) 
    {
        cout << "EMPTY !!!" << endl;
        return;
    }
    if(chapter == root->chapter) cout << "Found!" << endl;
    else FIND(root->R, chapter);
}

void CHANGE(Node* root, int del_chapter) 
{
    if (root == NULL) return; 

    if (root->chapter > del_chapter) 
    {
        root->chapter--;
    }

    CHANGE(root->L, del_chapter);
    CHANGE(root->R, del_chapter);
}

void DEL1(Node* root, int c)
{
    Node* p1;
    int del_chapter;
    if(c == root->R->chapter)
    {
        p1 = root->R;
        if(!IS_EMPTY(root->R->R)) root->R = root->R->R;
        del_chapter = p1->chapter;
        delete p1;
    }
    CHANGE(root, del_chapter);
}   

void DEL(Node* root, int c)
{
    if(c == root->chapter)
    {
        root = root->R;
        delete root->R;
    }
    DEL1(root, c);
}

void PREFIX(Node* root)
{
    if(IS_EMPTY(root)) return;
    cout << "Chapter: " << root->chapter << "Page: " << root->page << " sec: " << root->sec << " subs: " << root->subs;
    cout << endl;
    PREFIX(root->L);
    PREFIX(root->R); 
}

int main()
{
    Node* root = NULL;

    int chapter;
    int page;
    int sec;
    int subs;

    for(int i = 0; i < 3; i++)
    {
        cout << " Chapter: ";
        cin >> chapter;
        cout << " Page: ";
        cin >> page;
        cout << " sec: ";
        cin >> sec;
        cout << " subs: ";
        cin >> subs;

        root = INSERT(root, chapter, page, sec, subs);
    }

    PREFIX(root); cout << endl;

    NUM_OF_CHAP(root); cout << endl;

    int longest_chap;
    longest_chap = MAX_LEN(root, longest_chap);
    cout << longest_chap << endl;
    FIND(root, 2); cout << endl;
    DEL(root, 2);


    return 0;
}