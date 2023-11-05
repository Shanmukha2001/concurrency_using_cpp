#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Calculate the product of all elements
    int mulVal = accumulate(v.begin(), v.end(), 1, multiplies<int>());
    cout << "Product: " << mulVal << endl;

    // Create a concatenated string of the elements
    auto lambdaFunc = [](string oldVal, int currNum) {
        return move(oldVal) +"-"+ to_string(currNum);
    };
    string val = accumulate(v.begin()+1, v.end(), to_string(v[0]), lambdaFunc);
    
    cout << "Concatenated String: " << val << endl;

    return 0;
}
