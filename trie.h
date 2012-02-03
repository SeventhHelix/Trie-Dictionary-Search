#ifndef __TRIE_H__
#define __TRIE_H__
#include <string>

struct TrieNode {
    enum { Apostrophe = 26, NumChars = 27 };
    bool isWord;
    TrieNode *letters[NumChars];
    TrieNode() {
        isWord = false;
         for ( int i = 0; i < NumChars; i += 1 ) {
             letters[i] = NULL;
         } // for
    }
}; // TrieNode

void insert( TrieNode &node, const std::string &word, int index);

void remove( TrieNode &node, const std::string &word, int index);

std::string find( const TrieNode &node, const std::string &word, int index);

void allChildren( const TrieNode &node, const std::string &parentWord );

void includeFile( TrieNode *node, const std::string &fileName );

void annihilateTrie (TrieNode *trie);

#endif


