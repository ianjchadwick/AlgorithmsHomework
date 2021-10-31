#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
//used GeeksforGeeks YouTube tutorial for hint/help when I got stuck https://www.youtube.com/watch?v=X5UhF3xS5Dk&feature=emb_logo

int sumTo330(vector<int> nums)
{
    int left_index, right_index;
    long long int sum, result;

    //get the size of the vector
    int length = nums.size();

    //sort the vector from least to greatest
    sort (nums.begin(), nums.end());

    //If it's length 3 return the sum
    if (length == 3)
    {
        return (nums[0] + nums[1] + nums[2]);
    }
    
    //for each value from the left, pair with each other pair
    for (int i = 0; i < length - 2; i++ )
    {
        left_index = i + 1;
        right_index = length - 1;

        while (left_index < right_index)
        {
            sum = nums[i] + nums[left_index] + nums[right_index];
            if (abs(sum - 330) <= abs(result - 330))
                result = sum;
            
            if (sum < 330)
            left_index++;
            else
            right_index--;
        }
    }
    return result;
}

int main()
{
    vector <int> nums;
    nums.push_back(120);
    nums.push_back(230);
    nums.push_back(-3203);
    nums.push_back(-20);
    int value = sumTo330 (nums);

    cout << value << endl;

    return 0;
}