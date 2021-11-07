#include <string>
using std::string;

class User {
    protected:
        vector<string> UserName;
        vector<string> publicKey;
        vector<int> currencyBal;
        friend class Transaction;
    public:
        void ReadUsers()
        {
            ifstream in("users.txt");
            string tempName, tempKey;
            int temp;
            for(int j=0; j<UserNumb; j++)
            {
                in>>tempName>>tempKey>>temp;
                UserName.push_back(tempName);
                publicKey.push_back(tempKey);
                currencyBal.push_back(temp);
                in.ignore(10, '\n');
            }
        }
        void printUsers()
        {
            for(int i=0; i<UserNumb; i++)
            {
                cout<<UserName[i]<<" "<<publicKey[i]<<" "<<currencyBal[i]<<endl;
            }
        }
};
class Transaction {
    protected:
        vector<string> sender;
        vector<string> payee;
        vector<int> amount;
        vector<string> ID;
    public:
		void generate_transactions(User& users)
        {
            srand((unsigned int)time(NULL));
            int random;
            for(int i=0; i<TransNum; i++)
            {
                string some_string;
                int r = UserNumb-1;
                random = rand() % r;
                some_string = users.publicKey[random];
                sender.push_back(some_string);
                random = rand() % r;
                some_string = users.publicKey[random];
                do
                {
                    random = rand() % r;
                    some_string = users.publicKey[random];
                }while(sender[sender.size()]==some_string);
                payee.push_back(some_string);
                random = rand() % 1000000;
                amount.push_back(random);
            }
        }
        void Get_id()
        {
            string fields;
            for(int i=0; i<TransNum; i++)
            {
                fields = sender[i] + payee[i] + to_string(amount[i]);
                ID.push_back(HASHING2(fields));
            }
        }
        void show_transactions()
        {
            ofstream out("transactions.txt");
            for(int i=0; i<TransNum; i++)
            {
                out<<sender[i]<<" "<<amount[i]<<" "<<payee[i]<<endl;
            }
        }
};
class Block
{
    private: 
        int PrevBlockHash;
        double timestamp;
        int Version;
        string MerkelRootHash;
        int Nonce;
        int Difficulty;
    public:
    
};
