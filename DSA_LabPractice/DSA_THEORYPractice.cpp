#include <iostream>
using namespace std;

template <class T>

class Stack
{

	private:
	
	int size;
	int top;
	T* arr;

	public:

	Stack(int s)
	{

		size=s;
		top=-1;
		arr=new T[size];
	}

	bool isFull()
	{

		if(top==size-1)
			return true;

		return false;

	}

	bool isEmpty()
	{

		if(top==-1)
			return true;

		return false;

	}


	void push( T value)
	{

		if(!isFull())
			arr[++top]=value;

		else
			cout<<"Sorry The Stack Is Full...."<<endl;
	}

	T pop()
	{

		return arr[top--];
		
	}

	T returnTop()  // this will only return the top element without decrementing the top
	{

		return arr[top];

	}

};

template <class T>
class BNode {
public:
    T data;
    BNode<T>* left;
    BNode<T>* right;

    BNode(T d) {
        data = d;
        left = nullptr;
        right = nullptr;
    }
};

template <class t>
class BST
{
    BNode<t> * root;
    public:
    BST()
    {
        root=NULL;
    }

    void insert(t val)
    {
        BNode<t>* temp=new BNode<t>(val);
        if(root==NULL)
            root=temp;
        else
        {
            BNode<t>* pcurr=NULL;
            BNode<t>* curr=root;
            while(curr!=NULL)
            {
                pcurr=curr;
                if(val<curr->data)
                    curr=curr->left;
                else    
                    curr=curr->right;
            }
            if(val<pcurr->data)
                    pcurr->left=temp;
                else    
                    pcurr->right=temp;
    
        }
    }

    void inorder(BNode<int>* curr)
    {
        if(curr != NULL)
        {
            inorder(curr->left);
            cout<<curr->data<<" ";
            inorder(curr->right);
        }
    }

    void preorder(BNode<int>* curr)
    {
        if(curr != NULL)
        {
            cout<<curr->data<<" ";
            preorder(curr->left);
            preorder(curr->right);
        }
    }

    void postorder(BNode<int>* curr)
    {
        if(curr != NULL)
        {
            postorder(curr->left);
            postorder(curr->right);
            cout<<curr->data<<" ";
        }
    }

    BNode<t>* getRoot()
    {
        return root;
    }

    void ValuesIntoStack(BNode<int>* curr, int arr[], int arr2[], int &index)
    {
        if(curr != NULL)
        {
            ValuesIntoStack(curr->left,arr, arr2, index);
            //cout<<curr->data<<" ";
            arr[index++] = curr->data;
            ValuesIntoStack(curr->right,arr , arr2, index);
        }
    }

    void Sort(int arr[], int index)
    {
        for(int i = 0; i< index-1; i++)
        {
            for(int j = 0; j<index-i-1; j++)
            {
                if(arr[j] > arr[j+1])
                {
                    int temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                }
            }
        }
    }

    void swapNode(BNode<int>* curr, int x, int y)
    {
        if(curr != NULL)
        {
            swapNode(curr->left,  x,  y);
            if(curr->data == x)
            {
                curr->data = y;
            }
            else if(curr->data == y)
            {
                curr->data = x;
            }
            swapNode(curr->right, x,  y);
        }
    }
};



int main()
{
    BST<int> tree;
    int arr[20], arr2[20];
    BNode<int>* root = new BNode<int> (50);
    root->left = new BNode<int>(30);
    root->right = new BNode<int>(70);
    root->left->left = new BNode<int>(20);
    root->right->left = new BNode<int>(60);
    root->right->right = new BNode<int>(55);
    root->right->left->left = new BNode<int>(80);
    cout<<"Before: ";
    Stack<int> s(100);
    tree.inorder(root);
    cout<<endl;
    
    int size = 0;
    int count = 0;
    tree.ValuesIntoStack(root,arr, arr2, size);

    int x = 0, y = 0;

    for(int i = 0; i< size; i++)
    {
         if(arr[i] != arr2[i])
        {
            if(x == -1)
            {
                x = arr[i];
                y = arr2[i];
            }
            else
            {
                y = arr2[i];
            }
        }
    }

    tree.swapNode(root, x, y);
    cout<<"After: ";
    tree.inorder(root);
    cout<<endl;
    return 0;
}