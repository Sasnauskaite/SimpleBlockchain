#include "hashing.cpp"

using namespace std;

int main()
{
    User users;
    Transactions transfer;
    Chain chain;
    //Transactions2 tr2;
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
    //while(TransNum>transfers_to_block){
        cout<<"...Choosing transactions to put to new block..."<<endl;
        transfer.Choose_transactions();
        cout<<"TRANSACTIONS CHOSEN!"<<endl;
        cout<<"...Hashing Merkle Root of new block..."<<endl;
        blocks.MerkleRoot(transfer);
        cout<<"MERKLE ROOT HASHED!"<<endl;
        cout<<"...Mining..."<<endl;
        chain.Mining();
        cout<<"MINED!"<<endl;
    //};
    return 0;
}