#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "queue.h"


typedef struct tnode
{
  void *dp;
  struct tnode *lc;
  struct tnode *rc;
}TNODE;

typedef struct btree
{
  TNODE *root;
  int  count;
  bool(*compare)(void *, void *);
  void (*print)(void*);
}btree;

btree* createtree(bool(*compare)(void *, void *),void (*print)(void*))
{
  btree* t = (btree*)malloc(sizeof(btree));
  if(!t)
    return NULL;
  t->root = NULL;
  t->count = 0;
  t->compare = compare;
  t->print = print;
  return t;
}

bool insert_tree_node(btree *t, void *dp)
{
  TNODE *newnode, *traverse, *parent;
  int ch;
  traverse = t->root;
  while(traverse)
    {
      printf("Enter 1 for left and 2 for right: ");
      scanf("%d", &ch);
      parent = traverse;
      if(ch == 1)
        traverse = traverse->lc;
      else if(ch == 2)
        traverse = traverse->rc;
      else
        printf("Invalid choice\n");
    }
  newnode = (TNODE*)malloc(sizeof(TNODE));
  if(!newnode)
    return false;
  newnode->dp = dp;
  newnode->lc = NULL;
  newnode->rc = NULL;
  if(!t->root)
    t->root = newnode;
  else if(ch == 1)
    parent->lc = newnode;
  else if(ch == 2)
    parent->rc = newnode;
  t->count++;
  return true;
}

bool find_key(btree *t, TNODE *root, void *pkey)
{
  if(root)
  {
    if(t->compare(root->dp, pkey))
      return true;
    if(root->lc)
    {
      if(find_key(t, root->lc, pkey))
        return true;
    }
    if(root->rc)
    {
      if(find_key(t, root->rc, pkey))
        return true;
    }
  }
  return false;
}
/*
void find_key_freq(btree *t,TNODE *root, int *freq, void *pkey)
{
  if(root)
  {
    if(t->compare(root->dp, pkey))
      (*freq)++;
    if(root->lc)
      find_key_freq(t, root->lc,freq, pkey);
    if(root->rc)
      find_key_freq(t, root->rc,freq, pkey);
  }
}

void preorder_traversal(btree *t, TNODE *root)
{
  if(root)
  {
    t->print(root->dp);
    if(root->lc)
      preorder_traversal(t, root->lc);
    if(root->rc)
      preorder_traversal(t, root->rc);
  }
}

void inorder_traversal(btree *t, TNODE *root)
{
  if(root)
  {
    if(root->lc)
      inorder_traversal(t, root->lc);
    t->print(root->dp);
    if(root->rc)
      inorder_traversal(t, root->rc);
  }
}

void postorder_traversal(btree *t, TNODE *root)
{
  if(root)
  {
    if(root->lc)
      postorder_traversal(t, root->lc);
    if(root->rc)
      postorder_traversal(t, root->rc);
    t->print(root->dp);
  }
}
*/
/*void no_leaf_node(TNODE *root, int *leaf)
{
  if(root)
  {
    if(!root->lc && !root->rc)
      (*leaf)++;
    if(root->lc)
      no_leaf_node(root->lc, leaf);
    if(root->rc)
      no_leaf_node(root->rc, leaf);
  }
}

int find_tree_height(TNODE *root)
{
  int hl,hr;
  if(root)
  {
    hl = find_tree_height(root->lc);
    hr = find_tree_height(root->rc);
    if(hl > hr)
      return hl + 1;
    else
      return hr + 1;
  }
  return 0;
}

bool  tree_balanced(TNODE *root)
{
  if(root)
  {
    int b = find_tree_height(root->lc) - find_tree_height(root->rc);
    if(b > 1 || b < -1)
      return false;
    return true;
  }
  return true;
}

void key_parent(btree *t, TNODE *root, TNODE **parent, void *pkey)
{
  if(root)
  {
    if(t->compare(root->dp, pkey))
    {
      *parent = root;
      return;
    }
    if(root->lc)
    {
      key_parent(t, root->lc, parent, pkey);
      if(root->lc == *parent && t->compare(root->lc->dp, pkey))
        *parent = root;
    }
    if(root->rc)
    {
      key_parent(t, root->rc, parent, pkey);
      if(root->rc == *parent && t->compare(root->rc->dp, pkey))
        *parent = root;
    }
  }
}

void breath_first_traversal(btree *t)
{
  TNODE *curnode;
  QUEUE *q = createqueue();
  curnode =  t->root;
  while(curnode)
    {
      t->print(curnode->dp);
      if(curnode->lc)
        if(enqueue(q, curnode->lc))
          ;
      if(curnode->rc)
        if(enqueue(q, curnode->rc))
          ;
      if(!qempty(q))
        curnode = (TNODE*)dequeue(q);
      else
        curnode = NULL;
    }
}
*/
void delete_node(TNODE *root)
{
  if(root)
  {
    delete_node(root->lc);
    delete_node(root->rc);
    free(root->dp);
    free(root);
  }
}
bool destroy_btree(btree *t)
{
  TNODE *temp;
  if(t)
  {
    temp = t->root;
    delete_node(temp);
    free(t);
    return true;
  }
  return false;
}

/*
TNODE* create_new_node(TNODE *root)
{
  TNODE *newnode;
  newnode = (TNODE*)malloc(sizeof(TNODE));
  if(newnode)
  {
    newnode->dp = root->dp;
    newnode->lc = create_new_node(root->lc);
    newnode->rc = create_new_node(root->rc);
    return newnode;
  }
  return NULL;
}

btree* copy_binary_tree(btree *t)
{
  btree* newtree = (btree*)malloc(sizeof(btree));
  if(newtree)
  {
    newtree->root = create_new_node(t->root);
    newtree->count = t->count;
    newtree->compare = t->compare;
    newtree->print = t->print;
    return newtree;
  }
  return NULL;
}
//main!!!!

bool compare(void *dp1, void *dp2)
{
  if(*(int *)dp1 == *(int *)dp2)
    return true;
  return false;
}

void print(void *dp)
{
  printf("%d\t", *(int *)dp);
}

int main()
{
  btree *t = createtree(compare, print);
  btree* newt;
  if(!t)
    return 1;
  int *din,ch,leaf=0,freq=0;
  TNODE *p;
  while(1)
    {
      printf("Enter you choice :\n 1-insert \n2-search \n3-freq of key \n4-no. of nodes \n5-tree traversal \n6-Balanced tree \n7-parent of key \n8-copy tree \n9-Destroy tree\n");
      scanf("%d", &ch);
      switch(ch)
        {
          case 1:
            din = (int *)malloc(sizeof(int));
            if(!din)
              break;
            printf("Enter the data to be inserted: ");
            scanf("%d", din);
            if(insert_tree_node(t, din))
              printf("Inserted\n");
            else
              printf("Not inserted\n");
            break;
          case 2:
            printf("Enter the data to be searched: ");
            scanf("%d", &ch);
            if(find_key(t, t->root, &ch))
              printf("Found\n");
            else
              printf("Not found\n");
            break;
          case 3:
            printf("Enter the key to be searched: ");
            scanf("%d", &ch);
            find_key_freq(t, t->root, &freq, &ch);
            printf("Frequency of key is: %d\n",freq);
            break;
          case 4:
            leaf = 0;
            no_leaf_node(t->root, &leaf);
            printf("Total No. of nodes : %d\n",t->count);
            printf("No. of leaf nodes are: %d\n", leaf);
            printf("Total No. internal of nodes : %d\n",t->count-(leaf));
            break;
          case 5:
            if(t->count == 0)
            {
              printf( "Tree is empty\n");
              break;
            }
            printf("Enter your choice :\n 1-preorder \n2-inorder \n3-postorder\n");
            scanf("%d", &ch);
            switch(ch)
              {
                case 1:
                  preorder_traversal(t, t->root);
                  break;
                case 2:
                  inorder_traversal(t, t->root);
                  break;
                case 3:
                  postorder_traversal(t, t->root);
                  break;
                default:
                  printf("Invalid choice\n");
              }
          break;
          case 6:
            if(tree_balanced(t->root))
              printf("Tree is balanced\n");
            else
              printf("Tree is not balanced\n");
            break;
          case 7:
            printf("Enter the key to be searched: ");
            scanf("%d", &ch);
            key_parent(t, t->root, &p, &ch);
            if(p)
              printf("Parent of key is: %d\n", *(int *)p->dp);
            else
              printf("Parent of key doesn't exists\n");
            break;
          case 8:
            newt = (btree*)copy_binary_tree(t);
            if(newt)
              printf("Tree copied\n");
            else
              printf("Tree not copied\n");
            break;
          case 9:
            if(destroy_btree(t))
              printf("Tree destroyed\n");
            else
              printf("Tree not destroyed\n");
            return 0;  
        }
    }
  return 0;
}
*/
typedef struct student
{
	char name[10];
	int roll;
	char usn[10];
}STUD;

// Function to print student details
void print(void *dp) {
    STUD *s = (STUD*)dp;
    printf("Name: %s\n", s->name);
    printf("Roll number: %d\n", s->roll);
    printf("USN: %s\n", s->usn);
}
bool compare(void *a, void *b) {
    STUD *p = (STUD *)a;
    STUD *q = (STUD *)b;
    return (p->roll == q->roll);
}

int main()
{
	STUD *s,*q;
	s=(STUD*)malloc(sizeof(STUD));
	q=(STUD*)malloc(sizeof(STUD));
	btree *t=createtree(compare,print);
	printf("enter First student details:");
	printf("enter the name:");
	scanf("%s",s->name);
	printf("enter the name:");
	scanf("%s",s->usn);
	printf("enter the name:");
	scanf("%d",&s->roll);
	insert_tree_node(t,s);
	printf("enter second student details:");
	printf("enter the name:");
	scanf("%s",q->name);
	printf("enter the name:");
	scanf("%s",q->usn);
	printf("enter the name:");
	scanf("%d",&q->roll);
	insert_tree_node(t,q);
	int ch;
    printf("Enter the roll number to search: ");
    scanf("%d", &ch);
	if(find_key(t,t->root,&ch))
		printf("found");
	else
		printf("Not found");
	destroy_btree(t);
	return 0;
}
