/*Header Files*/
#include<stdio.h>
#include<iostream>
using namespace std;
/* Structure for B tree */ 
struct BTree
{ 
    int *key;  // data
    BTree **child;  //child node pointers 
    bool leaf; //True- if it’s a leaf node
    int counter; // maintains the number of keys
}*root = NULL, *p = NULL; // pointers to root nodes
/* Whenever the node becomes full and needs an insertion Split_child operation need to be performed, where a particular node need to be divided to accommodate new key*/
int split_child(BTree *p, int i)
{
    int j, mid;
    BTree *p1, *p2, *p3;
p2= new BTree; //creating a new p2 btree empty leaf node
   p2->key = new int[5];
    p2->child = new BTree *[6];
   p2->leaf = true;
  p2->counter = 0;
    for (i = 0; i < 6; i++)
    {
        p2->child[i] = NULL;
    }   
    if (i == -1)
    {
        mid = p->key[2];
        p->key[2] = 0;
        p->counter--;
       p1= new BTree;
   p1->key = new int[5];
    p1->child = new BTree *[6];
  p1->counter = 0;
    for (i = 0; i < 6; i++)
    {
        p1->child[i] = NULL;
    }

       p1->leaf = false;
        p->leaf = true;
        for (j = 3; j < 5; j++)
        {
            p2->key[j - 3] = p->key[j];
           p2->child[j - 3] = p->child[j];
            p2->counter++;
            p->key[j] = 0;
            p->counter--;
        }
        for(j = 0; j < 6; j++)
        {
            p->child[j] = NULL;
        }
       p1->key[0] = mid;
        p1->child[p1->counter] = p;
        p1->child[p1->counter + 1] = p2;
        p1->counter++;
        root = p1;
    }
    else
    {
        p3 = p->child[i];
        mid = p3->key[2];
        p3->key[2] = 0;
        p3->counter--;
        for (j = 3; j < 5; j++)
        {
            p2->key[j - 3] = p3->key[j];
            p2->counter++;
           p3->key[j] = 0;
            p3->counter--;
        }
        p->child[i + 1] = p3;
        p->child[i + 1] = p2;
    }
    return mid;
}
/* sort method- swapping done while insertion of elements*/
void sort(int *k, int con)
{
    int i, j, temp;
    for (i = 0; i < con; i++)
    {
        for (j = i; j <= con; j++)
        {
            if (k[i] > k[j])
            {
                temp = k[i];
                k[i] = k[j];
                k[j] = temp;
            }
        }
    }
}
/* Insertion of elements considering if inserting element is first element( root) or another leaf node*/
void insertion(int ele)
{
    int i, temp;
    p = root;
    if (p == NULL)
    {
        root= new BTree;
   root->key = new int[5];
    root->child = new BTree *[6];
    root->leaf = true;
   root->counter = 0;
    for (i = 0; i < 6; i++)
    {
        root->child[i] = NULL;
    }
        p = root;
    }
    else
    {
        if (p->leaf == true && p->counter == 5)
        {
            temp = split_child(p, -1);
            p = root;
            for (i = 0; i < (p->counter); i++)
            {
                if ((ele > p->key[i]) && (ele < p->key[i + 1]))
                {
                    i++;
                    break;
                }
                else if (ele < p->key[0])
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
            p = p->child[i];
        }
        else
        {
            while (p->leaf == false)
            {
            for (i = 0; i < (p->counter); i++)
            {
                if ((ele> p->key[i]) && (ele < p->key[i + 1]))
                {
                    i++;
                    break;
                }
                else if (ele < p->key[0])
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
                if ((p->child[i])->counter == 5)
                {
                    temp = split_child(p, i);
                    p->key[p->counter] = temp;
                    p->counter++;
                    continue;
                }
                else
                {
                    p = p->child[i];
                }
            }
        }
    }
    p->key[p->counter] = ele;
    sort(p->key, p->counter);
    p->counter++;
}
/* Traverse through the tree- the increasing order of entered keys*/
void traversal(BTree *p)
{
    cout<<endl;
    int i;
    for (i = 0; i < p->counter; i++)
    {
        if (p->leaf == false)
        {
            traversal(p->child[i]);
        }
        cout << " " << p->key[i];
    }
    if (p->leaf == false)
    {
        traversal(p->child[i]);
    }
    cout<<endl;
}
/* user provided option among entering the elements to build the tree, traversal and exit from program*/
int main()
{
int Val,no,element,i;
while(1)
{
cout<<"***********B-Tree***********\n";
cout<<"Menu\n";
cout<<"1.construction of B tree/ Insertion\n";
cout<<"2. Traversal of B tree\n";
cout<<"3.exit";
cin>> Val;
switch(Val)
{
case 1: cout<<"enter the no of elements to be inserted\n";
              cin>> no;
    for(i = 0; i < no; i++)
    {
        cout<<"enter an element\n";
        cin>>element;
        insertion(element);
    }
break;
case 2:  cout<<"tree traversal\n";
traversal(root);
break;
default: exit(0);
}
}
}


