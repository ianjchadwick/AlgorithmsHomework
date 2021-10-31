#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

//used GeeksforGeeks YouTube tutorial for hint/help when I got stuck https://www.youtube.com/watch?v=X5UhF3xS5Dk&feature=emb_logo

int sumTo330(vector<int> nums)
{
    long long int left_index, right_index;
    long long int sum, result;

    //get the size of the vector
    long long int length = nums.size();

    //sort the vector from least to greatest
    sort (nums.begin(), nums.end());

    //If it's length 3 return the sum
    if (length == 3)
    {
        return (nums[0] + nums[1] + nums[2]);
    }
    
    //for each value from the left, pair with the remaining values to the right
    for (long long int i = 0; i < length - 2; i++ )
    {
        //set 2nd index to the right of i
        left_index = i + 1;
        //set the 3rd index to the last element
        right_index = length - 1;

        //while the indexes are not equal
        while (left_index < right_index)
        {
            //sum up the integer values
            sum = nums[i] + nums[left_index] + nums[right_index];

            //if the difference between 330 and the sum is less than the current result, replace it
            if (abs(sum - 330) <= abs(result - 330))
                result = sum;
            
            //if the sum is less than 330 move the left (2nd) index to the right
            if (sum < 330)
            left_index++;

            //else move the right (3rd) index to the left
            else
            right_index--;
        }
    }

    //return the closest value
    return result;
}