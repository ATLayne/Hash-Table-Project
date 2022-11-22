#ifndef STACK_H
#define STACK_H
#include <string>
using namespace std;
class Stack
{
private:
	struct StackNode
	{
		string teamName;
		StackNode* next;
	};

	StackNode* top;
public:
	Stack() 
		{ top = nullptr; }

	~Stack();

	void push(string);
	void pop(string&);
	bool isEmpty();
};
#endif // !STACK_H
