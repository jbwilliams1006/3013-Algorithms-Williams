///////////////////////////////////////////////////////////////////////////////
//
// Author:           Joshua Williams
// Email:            jbrockwilliams@gmail.com
// Label:            P01
// Title:            Program 1 - Resizing the stack
// Course:           3013
// Semester:         Spring 2021
//
// Description:
//       A program that adds stack implementation to an already existing program
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
/** 
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack{
private:
int *A;           // pointer to array of int's
int top;          // top of stack 
public:
double size;         // current max stack size
int ct = 0;           // count of times stack resizes
/**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
ArrayStack(){
    size = 10;
    A = new int[size];
    top = -1;
  }
/**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
ArrayStack(int s){
    size = s;
    A = new int[s];
    top = -1;
  }
/**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
bool Empty(){
return (top <= -1);
  }
/**
  * Public bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
bool Full(){
return (top >= size-1);
  }

/**
  * Public bool: TooSmall
  * 
  * Description:
  *      Stack too small?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
bool TooSmall(){
  return (size > 10 && top <= size * 0.15);
}

/**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
int Peek(){
if(!Empty()){
return A[top];
    }
return -99; // some sentinel value
// not a good solution
  }
/**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
void Pop(){
if(!Empty()){
    top--;
    }
    CheckResize();
}

/**
  * Public void: Print
  * 
  * Description:
  *      Prints stack to standard out
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
void Print(){
for(int i=0;i<=top;i++){
      cout<<A[i]<<" ";
    }
    cout<<endl;
  } 

/**
  * Public void: CheckResize
  * 
  * Description:
  *      Resizes the container for the stack by doubling
  *      its capacity or havling its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
void CheckResize()
{
  if(Full())
  {
    ContainerGrow();
    ct++;
    }
  if(TooSmall())
  {
    ContainerShrink();
    ct++;
  }
}

/**
  * Public bool: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      
  */
void Push(int x){
CheckResize();
      A[++top] = x;
  }
/**
  * Public void: ContainerGrow
  * 
  * Description:
  *      Resizes the container for the stack by doubling
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
void ContainerGrow(){
int newSize = size*2;       // double size of original
int *B = new int[newSize];  // allocate new memory
for(int i=0;i<size;i++){    // copy values to new array
      B[i] = A[i];
    }
delete [] A;                // delete old array
    size = newSize;             // save new size
    A = B;                      // reset array pointer
  }

/**
  * Public void: ContainerShrink
  * 
  * Description:
  *      Resizes the container for the stack by dividing
  *      its capacity by two
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */

void ContainerShrink(){ 
int newSize = size / 2;       // half size of original
int *C = new int[newSize];  // allocate new memory
for(int i=0;i<size / 2;i++){    // copy values to new array
      C[i] = A[i];
    }
delete [] A;                // delete old array
    size = newSize;             // save new size
    A = C;                      // reset array pointer
  }

};
// MAIN DRIVER
// Simple Array Based Stack Usage:
int main() {
  ofstream outfile;
  outfile.open("Prog 1 output");

  outfile << "######################################################################\n"
        <<"     Assignment 4 - Resizing the Stack\n" 
        <<"     CMPS 3013\n"
        <<"     Joshua Williams \n\n";
  
  ArrayStack stack;

  ifstream fin;
  int num;                  //Number from infile
  int max = stack.size;     //Tracks stack max size
  int FinSize;              //Is the final size of stack

  fin.open("nums_test.dat");
  while(!fin.eof())
  {
    fin >> num;

    if (num%2==0)
    {
      stack.Push(num);
      if (max < stack.size)
      {
        max = stack.size;
      }
    }
    else
    {
      stack.Pop();
    }
    FinSize = stack.size;
  }
  int count = stack.ct;     //Tracks number of time stack resizes

  outfile <<"     Max Stack Size: "
          << max
          <<"\n     End Stack Size: "
          << FinSize
          <<"\n     Stack Resized: "
          <<count
          <<" times\n\n"
          <<"######################################################################";
outfile.close();

return 0;
 }

