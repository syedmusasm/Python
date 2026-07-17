#include <iostream>
using namespace std;

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

void nextImage(DNode<string>* &cur) 
{
    do {
        cout << "next -> Viewing:  " << cur->data << endl;
        cur = cur->next;
    }while(cur != nullptr);
    cout<<"next -> Viewing: Already at the last image."<<endl;
}

void previousImage(DNode<string>* &cur) 
{

    do {
        cout << "prev -> Viewing: " << cur->data << endl;
        cur = cur->prev;
    }while(cur != nullptr);
    cout<<"prev -> Viewing: Already at the first image."<<endl;
}
// ===================== Main Function =====================
int main() {
    DoublyLinkedList<string> gallery;

    gallery.insertEnd("Sunset.jpg");
    gallery.insertEnd("Mountain.jpg");
    gallery.insertEnd("Beach.jpg");
    gallery.insertEnd("Forest.jpg");
    gallery.insertEnd("City.jpg");
    

    gallery.displayForward();

    DNode<string>* current = gallery.getHead();
    DNode<string>* current1 = gallery.getTail();
    nextImage(current);
    cout<<endl;
    previousImage(current1);


    return 0;
}