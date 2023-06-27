#include <iostream>
using namespace std;

#define STRINGCAT_HELPER(x, y)  x##y
#define test(x,y) x##y

#define test2(x) #x

int main()
{
    cout << "Hello world!" << endl;
    cout << test(1,2) << endl;
    cout << test2(345) << endl;
    return 0;
}