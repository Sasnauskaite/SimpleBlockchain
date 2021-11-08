#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <stdlib.h>
#include <time.h>

using namespace std;
int UserNumb = 1000, TransNum = 10000, transfers=128;//UserNumb=vartotoju skaicius; TransNum=transakciju skaicius; 
//transfers=transakciju, kurios bus dedamos i bloka numeriai
int num = 100; //Public key ilgis
string letters [52] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", 
"K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", 
"Z", "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", 
"o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
int numbers [70] = {1111, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 
9999, 1112, 2223, 3334, 4445, 5556, 6667, 7778, 8889, 9990, 1123,
2234, 3345, 4456, 5567, 678, 7789, 8890, 9901, 1134, 2345, 3346, 
4567, 5578, 6689, 7780, 8801, 9912, 1245, 2346, 3567, 4578, 5789, 
6890, 7801, 8912, 9134, 9685, 6852, 3857, 8574, 5241, 2740, 7496,
9745, 9765, 8654, 7643, 6532, 5421, 4320, 3209, 2098, 1987, 1375, 
8640, 5657, 8989, 5356, 2525, 6523, 1259};

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
    long int integer;
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
            temp = text[i];
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