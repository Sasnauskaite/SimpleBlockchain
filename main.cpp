#include <iostream>
#include <fstream>
#include "hashing.cpp"
#include "class.h"

using namespace std;

int main()
{
    User users;
    Transaction transfer;
    Block blocks;
    cout<<"...SIMPLE BLOCKCHAIN..."<<endl;
    cout<<"...Generating "<< UserNumb <<" users..."<<endl;
    GenerateUsers();
    users.ReadUsers();
    cout<<"USERS GENERATED!"<<endl;
    cout<<"...Generating "<< TransNum <<" transactions..."<<endl;
    transfer.generate_transactions(users);
    transfer.Get_id();
    transfer.show_transactions();
    cout<<"TRANSACTIONS GENERATED!"<<endl;
    cout<<"...Choosing transactions to put to block..."<<endl;
    transfer.Choose_transactions();
    cout<<"TRANSACTIONS CHOSEN!"<<endl;
    blocks.MerkleRoot(transfer);
    return 0;
}