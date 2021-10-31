#include <stack>
#include <iostream>
using namespace std;

int keepMod(unsigned long long int num) {
	/* your code here */
	if (num == 0)
	{
		return 0;
	}

	stack <int> num_stack;
	int temp = 0;
	int mod_result = 0;

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

	
	mod_result = num_stack.top();
	num_stack.pop();
	
	while (!(num_stack.empty()))
	{
		temp = num_stack.top();
		num_stack.pop();
		
		mod_result = mod_result % temp;
	}

	return mod_result; /* don't forget to change the return value */
}

int main()
{

    int test = 0;
    int result = 0;

    cout << "Enter a number: ";
    cin >> test;

    result = keepMod (test);

    cout << endl << "The result is: " << result << endl;

    return 0;
}