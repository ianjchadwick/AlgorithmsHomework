char findOdd(char arr[], int arr_size) {
	/* your code here */
	//Thanks to TA Khoa for the hint
	
	//create an array of all lower case letters for comparison
	char alphabet[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

	//create an array of 26 integers to correspond to the counts of each letter
	int result[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	//character to store the return value
	char answer;
	//to find the index of the odd character from the alphabet array
	int index = 0;

	//for each letter in alphabet array, count the instances in the input array.
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

	//go through the counts to find the one that is odd and exit once the index is found
	while ((result[index]%2) == 0)
	{
		index++;
	}

	//set answer to the correct letter
	answer = alphabet[index];

	//return the letter that appears odd times
	return answer;
}