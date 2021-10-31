#include <stack>
using namespace std;

int keepMod(unsigned long long int num) {
	/* your code here */
	if (num == 0)
	{
		return 0;
	}

	//create a stack to hold the digits of num
	stack <int> num_stack;

	//initialize variables to hold the temporary and final values
	int temp = 0;
	int mod_result = 0;

	//loop through the input number until it is 0
	while (num >= 1)
	{
		//get the one's digit
		temp = num % 10;
		
		//add it to the stack if it's not equal to zero
		if (temp != 0)
		{
		num_stack.push(temp);
		}

		//divide by 10 to drop the one's digit
		num = num/10;
	}

	//get the first value off the stack which will be the most significant digit
	mod_result = num_stack.top();
	num_stack.pop();
	
	//while the stack is not empty loop through
	while (!(num_stack.empty()))
	{
		//pop off the top element
		temp = num_stack.top();
		num_stack.pop();
		
		//mod the current value by the next digit
		mod_result = mod_result % temp;
	}

	//return the calculated value
	return mod_result;
}