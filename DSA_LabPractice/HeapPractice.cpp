#include <iostream>
using namespace std;


void heapifyUp(int arr[], int index)
{
    while(index > 1)
    {
        int parent = index/2;
        if(arr[index] > arr[parent])
        {
            swap(arr[index], arr[parent]);
            index = parent;
        }
        else
        {
            break;
        }
    }
}

void insertHeap(int arr[], int value, int &size)
{
    size++;
    arr[size] = value;
    heapifyUp(arr, size);
}

void HeapifyDown(int arr[], int &size, int index)
{
    while(true)
    {
        int left = 2* index;
        int right = 2* index+ 1;
        int largest = index;

        if(left <= size && arr[left] > arr[largest])
        {
            largest = left;
        }
        if(right <= size && arr[right] > arr[largest])
        {
            largest = right;
        }
        if(largest == index)
        {
            break;
        }

        swap(arr[index], arr[largest]);
        index = largest;
    }
}

void DeleteValue(int arr[], int &size, int value)
{
    int index = -1;
    for(int i = 1; i <= size; i++)
    {
        if(arr[i] == value)
        {
            index = i;
            break;
        }
    }
    arr[index] = arr[size];
    size--;
    HeapifyDown(arr, size, index);
}

void DeleteRoot(int arr[], int &size, int index)
{
    arr[index] = arr[size];
    size--;
    HeapifyDown(arr, size, index);
}

bool SearchValue(int arr[], int size, int value)
{
    for(int i = 1; i<size; i++)
    {
        if(arr[i] == value)
        {
            return true;
        }

    }
    return false;
}

int findMax(int arr[], int &size)
{
    return arr[1];
    
}

int findMin(int arr[], int size)
{
    if(size == 0)
        return -1;   // or throw an error

    int min = arr[1];

    for(int i = 2; i < size; i++)
    {
        if(arr[i] < min)
        {
            min = arr[i];
        }
    }

    return min;
}

void HeapSort(int arr[], int size)
{
    int n = size;
    while(size >=1){
        for(int i = 1; i<=n; i++)
        {
            if(arr[i]> arr[n]){
                swap(arr[i], arr[n]);
                n--;
                HeapifyDown(arr, n, 1);
            }
        }
        size--;
    }
}

void MinHeapifyDown(int arr[], int &size, int index)
{
    while(true)
    {
        int left = 2* index;
        int right = 2* index+ 1;
        int largest = index;

        if(left <= size && arr[left] < arr[largest])
        {
            largest = left;
        }
        if(right <= size && arr[right] < arr[largest])
        {
            largest = right;
        }
        if(largest == index)
        {
            break;
        }

        swap(arr[index], arr[largest]);
        index = largest;
    }
}

void MinHeap(int arr[], int &size)
{
    for(int i = size/2 ; i>=1; i--)
    {
        MinHeapifyDown(arr, size, i);
    }
}



int main()
{
    int arr[100];
    int size = 0;

    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the elements:\n";

    for(int i = 1; i <= n; i++)
    {
        int value;
        cin >> value;

        insertHeap(arr, value, size);
    }

    cout << "The Heap is: ";

    for(int i = 1; i <= size; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;

    // insertHeap(arr, 60, size);
    // cout<<"After Inserting 60 the Heap: ";

    // for(int i = 1; i <= size; i++)
    // {
    //     cout << arr[i] << " ";
    // }
    // cout<<endl;

    int x;
    cout<<"Enter Value to delete: ";
    cin>>x;

    DeleteRoot(arr, size, x);
    cout<<"After deleting the root the Heap: ";

    for(int i = 1; i <= size; i++)
    {
        cout << arr[i] << " ";
    }
    cout<<endl;

    // int value2;
    // cout<<"Enter a value to search for: ";
    // cin>>value2;

    // if(SearchValue(arr, size, value2) == true)
    // {
    //     cout<<"Value Exist...."<<endl;
    // }
    // else
    // {
    //     cout<<"Value Doesn't Exist..."<<endl;
    // }

    // int max = findMax(arr, size);
    // cout<<"Maximum: "<<max<<endl;

    // int min = findMin(arr, size);
    // cout<<"Minimum: "<<min<<endl;

    HeapSort(arr, size);
    cout<<"Heap After Sorting: ";
    for(int i = 1; i <= size; i++)
    {
        cout << arr[i] << " ";
    }
    cout<<endl;

    MinHeap(arr, size);
    cout<<"Min heap: ";
    for(int i = 1; i <= size; i++)
    {
        cout << arr[i] << " ";
    }
    cout<<endl;

    return 0;
}
