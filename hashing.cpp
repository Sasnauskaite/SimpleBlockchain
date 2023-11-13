#include "class.h"

//Function that generates users
int GenerateUsers()
{
    string username, publicKey;
    int r, currency;
    //gets the information that is stored in users.txt file
    ofstream out("users.txt");
    srand((unsigned int)time(NULL));
    //loop starts
    for(int j=0; j<UserNumb; j++)
    {
        //loop in loop
        for (int i=0; i<4; i++)
        {
            r = rand() % 51;
            username += letters[r];
        }
        //another loop
        for (int i=0; i<5; i++)
        {
            r = rand() % 10;
            username += to_string(r);
        }
        //once another loop
        for (int i=0; i<num; i++)
        {    
            r = rand() % 51;
            publicKey += letters[r];
        }
        //gets random number from 0 to 1000000
        r = rand() % 1000000;
        //currency is that random number
        currency = r;
        //output of user and his/her public key and currecy
        out<<username<<" "<<publicKey<<" "<<currency<<"\n";
        username.clear();
        publicKey.clear();
    }
    out.close();
}
//hashing function that gets string type variable
string HASHING2(string text)
{
    srand((unsigned int)time(NULL));
    string code;
    //clearing the code variable to be empty
    code.clear();
    //declaring string vector and other variables
    vector <string> arr;
    string temp, temprorary;
    long int integer, tempp;
    int sizes, index, n=64;
    int INPUTsize = text.size();
    //declaring ii that is = 0
    int ii= 0;
    if(INPUTsize > 6) //checking if input size is more than 6
    {
        string::size_type i = 0;
        while( i < text.size() && arr.size() < 6) 
        {
            temp = text[i];
            //adding temp to the end of an array
            arr.push_back(temp);
            i=i+3;
        }
    }
    else// if input size is less than or equal 6
    {
        for (string::size_type i = 0; i < text.size(); i++) 
        {
            tempp = rand() % 69;
            //adding temp to the end of an array
            temp = letters[tempp];
            arr.push_back(temp);
        }
    }
    int m=code.size();
    //loop
    for(int i = 0; i<arr.size(); i++)
    {
        for(int j=0; j<52; j++)
        {
            //checking if element i in array is equal to element j in letters
            if(arr[i] == letters[j])
            {
                integer = 0;
                integer = numbers[j+5] * INPUTsize;
                integer = integer + ((integer+5)* (INPUTsize * (j + j + 3)));
                //checking if integer is less than 0
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
    //
    while(code.size() < 64)
    {
        //isSecret is chosen as a random number from 0 to 69
        int iSecret = rand() % 69;
        int change = numbers[iSecret+x]*(INPUTsize+i);
        change = change % 10;
        //see if change is less than 0
        if(change<0)
        {
            change=change*(-1);
        }
        //make code a string value
        code += to_string(change);
        iSecret = rand() % 51;
        code = code + letters[iSecret];
        i++;
        if(i >= 70)
        {
            i=0;
        }
    }

    //loop while the code size is more or equal to 65
    while(code.size() >= 65)
    {
        code.erase(code.end()-1);
    }  
    return code;
}
