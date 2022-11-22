#include <iostream>
#include "stack.h"
using namespace std;

//Destructor
Stack::~Stack() {
	//Creating two new node pointers.
	StackNode* nodePtr = nullptr;
	StackNode* nextNode = nullptr;

	//Starting at the top of the stack.
	nodePtr = top;

	//Traversing list and deleting each node.
	while (nodePtr != nullptr)
	{
		nextNode = nodePtr->next;
		delete nodePtr;
		nodePtr = nextNode;
	}
}

void Stack::push(string teamName) {

	//Creating pointer to a new node;
	StackNode* newNode = nullptr;

	//Allocating memory for the new node.
	//Setting the new nodes teamname to the string passed to it.
	newNode = new StackNode;
	newNode->teamName = teamName;

	//The new node should always be at the top of the stack.
	if (isEmpty()) {
		top = newNode;
		newNode->next = nullptr;
	}
	else
	{
		//If not then the newNodes next pointer will be
		//the previous top.
		newNode->next = top;	
		top = newNode;
	}
}

void Stack::pop(string& teamName) {

	StackNode* temp = nullptr;

	if (isEmpty()) {
		cout << "The stack is empty." << endl;
	}
	else
	{
		teamName = top->teamName;
		temp = top->next;
		delete top;
		top = temp;
	}
}

bool Stack::isEmpty() {
	bool status;
	if (!top)
		status = true;
	else
		status = false;

	return status;
}
