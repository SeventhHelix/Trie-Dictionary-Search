/*
 * =====================================================================================
 *
 *    Description:  Several functions for operating on the trie structure
 *
 *         Author:  Jeff Dyck
 *
 * =====================================================================================
 */

#include "trie.h"
#include <iostream>
#include <fstream>

/*
 * words is used in the find and allChildren functions to put the found words together
 * Set at this level since it needs to be viewable at all depths of recursion
 * Set back to "" at the end of find
 * tempStr is used to hold the completed word list before clearing words
 * tempChar is used to add characters to the words in allChildren
 */
std::string words = "";
std::string tempStr = "";
char tempChar;


/*
 * Inserts the specified word into the given node
 * Creates new TrieNodes along the way if necessary
 * If the word already exists, nothing happens
 */
void insert( TrieNode &node, const std::string &word, int index) {
   if (index == word.length()){                                 // End of word
      node.isWord = true;
      return;
   } else {                                                     // Add letter
      // Creates the node at the index of the next letter of word if needed
      // then recurses on it
      if (node.letters[word[index] - 'a'] == NULL) {   
         node.letters[word[index] - 'a'] = new TrieNode; 
      }
      insert(*(node.letters[word[index] - 'a']), word, index+1);   // Recurse
   } // else
}


/*
 * Remove the specified word into the given node
 * If the word doesn't exist, nothing happens
 */
void remove( TrieNode &node, const std::string &word, int index) {
   if (index == word.length()){                           // End of word
      node.isWord = false;
      return;
   } else {
      if (node.letters[word[index] - 'a'] == NULL) {      // Letter doesn't exist, word not found
         return;
      } else {
         remove(*(node.letters[word[index] - 'a']), word, index+1);
      }
   } // else
}


/*
 * Returns a string of all the tab-completed words from the given word
 * Recurses until it hits the end of the word, then calls allChildren
 * to return all of the following words
 */
std::string find( const TrieNode &node, const std::string &word, int index) {
   if (index == word.length()){                       // End of word
      allChildren(node, word);      
      std::string tempStr = words;
      words = "";
      return tempStr;
   } else {
      if (node.letters[word[index] - 'a'] == NULL) {  // Letter doesn't exist
         return "";
      } else {
         return find(*(node.letters[word[index] - 'a']), word, index+1);  // Recurse
      }
   } // else
}


/*
 * Works on the global words string, adding words to it as they are found.
 * words becomes a list of all of the words that begin at the first given root 
 */
void allChildren( const TrieNode &node, const std::string &parentWord ) {
   if (node.isWord) {
      words += parentWord + ' ';
   }
   for (int i=0; i < 26; i++) {
      if (node.letters[i]) {         // If the next letter isn't null
         tempChar = i + 'a';
         allChildren(*(node.letters[i]), parentWord + tempChar);
      }
   } // for
}

/*
 * Creates an ifstream from a given filename, and loops over the file
 * similarily to the main function loop.
 * Run all of the commands in the given file
 */
void includeFile( TrieNode *trie, const std::string &fileName ) {
   std::string word, op;
   std::ifstream file(fileName.c_str());

   while (file >> op){                              // Loops over input
      file >> word;      

      if (op == "+")             insert(*trie, word, 0);     // Add a word
      else if (op == "-")        remove(*trie, word, 0);     // Remove word
      else if (op == "?")        std::cout << find(*trie, word, 0) << std::endl;  // Query a word
      else if (op == "include")  includeFile(trie, word);    // Include a file
   } // while
}

/*
 * Deletes a Trie from memory
 * First recurses on all of the given trie's children, then deletes itself
 */
void annihilateTrie (TrieNode *trie) {
   if (trie == NULL) {
      return;
   } else {
      for (int i = 0; i < 26; i++) {
         if (trie->letters[i]) {
            annihilateTrie(trie->letters[i]);
         }
      } // for
      delete trie;
   } // else
}
