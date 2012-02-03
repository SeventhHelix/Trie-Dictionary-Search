/*
 * =====================================================================================
 *
 *    Description:  Uses a Trie structure to build a tree of letters forming words
 *                  The +. -, ? operators are used to add, remove, and query words
 *                  include <filename> will run the commands listed in another file
 *
 *         Author:  Jeff Dyck
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include "trie.h"

using namespace std;

int main(){

   string word, op;
   TrieNode *trie = new TrieNode;

   while (cin >> op){                                        // Loops over input
      cin >> word;      

      if (op == "+")             insert(*trie, word, 0);     // Add a word
      else if (op == "-")        remove(*trie, word, 0);     // Remove word
      else if (op == "?")        cout << find(*trie, word, 0) << endl;  // Query a word
      else if (op == "include")  includeFile(trie, word);    // Include a file
   } // while

   annihilateTrie(trie);

   return 0;
}
