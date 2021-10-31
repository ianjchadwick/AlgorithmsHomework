#include <string>
#include "sorta.h"

std::string sortByFreq(std::string s) {
	
     //Get the size of input string
    int input_size = s.size();

    //If the input string is 1 or less characters, no need to sort, return the string 
    if(input_size <= 1)
        return s;

    //comparison string with each letter of alphabet in order
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";

    //initialize a string to return
    std::string sorted_string = "";
    
    //initialize integer array full of 26 zeros to hold count of each letter of alphabet
    int letter_count[26];
    for(int i = 0; i < 26; i++)
        letter_count[i] = 0;

    //for each letter in the alphabet, count the number of occurences in the input string
    for (int i = 0 ; i < 26; i++)
    {
        for (int j = 0; j < input_size; j++ )
        {
            if(s[j] == alphabet[i])
                {
                    letter_count[i] = letter_count[i]+1;
                }
        }
    }

    //maintain a count of number of letters in alphabet
    int pass_count = 26;

    //loop until each of 26 letters has been checked
    while(pass_count > 0)
    {   
        //reset index to 0
        int index = 0;

        //search the array for the smallest value in alphabetical order
        for(int i = 0; i < 26; i++)
        {
            //only check if the count of that letter is greater than 0
            if(letter_count[i] > 0)
                {
                index = i;
                for(int j = 0; j < 26; j++)
                    {
                    //if the count at the index is greater than count the next index, replace the index with that index
                    if((letter_count[index] > letter_count [j]) &&
                        (letter_count[j] > 0))   
                        index = j;
    
                    //otherwise if they are equal in count, swap the index if it is earlier in alphabetical order
                    else if((letter_count[index] == letter_count[j]) &&
                            (alphabet[j] < alphabet[index])
                            )
                            {
                                index = j;
                            }
                 
                }

            //add 1 of each letter for the count in the letter count array to the output string
            while (letter_count[index] > 0)
                {
                sorted_string = sorted_string + alphabet[index];
                letter_count[index] = letter_count[index] - 1;
                }
                }
        }
        
        //decrement the pass count
        pass_count = pass_count - 1;
    }

    return sorted_string;
}