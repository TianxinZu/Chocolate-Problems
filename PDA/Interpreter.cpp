#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

struct Item //store commands
{
    int statein;
    char input;
    char topofstack;
    char decision;
    char push;
    int stateout;

    Item(int a, char b, char c, char d, char e, int f)
    {
        statein = a;
        input = b;
        topofstack = c;
        decision = d;
        push = e;
        stateout = f;
    };
};



int main()
{
    //read input file
    string filename;
    cout << "Input file name: ";
    getline(cin, filename);
    ifstream infile(filename.c_str());
    if (!infile)
    {
        cout << "Cannot open " << filename << "!" << endl;
        return 1;
    }

    //read commands
    vector<Item*> track;  //store all commands
    string command;
    string inputstring;
    int instate;
    int outstate;
    char readin;
    char decide;
    char operation;
    char tos;

    while (!infile.eof())
    {
        getline(infile, command);

        if (command[0] != '{') //check if it is input string
        {
            inputstring = command;
            break;
        }
        instate = command[1]-48;
        readin = command[3];
        tos = command[5];
        decide = command[12];
        operation = command[14];
        outstate = command [16]-48;
        Item* c = new Item(instate, readin, tos, decide, operation, outstate);
        track.push_back(c);

        command = "";
    }
    

    int state = 0;
    stack<char> buff;
    bool find = false;  //false when not find command corresponding to input

    for (unsigned int i = 0; i < inputstring.length()-1; i++)
    {
        find = false;
        for (unsigned int j = 0; j < track.size(); j++)
        {
            if (state == track[j]->statein)
            {
                if (inputstring[i] == track[j]->input)
                {
                    if (track[j]->topofstack == '-' && buff.size() == 0)  //see nothing on stack
                    {
                        state = track[j]->stateout;
                        if (track[j]->decision == '+')
                        {
                            buff.pop();
                        }
                        if (track[j]->push != '~')
                        {
                            buff.push(track[j]->push);
                        }
                        find = true;
                        break;
                    }
                    else if (track[j]->topofstack == '~')  //no matter what's on the stack
                    {
                        state = track[j]->stateout;
                        if (track[j]->decision == '+')
                        {
                            buff.pop();
                        }
                        if (track[j]->push != '~')
                        {
                            buff.push(track[j]->push);
                        }
                        find = true;
                        break;
                    }
                    else if (buff.size() != 0 && track[j]->topofstack == buff.top())
                    {
                        state = track[j]->stateout;
                        if (track[j]->decision == '+')
                        {
                            buff.pop();
                        }

                        if (track[j]->push != '~')
                        {
                            buff.push(track[j]->push);
                        }
                        find = true;
                        break;
                    }
                }
                else if ((track[j]->input == 'a' && (inputstring[i] >= 97 && inputstring[i] <= 122)) ||  //letters
                (track[j]->input == '0' && (inputstring[i] >= 48 && inputstring[i] <= 57)) ||  //numbers
                (track[j]->input == '+' && (inputstring[i] >= 42 && inputstring[i] <= 47)))  //operation signs
                {
                    state = track[j]->stateout;
                    find = true;
                    break;
                }
            }
        }
        if (find == false)
        {
            cout << "No command found." << endl;
            break;
        }
        
        if (state == 6)
        {
            break;
        }
    }

    
    if (find == false) //no command found for one input
    {
        return -1;
    }

    if (buff.size() == 0 && state != 6)  //state S-1
    {
        state = 5;
    }
    else  //size != 0
    {
        state = 6;
    }
    if (state == 6)
    {
        cout << "No" << endl;
        return -1;
    }
    
    if (state == 5)
    {
        cout << "Yes" << endl;
        return 0;
    }

}