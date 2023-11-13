#include "class.h"

int GenerateUsers()
{
    string username, publicKey;
    int r, currency;
    ofstream out("users.txt");
    srand((unsigned int)time(NULL));
    for(int j=0; j<UserNumb; j++)
    {
        for (int i=0; i<4; i++)
        {
            r = rand() % 51;
            username += letters[r];
        }
        for (int i=0; i<5; i++)
        {
            r = rand() % 10;
            username += to_string(r);
        }
        for (int i=0; i<num; i++)
        {    
            r = rand() % 51;
            publicKey += letters[r];
        }
        r = rand() % 1000000;
        currency = r;
        out<<username<<" "<<publicKey<<" "<<currency<<"\n";
        username.clear();
        publicKey.clear();
    }
    out.close();
}
string HASHING2(string text)
{
    srand((unsigned int)time(NULL));
    string code;
    code.clear();
    vector <string> arr;
    string temp, temprorary;
    long int integer, tempp;
    int sizes, index, n=64;
    int INPUTsize = text.size();
    int ii= 0;
    if(INPUTsize > 6)
    {
        string::size_type i = 0;
        while( i < text.size() && arr.size() < 6) 
        {
            temp = text[i];
            arr.push_back(temp);
            i=i+3;
        }
    }
    else
    {
        for (string::size_type i = 0; i < text.size(); i++) 
        {
            tempp = rand() % 69;
            temp = letters[tempp];
            arr.push_back(temp);
        }
    }
    int m=code.size();
    for(int i = 0; i<arr.size(); i++)
    {
        for(int j=0; j<52; j++)
        {
            if(arr[i] == letters[j])
            {
                integer = 0;
                integer = numbers[j+5] * INPUTsize;
                integer = integer + ((integer+5)* (INPUTsize * (j + j + 3)));
                if(integer<0)
                    integer=integer*(-1);
                temprorary = ' ';
                temprorary = letters[j+1];
                code += to_string(integer);
                code += temprorary;
            }
        }
    }

    int i = 0, x=5;
    while(code.size() < 64)
    {
        int iSecret = rand() % 69;
        int change = numbers[iSecret+x]*(INPUTsize+i);
        change = change % 10;
        if(change<0)
        {
            change=change*(-1);
        }
        code += to_string(change);
        iSecret = rand() % 51;
        code = code + letters[iSecret];
        i++;
        if(i >= 70)
        {
            i=0;
        }
    }
    
    while(code.size() >= 65)
    {
        code.erase(code.end()-1);
    }  
    return code;
}
