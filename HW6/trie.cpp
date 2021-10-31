#include <string>
#include "trie.h"

using namespace std;

void Trie::insert(string key, int val) {
    
    //create a pointer to track where we are in the Trie
    TrieNode *current = root;

    //for each letter in the key search the trie and add a letter to that node if it does not exist
    for (int i = 0; i < key.length(); i++)
        {        
            int index = (key[i]  - 'a');

          if (current->children[index] == NULL)
            {
                //add the new node and increase the tree size by one
                current->children[index] = new TrieNode;
                this->tree_size = this->tree_size+1;
            }
            //move pointer to next letter node
            current = current->children[index];
        }

        //if this is a new word, add one to the map size
        if (current->val == 0)
            this->map_size = this->map_size + 1;
        
        //then update the value with the new one
        current->val = val;
        
}

int Trie::search(string key) {
    
    if(key != ""){

        TrieNode *current = root;
        for (int i = 0; i < key.length(); i++)
            {
                int index = (key[i] - 'a');
                if (current->children[index] == NULL)
                    {
                        return 0;
                    }
                else{
                    current = current->children[index];
                    }
            }
        return current->val;
        }
    else
        return 0;
}

void Trie::remove(string key) {
    if (key != "") 
    {
        TrieNode *current = root;
        for(int i = 0; i < key.length(); i++)
            {
                int index = (key[i] - 'a');
                if (current->children[index] == NULL)
                    {
                        return;
                    }
                else
                    {
                        current = current->children[index];
                    }
            }
        
        //check to see if it's a leaf
        bool test = true;
        for (int i = 0; i < ALPHABET_SIZE; i++)
            {
                if (current->children[i] == NULL)
                    {
                    test = (test && true);
                    }
                else
                    test = false;
            }
        
        //if it is find the parent and set the pointer to the child to NULL
        if (test)
        {
            current = root;
            for(int i = 0; i < (key.length() - 1); i++)
           {
                int index = (key[i] - 'a');
                current = current->children[index];
           }
            int delete_target = (key[(key.length()-1)] - 'a');
            current->children[delete_target] = NULL;
            map_size--;
            tree_size--;

        }
        //else just set the value to 0
        else
        {
            current->val = 0;
            map_size--;
        }
    }
}
