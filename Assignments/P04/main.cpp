/*****************************************************************************
*                    
*  Author:           Joshua Williams
*  Email:            jbrockwilliams@gmail.com
*  Label:            P04
*  Title:            Processing in Trie Tree Time
*  Course:           CMPS 3013
*  Semester:         Spring 2021
* 
*  Description:
*        This program loads a binary search with dictionary words, then timing how it takes to look them up.
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

//size of dictionary file
const int SIZE = 102217;

void Loadwords(string a[],string b[],string file_name) {
    ifstream fin;       // file to get dictionary words
    string line;
    int count = 102217; // get size of input file
    int i = 0;          //array location
    fin.open(file_name); // open file for reading

    // knowing the size of the file lets us treat
    // it like an array without using .push_back(value)
    while(i != 102217) 
    {
        getline(fin,line,':');
        a[i] = line;           // read in words
        getline(fin,line);
        b[i] = line;           //read in def
        i++;
    }
}


struct wordNode
{
	string word;
  string definition;
	wordNode *right;
  wordNode *left;
	// The following is a constructor for a node that 
	// will allow a node to be created that holds a string
	// entered and sets the next pointer that points 
	// eiher to a node entered or by default to NULL.
	
	// Default constructor allows an empty node to be created
	wordNode()
	{
    word = "";
    definition = "";
		left = right = NULL;
	}

	// This can be adusted to set any values held by
	// a node, example:  string ln, string fn, string id, double gpa
	wordNode(string w, string d)
	{
		word = w; 
    definition = d;
	}

};


class BST 
{
  private:
    wordNode *root;
    int size;
    vector<string> results;

    bool Find(wordNode *, string key){
    if (!root) {
        return false;
    } else {
        //PreOrder
        if (root->word == key) {
            return true;
        } else if (key < root->word) {
            return Find(root->left, key);
        } else {
            return Find(root->right, key);
        }
    }
}


  public:
  int num;
  BST() 
  {
    size = 0;
    root = NULL;
  }
  void Insert(wordNode *&, string w, string d)
    {
       if (root) {
        root = new wordNode(w , d);
        return;
    } else {
        if (root-> word > w) {
            Insert(root->left, w , d);
        } else {
            Insert(root->right, w,d);
        }
          }
    }

  void Insert(string x, string y)
    {
    if (!root) {
        wordNode *temp = new wordNode(x,y);
        root = temp;
    } else {
        Insert(root, x, y);
    }
    }

      bool Find(string key)
   {
      return Find(root, key);
   }



vector<string> FindWords(string substring,string a[]) {
    vector<string> matches; // to hold any matches
    size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found.
    
   for (int i=0; i<SIZE; i++){
         found =a[i].find(substring);    // check for substr match
         if (found != string::npos) {         // if found >= 0 (its found then)
             matches.push_back(a[i]);     // add to matches
             num++; //increments for each word found
         }
   }
    return matches;
  }

};



int main() {
  char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    string words [SIZE]; // array of all words
    string def [SIZE]; //array of all definitions
    vector<string> matches; // any matches found in vector of animals
    BST list;     //list of dictionary words
    int num;      //number of words found
    Timer T;   // create a timer
    T.Start(); // start it
    int h=0;
    int j=0;

    Loadwords(words, def, "dictionary.txt");

     for (int i =0; i <SIZE; i++){
       list.Insert(words[i],def[i]);
     }


    T.End(); //End timer

    // print out how long it took to load the dictionary file
     cout << T.Seconds() << " seconds to read in dictionary file" << endl;
     cout << T.MilliSeconds() << " milli to read in dictionary file" << endl;

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
     
        // Find any words in the array that partially match
        // our substr word
        T.Start(); // start it
        //Finds all words in the linked list that match word
        //Finds all words in the linked list that match word
        matches = list.FindWords(word,words);
        
        T.End(); // end the current timer
        cout << T.Seconds() << " seconds to read in and print json" << endl;
        cout << T.MilliSeconds() << " milli to read in and print json" << endl;
        if ((int)k != 32) 
        { // if k is not a space print it
            cout << "Keypressed: " << termcolor::on_yellow << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            cout << matches.size() <<" Words Found: ";
            cout << termcolor::green;
            // This prints out all found matches
            //Prints 10 matches at most 
              if(matches.size()>=10)
               { for(int i = 0; i < 10; i++)
                 cout << matches[i] << " ";
              }
              else if(matches.size()<10)
              {
                for(int i = 0; i < matches.size(); i++)
                cout << matches[i] << " ";
              }
            
            cout << termcolor::reset << endl
                 << endl;
        }

     }

    return 0;   
}
