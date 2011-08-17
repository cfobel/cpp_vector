#include <vector>
#include <iostream>
using namespace std;

int main() {
    vector<vector<int> > v1(10, vector<int>(10, 0)); 
    vector<vector<int> > v2 = v1;

    cout << v1[0][0] << endl;
    cout << v2[0][0] << endl;
    v2[0][0] = 10;
    cout << v1[0][0] << endl;
    cout << v2[0][0] << endl;
    v1 = v2;
    cout << v1[0][0] << endl;
    cout << v2[0][0] << endl;
    return 0;
}
