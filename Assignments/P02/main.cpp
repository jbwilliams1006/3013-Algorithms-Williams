/*****************************************************************************
*                    
*  Author:           Joshua Williams
*  Email:            jbrockwilliams@gmail.com
*  Label:            P02
*  Title:            Processing in Linear Time
*  Course:           CMPS 3013
*  Semester:         Spring 2021
* 
*  Description:
*        This program loads a singly linked list with dictionary words, then timing how it takes to look them up.
It then matches user input with words in the dictionary and displays how many words the input matches as well as how long it took to find that many words. 
*        
*  Usage: 
*       - $ ./main filename
*       - This will read in a file containing whatever values to be read into our list. 
*       
*  Files:            
*       main.cpp      : driver program 
*       dictionary.txt: file containing the dictionary
*       getch.hpp     : gets char
        termcolor.hpp : adds color to output characters
        timer.hpp     : sets timer during runtime
*****************************************************************************/

#include "getch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


/**
 * Description:
 *      Loads a file of strings (words) reading them in
 *      with one word per line. So words must be delimited by newlines '\n'
 * Params:
 *      string file_name - file to get the line count
 *      string a[] - to hold the words
 * Returns:
 *      nothing
 */

void Loadwords(string a[],string file_name) {
    ifstream fin;       // file to get dictionary words
    int count = 128325; // get size of input file

    fin.open(file_name); // open file for reading

    // knowing the size of the file lets us treat
    // it like an array without using .push_back(value)
    for (int i = 0; i < count; i++) {
        fin >> a[i];           // read in words
        // for (auto &c : a[i]) { // c++ 11 style loop
        //     c = tolower(c);        // lowercase the animal name
        // }
    }
}


struct wordNode
{
	string data;
	wordNode *next;
	// The following is a constructor for a node that 
	// will allow a node to be created that holds a string
	// entered and sets the next pointer that points 
	// eiher to a node entered or by default to NULL.
	
	// Default constructor allows an empty node to be created
	wordNode()
	{
		next = NULL;
	}

	// This can be adusted to set any values held by
	// a node, example:  string ln, string fn, string id, double gpa
	wordNode(string d, wordNode* p = NULL)
	{
		data = d; 
		next = p;
	}

};

/** 
 * Node
 * 
 * Description:
 *      Linked List creator
 * 
 * Public Methods:
 *      FindWords
 *      insertWord
 * Usage: 
 *      - To create a linked list
 *      - To fill a list with an array of words
 *      - To match words in linked list with input
 *      
 *     
 */

class Node {
  private:
  wordNode * head;
  wordNode * tail;
 

  public:
    int num; //Keeps count of how many words found
    //constructor
    Node(){
      head = NULL;
      tail = NULL;
      num = 0;
    }

    //destructor
    // delete all nodes in the list at the end of execution.
   ~Node (){
  	wordNode *p = head;
	while (p != NULL)
	{
		head = p->next;
		delete(p);
		p = head;
	}
    wordNode *q = tail;
     while (tail->next != NULL)
     {
       tail = tail->next;
     }
  }


void insertWord(string x)
{
  wordNode *n;
  if (head == NULL)
	{
		n = new wordNode(x);
		head = n;
		tail = n;
	}
	// Create a new node with the value to be
	// inserted and let the next pointer of the 
	// new node point to the same thing that head
	// points to
	// Non-default constructor
	// n = new Node(x, head);
	// Or... using default constructor
  if (head != NULL)
  {
	n = new wordNode();
	n->data = x;
	n->next = head;
  }
	// Reset the head pointer to point to the new node
	head = n;
  
}



/**
 * Description:
 *      Finds partial matches in a list of strings and returns them. It
 *      doesn't matter where in the string the match is.
 * Params:
 *      string          substring   - substring to search for in each word
 * 
 * Returns:
 *      vector<string> - holding all the matches to substring
 */
vector<string> FindWords(string substring) {
    vector<string> matches; // to hold any matches
    size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found.
    
    for (int i = 0; i < 128325; i++) 
    { // loop through list
        found = head->data.find(substring);    // check for substr match
        if (found != string::npos) {         // if found >= 0 (its found then)
            matches.push_back(head->data);     // add to matches
            num++; //increments for each word found
        }
        head = head->next;  //Sets the head pointer to the next location 
    }

    return matches;
}


};


//size of dictionary file
const int SIZE = 128325;

int main() {
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    string words [SIZE]; // array of all words
    vector<string> matches; // any matches found in vector of animals
    Node list;     //list of dictionary words
    int num;      //number of words found
    Timer T;   // create a timer
    T.Start(); // start it


    Loadwords(words,"dictionary.txt");  //Loads all words into an array
    
      //inserts words from array into list
      for (int i = 0; i<SIZE; i++){
        list.insertWord(words[i]);
      }


     T.End(); // end the current timer

     // print out how long it took to load the dictionary file
     cout << T.Seconds() << " seconds to read in and print json" << endl;
     cout << T.MilliSeconds() << " milli to read in and print json" << endl;

     cout << "Type keys and watch what happens. Type capital Z to quit.\n" << endl;

     // While capital Z is not typed keep looping
     while ((k = getch()) != 'Z') 
     {
        
         // Tests for a backspace and if pressed deletes
         // last letter from "word".
         if ((int)k == 127) 
         {
             if (word.size() > 0) 
             {
                 word = word.substr(0, word.size() - 1);
             }
         } else 
         {
             // Make sure a letter was pressed and only letter
            // if (!isalpha(k)) 
            // {
            //     cout << "Letters only!" << endl;
            //     continue;
            // }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            // if ((int)k < 97) 
            // {
            //     k += 32;
            // }
            word += k; // append char to word
        }
        cout << termcolor::red << k;
     }
        // Find any words in the array that partially match
        // our substr word
        T.Start(); // start it
        //Finds all words in the linked list that match word
        matches = list.FindWords(word);
        T.End(); // end the current timer

        if ((int)k != 32) 
        { // if k is not a space print it
            cout << "\n";

            cout << termcolor::red << list.num << termcolor::reset <<" Word(s) Found in "<<T.Seconds() << endl ;
            // This prints out all found matches
            for (int i = 0; i < matches.size(); i++) {
                cout << matches[i] << " ";
            }
            cout << termcolor::reset << endl
                 << endl;
        }

    

    return 0;   
}

