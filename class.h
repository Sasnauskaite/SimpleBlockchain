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
        vector<int> put_to_block;
        friend class Block;
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
        void Choose_transactions()
        {
            int temp;
            srand((unsigned int)time(NULL));
            for(int i=0; i<transfers; i++)
            {
                put_to_block.push_back(rand() % TransNum);
            }
            ofstream out("to_block.txt");
            for(int i=0; i<transfers; i++)
            {
                temp = put_to_block[i];
                out<<ID[temp]<<" "<<sender[temp]<<" "<<amount[temp]<<" "<<payee[temp]<<endl;
            }
        }
};
class Block
{
    private: 
        string PrevBlockHash;
        double timestamp;
        int Version;
        string MerkleRootHash;
        int Nonce;
        int Difficulty;
    public:
        void MerkleRoot(Transaction& tr)
        {
            string toHash;
            int times;
            vector<string> first;
            vector<string> second, third;
            int temp;
            for(int i=0; i<transfers; i++)
            {
                temp = tr.put_to_block[i];
                toHash = tr.sender[temp] + to_string(tr.amount[temp]) + tr.payee[temp];
                toHash = HASHING2(toHash);
                first.push_back(toHash);
            }
            times = transfers;
            for(int j=0; j<7; j++)
            {
                for(int ii=0; ii<times; ii++)
                {
                    toHash = first[ii] + first[ii+1];
                    toHash = HASHING2(toHash);
                    second.push_back(toHash);
                    ii++;
                }
                times= times/2;
                first.clear();
                first=second;
                second.clear();
            }
            MerkleRootHash = first[0];
        }
};
