#include <iostream>
#include <stack>
#include <sstream>

using namespace std;

int main()
{
    cout << "Enter a series of arithmetic expression: ";

    stack<char> buffer;

    char x;
    string m;
    bool fail = false;
    bool after =false; //after ')'
    getline(cin, m);
    stringstream ss(m);
    ss >> x;

    while (!ss.eof() && fail == false)
    {
        if (x == '(')
        {
            buffer.push(x);
            after = false;
        }
        else if (x >= 48 && x <= 57) //numbers
        {
            if (after) //numbers cannot appear right after ')'
            {
                fail = true;
                break;
            }
            else if (!buffer.empty() && buffer.top() >= 97) //number cannot appear right after letters
            {
                fail = true;
                break;
            }
            buffer.push(x);
            after = false;
        }
        else if (x >= 97)   //letters
        {
            if (after)
            {
                fail = true;
                break;
            }
            if (!buffer.empty() && buffer.top() >= 48 && buffer.top() <= 57) // letters cannot appear right after numbers
            {
                fail = true;
                break;
            }
            buffer.push(x);
            after = false;
        }
        else if (x >= 42 && x <= 47) //operation signs
        {
            if (!buffer.empty() && buffer.top() >= 42 && buffer.top() <= 47) //operation signs cannot appear right after itself
            {
                fail = true;
                break;
            }
            buffer.push(x);
            after = false;
        }
        else if (x == ')')
        {
            if (!buffer.empty() && buffer.top() >= 42 && buffer.top() <= 47) //')' cannot appear right after operation signs
            {
                fail = true;
                break;
            }
            while (buffer.size() > 0 && buffer.top() != '(') //find the pairs
            {
                buffer.pop();
            }
            if (buffer.size() == 0) //extra ')'
            {
                fail = true;
                break;
            }
            buffer.pop();
            if (!buffer.empty() && buffer.top() >= 42 && buffer.top() <= 47) //pop the operation sign before the parenthesis
            {
                buffer.pop();
            }
        }



        ss >> x;
    }

    while (buffer.size() > 0 && buffer.top() != '(') //remove elements beside '('
    {
        buffer.pop();
    }

    if (fail == false && buffer.size() == 0)
    {
        cout << "Yes" << endl;
    }
    else //extra '('
    {
        cout << "No" << endl;
    }

}