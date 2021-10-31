#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

int sumTo330(vector<int> nums)
{
    //get the size of the vector
    int length = nums.size();

    //If it's length 3 return the sum
    if (length == 3)
    {
        return (nums[0] + nums[1] + nums[2]);
    }

    // sort the vector from least to greatest
    sort (nums.begin(), nums.end());

    int middle_index = length/2;
    int left_index = middle_index - 1;
    int right_index = middle_index + 1;
    
    int middle_sum, left_sum, right_sum = 0;

    int middle_diff, left_diff, right_diff, temp, temp_diff;

    //calculate the sum from the middle 3 integers
    middle_sum = nums[left_index] + nums[middle_index] + nums[right_index];

    //if not out of bounds, sum the 3 integers to the left of the middle
    if((left_index - 1) >= 0)
    {
        left_sum = nums[left_index -1] + nums[left_index] + nums[left_index + 1];
        left_index--;
    }

    //if not out of bounds, sum the integers to the right of the middle
    if ((right_index + 1) <= (length -1))
     {
         right_sum = nums[right_index -1] + nums[right_index] + nums[right_index + 1];
         right_index++;
     }

    //calculate the difference between the sums and the target
    middle_diff = abs(middle_sum - 330);
    left_diff = abs(left_sum - 330);
    right_diff = abs(right_sum - 330);

    //while not out of bounds
    while ( ( (left_index-1) >= 0) && ( left_diff <= middle_diff) )
    {
        temp = nums[left_index -1] + nums[left_index] + nums[left_index + 1];
        temp_diff = abs(temp - 330);
        
        if (temp_diff <= left_diff)
        {
            left_sum = temp;
            left_diff = abs(left_sum - 330);
            left_index--;
        }
    }
    
    while ( ( (right_index + 1) <= (length - 1)) && ( right_diff <= middle_diff) )
    {
        right_sum = nums[right_index -1] + nums[right_index] + nums[right_index + 1];
        right_diff = abs(right_sum - 330);
        right_index++;
    }

    if ( (left_diff < right_diff) && (left_diff <= middle_diff))
    {
        return left_sum;
    }
    else if (middle_diff <= right_diff)
    {
        return middle_sum;
    }
    else
    {
        return right_sum;
    }
}