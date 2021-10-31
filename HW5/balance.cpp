#include "node.h"
#include <cmath>
#include "math.h"
#include <iostream>
using namespace std;


int treeValue(node* root)
{   
    int count = 1;
    
    //base case
    if ((root->left == NULL) && (root->right == NULL))
        return count;
    
    else {
        //if left child exists recurse on left
        if(root->left != NULL)
            count += treeValue(root->left);

        //if right child exists recurse on right
        if(root->right != NULL)
            count += treeValue(root->right);
    }
    
    return count;
}


bool isWeightBalanced(node* root, int k) { 
    bool balance = true;
    bool left_balance= true;
    bool right_balance = true;
    int left_tree = 0;
    int right_tree = 0;

    if ((root->left == NULL) && (root->right == NULL))
        return balance;
    
    if (root->left != NULL)
        {
            left_tree = treeValue(root->left);
            //cout << "Left Subtree at node " << root->data << " is: " << left_tree << endl;
        }

    if (root->right != NULL)
        {
            right_tree = treeValue(root->right);
            //cout << "right Subtree at node " << root->data << " is: " << right_tree << endl;
        }

    if (abs(right_tree-left_tree) > k)
        {
            balance = false;
            return balance;
        }
    else
        {
            if(root->left != NULL)
            {
                left_balance = isWeightBalanced(root->left, k);
            }
            if(root->right != NULL)
            {
                right_balance = isWeightBalanced(root->right, k);
            }
        }
    
    if ((!right_balance) || (!left_balance))
        balance = false;


    return balance; // don't forget to upate this
}

// your helper methods here