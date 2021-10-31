#include <vector>
#include "sortb.h"

int sortedMode(std::vector<int> v) {
    
    //initialize variables
    int current_count = 1;
    int max_count = 0;
    int value = 0;

    //get size of input
    int size = v.size();

    //if the size is 1 return the value in the vector
    if (size == 1)
    {
        return v[0];
    }

    /*Since the array is sorted step through the array count the number of sequential repeated numbers. 
    When the total count is greater than the current maximum count replace the value with the value 
    that has the highest count. This is the new mode.*/
    for (int i = 0; i < size-1; i++)
    {
        if (v[i] == v[i+1])
        {
            current_count = current_count + 1;
            if (current_count > max_count)
                {
                value = v[i+1];
                max_count = current_count;    
                }
        }
        else
        {
            current_count = 1;
            if (current_count > max_count)
                {
                value = v[i];
                max_count = current_count;    
                }
        }
        /*if the highest count is greater than the remaining amount of numbers in the array, return the value that
        has that count. That is the mode. The mode must be that value because there aren't enough numbers left in 
        the vector to change the mode.*/
        if(max_count > (size - i))
        {
            return value;
        }
    
    }

    return value;
}
