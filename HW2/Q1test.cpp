#include <stack>
#include <vector>
#include <iostream>
using namespace std;

int kthDigit(int k)
{
    vector<int> series;
    stack<int> temp_stack;
    int temp1, temp2;

    for (int i = 0; i < k; i++)
    {
        if (i == 0)
            series.push_back(i);
        else
        {
        
        temp1 = i;
        
            while (temp1 > 0)
            {
                temp_stack.push(i%10);
                temp1 = temp1 /10;
            }
        
            while (!(temp_stack.empty()))
            {
                temp2 = temp_stack.top();
                temp_stack.pop();
                series.push_back(temp2);
            } 
        }
    }

return series[k-1];
}

int main()
{
    int testInt;
    cout << "Test Number:" << endl;
    cin >> testInt;
    cout << kthDigit(testInt) << endl;

    return 0;
}