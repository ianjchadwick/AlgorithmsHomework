#include <iostream>
using namespace std;

char findOdd(char arr[], int arr_size) {
	/* your code here */

	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	int result[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char answer;
	int index = 0;

	for (int i = 0; i < 26; i++)
	{
		for(int j = 0; j < arr_size; j++)
		{
			if (alphabet[i] == arr[j])
			{
				result[i] = result[i]+1;
			}
		}
	}

	while ((result[index]%2) == 0)
	{
		index++;
	}

	answer = alphabet[index];

	return answer; /* don't forget to change the return value */
}


int main()
{

    char testarray[7] = {'a','b','c','c','c','a','b'};
    int length = 7;

    cout << findOdd(testarray, length) << endl;

    return 0;
}