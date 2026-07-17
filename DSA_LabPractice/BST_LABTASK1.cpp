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
		

// ===================== DNode Class =====================
template <class T>
class DNode {
public:
    T data;
    DNode* prev;
    DNode* next;

    DNode(T val) : data(val), prev(nullptr), next(nullptr) {}
};

// ================= DoublyLinkedList Class =================
template <class T>
class DoublyLinkedList {
private:
    DNode<T>* head;
    DNode<T>* tail;

public:
    // Constructor
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    // Insert at End
    void insertEnd(T val) {
        DNode<T>* newNode = new DNode<T>(val);

        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    // Display Forward
    void displayForward() {
        DNode<T>* temp = head;

        cout << "Forward: ";
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Display Backward
    void displayBackward() {
        DNode<T>* temp = tail;

        cout << "Backward: ";
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << endl;
    }

    // Get Head
    DNode<T>* getHead() {
        return head;
    }

    // Get Tail
    DNode<T>* getTail() {
        return tail;
    }

    // Size of List
    int size() {
        int count = 0;
        DNode<T>* temp = head;

        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }

        return count;
    }

    // Destructor
    ~DoublyLinkedList() {
        DNode<T>* current = head;

        while (current != nullptr) {
            DNode<T>* nextNode = current->next;
            delete current;
            current = nextNode;
        }
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
    BNode<t>* search_rec(BNode<t>* curr,t target)
    {
        if(curr==NULL || curr->data==target)
            return curr;
        else
        {
            if(target<curr->data)
                curr=curr->left;
            else
                curr=curr->right;

            return search_rec(curr,target);
        }
    }
    int count_rec(BNode<t>* curr)
    {
        if(curr==NULL)
            return 0;
        else if(curr->left==NULL && curr->right==NULL)
            return 1;
        else
            return count_rec(curr->left)+count_rec(curr->right);

    }
    void inorder(BNode<t> * curr)
    {
        if(curr!=NULL)
        {
            inorder(curr->left);
            cout<<curr->data<<"  ";
            inorder(curr->right);
        }
    }

    int preorder_count(BNode<t> * curr,int count)
    {
        if(curr!=NULL)
        {
           if(curr->left==NULL && curr->right==NULL) 
           count++;
           count=preorder_count(curr->left,count);
           return preorder_count(curr->right,count);
           
        }
        return count;
    }

    int inorder_count(BNode<t> * curr,int count)
    {
        if(curr!=NULL)
        {
            count++;
           if(curr->left==NULL && curr->right==NULL) 
           count=inorder_count(curr->left,count);
           return inorder_count(curr->right,count);
           
        }
        return count;
    }

    BNode<t>* getRoot()
    {
        return root;
    }

};

int kth_smallest(BNode<int>* root, int k)
{
    BST<int> tree;
    int size = 0;
    BNode<int>* curr = root;
    size = tree.inorder_count(root, size);
    
    if(k > size)
    {
        cout<<"invalid K out of range: "<<endl;
        return 0;
    }
    else
	{
		Stack<BNode<int>*> s(100);
        int count = 0;

		while (curr != NULL || !s.isEmpty())
		{
			while(curr != NULL)
			{
                s.push(curr);
				curr = curr->left;
			}

            curr = s.pop();
            count++;

			if(count == k)
			{
				cout <<"Kth Lowest Score  (K="<<k<<"): "<< curr->data << " "<<endl;
                return 0;
				
			}
            curr = curr->right;
		}
	}
    return -1;
    
}

int main()
{
    BST<int> tree;
    int size, n = 0;
    cout<<"Enter Number of Players: ";
    cin>>size;

    cout<<"Enter Scores one by one: ";
    for(int i = 0; i<size; i++)
    {
        cin>>n;
        tree.insert(n);
    }

    int k;
    cout<<"Enter K to find Kth lowest scorer: ";
    cin>>k;
    cout<<"Inorder Sequence: ";
    tree.inorder(tree.getRoot());

    cout<<endl;
    kth_smallest(tree.getRoot(), k);
    
    int k1;
    cout<<"Enter K to find Kth lowest scorer: ";
    cin>>k1;
    cout<<endl;
    kth_smallest(tree.getRoot(), k1);

    return 0;
}