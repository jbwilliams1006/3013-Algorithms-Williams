/*****************************************************************************
*                    
*  Author:           Joshua Williams
*  Email:            jbrockwilliams@gmail.com
*  Label:            A03
*  Title:            Linked List Class
*  Course:           CMPS 3013
*  Semester:         Spring 2021
* 
*  Description:
*        This program implements a class that allows a linked list to be used just like 
*        an array. It overloads the "[]" (square brackets) to simulate accessing seperate 
*        array elements, but really it traverses the list to find the specified node using
*        an index value. It also overloads the "+" and "-" signs allowing a user to "add"
*        or "push" items onto the end of the list, as well as "pop" items off the end of our 
*        array. This class is not meant to replace the STL vector library, its simply a project
*        to introduce the beginnings of creating complex / abstract data types. 
*        
*  Usage: 
*       - $ ./main filename
*       - This will read in a file containing whatever values to be read into our list/array. 
*       
*  Files:            
*       main.cpp    : driver program 
*       list.h      : header file with list defintion
*       list.cpp    : list implementation
*****************************************************************************/
#include <iostream>

using namespace std;

int A[100];                                         //Array Variable for 100 intergers

/**
 * Node
 * 
 * Description:
 *      This Struct implements two methods that perform 
 *      the creation of a Node pointer in a linked list
 *     
 * Public Methods:
 *                                                     
 *      void                Node ()
 *      void                Node (int n)
 * 
 * Usage: 
 * 
 *      Node ();                                    // Creates an instance of a Node pointer 
 *                                                
 *      Node (int n);                               // Creates an instance of a Node Pointer
 *                                                  // with int n as it's value
 */


struct Node {
    int x;                                          //Integer used as value in Node intialization 
    
    Node *next;                                     //Pointer that points to the next memory location
                                                    //in the linked list 
    Node() {
        x = -1;
        next = NULL;
    }
    Node(int n) {
        x = n;
        next = NULL;
    }
};

/**
 * List
 * 
 * Description:
 *      This Class uses the Node creation from the previous struct to create a list. 
 *      The methods in the class peform actions on the list such as adding a value
 *      to the list, printing the list or printing the tail. This class also has a method
 *      that adds a new list on to the previous created list
 *     
 *      
 * 
 * Public Methods:
 *                                                     
 *      void                List ()
 *      void                Push (int val)
 *      void                Insert (int val)
 *      void                PrintTail()
 *      string              Print()
 *      List                operator(const List &Rhs)
 *      int                 operator[](index)
 *
 * 
 * Usage: 
 * 
 *      List ();                                    // Creates a linked list pointing tail to NULL
 *                                                
 *      Node (int n);                               // Creates an instance of a Node Pointer
 *                                                  // with int n as it's value
 */
class List {
private:
    Node *Head;                                     //Pointer that points to the front of the linked list
    Node *Tail;                                     //Pointer that points to the end of the lined list  
    int Size;                                       //Allocates the size of linked list 

public:
    List() {
        Head = Tail = NULL;
        Size = 0;
    }

    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }

    void PrintTail() {
        cout << Tail->x << endl;
    }

    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented
    int Pop() {
        Size--;
        return 0; //
    }

    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv) {
    List L1;
    List L2;

    for (int i = 0; i < 25; i++) {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++) {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}
