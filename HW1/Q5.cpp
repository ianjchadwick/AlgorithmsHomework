#include <iostream>
using namespace std;

int main()
{   
    int sum = 0;
    int n = 0;
    cout << "Enter a value for n: ";
    cin >> n;
    for (int i = n; i > 0; i--)
    {
        for (int j = n-i; j < n; j++)
        {
            sum = sum + 2;
        }
    }
    cout << endl << "The value of sum is: " << sum << endl;

    return 0;
}