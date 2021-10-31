#include <iostream>
#include <string>
#include "node.h"

using namespace std;

int main() {

	/*
			1
		   / \
          2   3
         /   / \
        4   5   6
       /
      7
	*/
	node* n1 = new node(1);
	node* n2 = new node(2);
	node* n3 = new node(3);
	node* n4 = new node(4);
	node* n5 = new node(5);
	node* n6 = new node(6);
	node* n7 = new node(7);
	n1->left = n2;
	n1->right = n3;
	n2->left = n4;
	n3->left = n5;
	n3->right = n6;
	n4->left = n7;

	cout << "At 1: " << isWeightBalanced(n1, 0) << endl;
	cout << "At 2: " << isWeightBalanced(n2, 1) << endl;
	cout << "At 3: " << isWeightBalanced(n3, 0) << endl;
	cout << "At 4: " << isWeightBalanced(n4, 1) << endl;


}