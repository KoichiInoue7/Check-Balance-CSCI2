#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <stack>
using namespace std;


void printFile(istream& dictfile)
{
    string line;
    int lineNumber = 1;
    while (getline(dictfile, line))
    {
        cout << lineNumber <<": " << line << endl;
        lineNumber++;
    }
}


bool balanceFile(istream& dictfile) 
{
    stack<char> S;
    stack<int>line;
    char c, d;
    bool match = true; 
    char prev = '\0';
    string comment;
    string makeString;
    int lineNumber = 1;

    while (dictfile.get(c))
    {
        if (c == '\n')
        {
            lineNumber++;
        }
        if (prev == '/' && c == '*')
        {
            char prevInside = '\0';
            while (dictfile.get(c))
            {
                if (c == '\n')
                {
                    lineNumber++;
                }

                comment += c;
                if ((prevInside == '*' && c == '/'))
                {
                    cout << "Pair matching /* */" << endl;
                    break;
                }
                prevInside = c;

            }
        }

        else if (prev == '/' && c == '/')
        {
            while (dictfile.get(c) && c != '\n')
            {
                if (c == '\n')
                {
                    lineNumber++;
                }
                comment += c;
            }
        }

        prev = c;


        if (c == '"')
        {
            bool isClosed = false;
            while (dictfile.get(c))
            {
                makeString += c;
                if (c == '\\')
                {
                    if (dictfile.get(c))
                    {
                        if (c == '\n')
                        {
                            lineNumber++;
                        }
                        makeString += c;
                    }
                    continue;


                }
                if (c == '"')
                {
                    isClosed = true;
                    break;
                }

            }

            if (isClosed == false)
                cout << "Missing " << '"' << " on line " << lineNumber << endl;
            else
            {
                cout << "Matching " << '"' << '"' << endl;
            }
        
        }



        if (c == '\'')
        {
            bool isClosed = false;
            while (dictfile.get(c))
            {
                if (c == '\n')
                
                makeString += c;
                if (c == '\\')
                {
                    if (dictfile.get(c))
                    {
                        if (c == '\n')
                        
                        makeString += c;
                    }
                    continue;


                }
                if (c == '\'')
                {
                    isClosed = true;
                    break;
                }

            }

            if (isClosed == false)
                cout << "Missing ' " << " on line " << lineNumber << endl;
            else
            {
                cout << "Matching '' " << endl;
            }

        }

       

      
        if (c == '(' || c == '{' || c == '[')
        {
            line.push(lineNumber);
            S.push(c);
        }

        else if (c == ')' || c == '}' || c == ']')
        {
            if (S.empty())
            {
                match = false;
                break;
            }
            d = S.top();
            line.pop();
            S.pop();


            cout << "Stack top: " << d << ", current: " << c << endl;


            if (c == ')' && d != '(' ||
                c == '}' && d != '{' ||
                c == ']' && d != '[')
            {
                match = false;
                break;
            }
           
        }
       
    }
    if (!line.empty())
    {
        int missing = line.top();
        if (S.top() == '(')
            cout << "Unmatched ) symbol at line " << missing << endl;
        if (S.top() == '{')
            cout << "Unmatched } symbol at line " << missing << endl;
        if (S.top() == '[')
            cout << "Unmatched ] symbol at line " << missing << endl;
        match = false;
    }

   
    if (!S.empty())
    {
        match = false;
    }
    

    if (match == true)
        cout << "Parentheses match" << endl;
    else
    {
        cout << "Parentheses do not match" << endl;
    }
    return match;
}

int main()
{
    ifstream infile;
    string filename;

    cout << "Please enter filename for C++ code: ";
    cin >> filename;
    infile.open(filename.c_str());

    if (!infile) {
        cout << "File not found!" << endl;
        return (1);
    }

    printFile(infile);
    infile.clear();
    infile.seekg(0, infile.beg);

    if (balanceFile(infile))
        cout << "balance ok" << endl;
}
