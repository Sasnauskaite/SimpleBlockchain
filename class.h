#include <string>
using std::string;

class User {
    protected:
        string privateKey = HASHING2(publicKey);
    public:
        string name;
		string publicKey;
        int currencyBal;
        void printUsers()
        {
            cout<<name<<" "<<publicKey<<" "<<currencyBal<<endl;
        }
};
class Transaction {
    protected:
        string fields = sender + payee + to_string(amount);
        string ID = HASHING2(fields);
    public:
		string sender;
        string payee;
        int amount;
};
class Block
{
    private: //nz ar public, ar private
        int PrevBlockHash;
        double timestamp;
        int Version;
        string MerkelRootHash;
        int Nonce;
        int Difficulty;
    public:
    
};
