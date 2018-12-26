//C++ program to implement insertion and deletion for a binary tree
#include<iostream>
#include<queue>
#include<stdlib.h>

using namespace std;

struct Node
{
        int data;
        struct Node *left, *right;
};

struct Node *getNode(int data)
{
        struct Node *newNode = new Node;
        newNode->data = data;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
};

//function to insert a new node using level order traveral
struct Node *insert(struct Node *root, int data)
{

//empty tree
        if (root == NULL)
        {
                root = getNode(data);
                return root;
        }

//queue used to perform bfs
        queue<struct Node*> q;
        q.push(root);

//loop until the tree is not comletely traversed,i.e, the queue is not empty 
        while (!q.empty())
        {

//the front node is marked as visited
//hence we will have reference to the children of the visited node
//then it is popped out
                struct Node *root = q.front();
                q.pop();

//if the left child is NULL then insert new node there; else push it to the queue to search for the empty space
                if (root->left == NULL)
                {
                        root->left = getNode(data);
                        break;
                }
                else
                        q.push(root->left);

                if (root->right == NULL)
                {
                        root->right = getNode(data);
                        break;
                }
                else
                        q.push(root->right);
        }
        return root;
}

//function to delete the last(deepest and rightmost) element in the tree found during level order traversal
void deepestEle(struct Node *root,struct Node *current)
{
        queue <struct Node*> q;
        q.push(root);

        while (!q.empty())
        {
                root = q.front();
                q.pop();

//check the right child first since that would be the last element, if present
                if (root->right != NULL)
                {
                        if (root->right == current)
                        {

//set the references to that node as NULL, then delete it
                                root->right = NULL;
                                delete(current);
                                return;
                        }
                        else q.push(root->right);
                }
                if (root->left != NULL)
                {
                        if (root->left == current)
                        {
                                root->left = NULL;
                                delete(current);
                                return;
                        }
                        else q.push(root->left);
                }
        }
}

//function to delete node whose data is specified
//find the last node, delete that node after replacing the data of the node to be deleted in the binary tree
struct Node *del(struct Node *root,int data)
{
        queue<struct Node*> q;
        q.push(root);

//to_be_del is the node to be deleted, which has to be found
        struct Node *to_be_del = NULL;

//current node to find the last node using level order traversal
        struct Node *current;

        while (!q.empty())
        {
                current = q.front();
                q.pop();

                if (current->data == data)
                        to_be_del = current;

                if (current->left)
                        q.push(current->left);

                if (current->right)
                        q.push(current->right);
        }
//last node is found, replace the data of the node to be deleted with the last node's data
        to_be_del->data = current->data;
//call function to now delete the last node             
        deepestEle(root,current);
        return root;
}

//function to perform inorder traversal(left->data->right) to check your operations
void inorder(struct Node *root)
{

//tree is empty
        if (root == NULL)
                return;

        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
}

int main()
{
        struct Node *root = NULL;
        int choice,n;
        while (1)
        {
        cout<<"Enter the choice:\n 1.Insertion \n 2.Deletion \n 3.Inorder Traversal \n Any other.Exit \n";
        cin>>choice;
        switch(choice)
        {
                case 1: cout<<"Enter the number to be inserted: ";
                        cin>>n;
                        root = insert(root,n);
                        break;

                case 2: cout<<"Enter the node data to be deleted: ";
                        cin>>n;
                        root = del(root,n);
                        break;

                case 3: inorder(root);
                        break;

                default: exit(0);
        }
        }
        return 0;
}

                                                                                                                                                                                          
