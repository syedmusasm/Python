#include<iostream>
using namespace std;
template <class t>
class BNode{
    public:
    t data;
    BNode<t>* left,*right;
    BNode( t d)
    {
        data=d;
        left=right=NULL;
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

    int inorder_count(BNode<t>* curr, int& count, int k)
    {
    if(curr == NULL)
        
        return -1;

    int left = inorder_count(curr->left, count, k);
    if(left != -1)
        return left;

    count++;


    return inorder_count(curr->right, count, k);
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

    BNode<t>* getRoot()
    {
        return root;
    }

};

int kth_smallest(BNode<int>* root, int k)
{
    static int count = 0;   // keeps track of visited nodes
    static int targetK = 0; // stores current k

    // reset when k changes
    if (targetK != k) {
        targetK = k;
        count = 0;
    }

    if(root == NULL)
        return -1;

    // go left subtree first
    int left = kth_smallest(root->left, k);
    if(left != -1)
        return left;

    // visit current node
    count++;
    if(count == k)
        return root->data;

    // go right subtree
    return kth_smallest(root->right, k);
}

int range_sum(BNode<int>* root, int low, int high)
{
    // if tree is empty, return 0
    if(root == NULL)
        return 0;

    int sum = 0;

    // if current node is greater than low,
    // left side may have valid values
    if(root->data > low)
        sum += range_sum(root->left, low, high);

    // if current node is in range, include it
    if(root->data >= low && root->data <= high)
    {
        cout << root->data << "  "; // print valid score
        sum += root->data;          // add to sum
    }

    // if current node is less than high,
    // right side may have valid values
    if(root->data < high)
        sum += range_sum(root->right, low, high);

    // return total sum of valid nodes
    return sum;
}

//  Task 1 code

// int main()
// {
//     BST<int> tree;
//     int n;
//     cout << "Enter Number of Players: ";
//     cin >> n;

//     cout << "Enter scores: ";
    
//     for (int i = 0; i < n; i++) // insert values into BST
//     {
//         int t;
//         cin >> t;
//         tree.insert(t);
//     }
    
//     cout << endl;

//     // --- K = 3 ---
//     int k;
//     cout<<"Enter K to find Kth lowest scorer:";
//     cin>> k;

//     cout<<"Inorder sequence:";
//     tree.inorder(tree.getRoot());
//     cout<<endl;

//     int ans3 = kth_smallest(tree.getRoot(), k);
//     if (ans3 == -1)
//         cout << "Kth Lowest Score(K = 3): Invalid k is out of Range" << endl;
//     else
//         cout << "Kth Lowest Score(K = 3): " << ans3 << endl;

//     // --- K = 6 ---
//     int k1;
//     cout<<"Enter K to find Kth lowest scorer:";
//     cin>> k1;
//     int ans6 = kth_smallest(tree.getRoot(), k1);
//     if (ans6 == -1)
//         cout << "Kth Lowest Score(K = 6): Invalid k is out of Range" << endl;
//     else
//         cout << "Kth Lowest Score(K = 6): " << ans6 << endl;

//     // --- K = 15 ---
//     int k2;
//     cout<<"Enter K to find Kth lowest scorer:";
//     cin>> k2;
//     int ans15 = kth_smallest(tree.getRoot(), k2);
//     if (ans15 == -1)
//         cout << "Kth Lowest Score(K = 15): Invalid k is out of Range" << endl;
//     else
//         cout << "Kth Lowest Score(K = 15): " << ans15 << endl;

//     return 0;
// }


// Task 2 code

// int main()
// {
//     BST<int> tree; // create BST object

//     int n;
//     cout << "Enter Number of Players: ";
//     cin >> n;

//     cout << "Enter scores: ";

//     // insert all player scores into BST
//     for(int i = 0; i < n; i++)
//     {
//         int x;
//         cin >> x;
//         tree.insert(x);
//     }

//     int low, high;

//     // first range input
//     cout << "Enter score range for prize eligibility (low high): ";
//     cin >> low >> high;

//     cout << "Eligible Scores: ";

//     // calculate sum of scores in range
//     int sum = range_sum(tree.getRoot(), low, high);

//     cout << "\nTotal Prize Pool Score Sum: " << sum << endl;

//     cout << endl;

//     // second range input
//     cout << "Enter score range for prize eligibility (low high): ";
//     cin >> low >> high;

//     cout << "Eligible Scores: ";

//     // calculate sum again for new range
//     int sum1 = range_sum(tree.getRoot(), low, high);

//     cout << "\nTotal Prize Pool Score Sum: " << sum1 << endl;

//     return 0; // program ends
// }



