#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

int main()
{
    stack<char> buffer;
    
    cout << "Enter a series of parenthesis: ";
    
    bool fail = false;
    char x;
    string m;
    getline(cin, m);
    stringstream ss(m);
    ss >> x;
    while (!ss.eof() && fail == false)
    {
        if ((x == '(') || (x == '['))
        {
            buffer.push(x);
        }
        else if (x == ')')
        {
            if (buffer.size() == 0)
            {
                fail = true;
                break;
            }
            if (buffer.top() != '(')
            {
                fail = true;
                break;
            }
            buffer.pop();
        }
        else if (x == ']')
        {
            if (buffer.size() == 0)
            {
                fail = true;
                break;
            }
            if (buffer.top() != '[')
            {
                fail = true;
                break;
            }
            buffer.pop();
        }

        ss >> x;
    }

    if ((fail == false) && (buffer.size() == 0))
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }
    
    return 0;
}
