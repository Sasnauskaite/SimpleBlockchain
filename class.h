#pragma Once

#include <ctime>
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
int UserNumb = 1000, TransNum = 10000, transfers_to_block=128;//UserNumb=vartotoju skaicius; TransNum=transakciju skaicius; 
//transfers=transakciju, kurios bus dedamos i bloka numeriai
int num = 50; //Public key ilgis
int Block_num = 0;//kiek viso yra blokų
int hashrate=50000, block=0;
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
string HASHING2(string text);

class User {
    protected:
        vector<string> UserName;
        vector<string> publicKey;
        vector<int> currencyBal;
        friend class Transactions;
        friend class Block;
    public:
        void ReadUsers() {
            ifstream in("users.txt");
            string tempName, tempKey;
            int temp;
            for(int j=0; j<UserNumb; j++) {
                in>>tempName>>tempKey>>temp;
                UserName.push_back(tempName);
                publicKey.push_back(tempKey);
                currencyBal.push_back(temp);
                in.ignore(10, '\n');
            }
        }
        void printUsers() {
            for(int i=0; i<UserNumb; i++) {
                cout<<UserName[i]<<" "<<publicKey[i]<<" "<<currencyBal[i]<<endl;
            }
        }
};
class Transactions {
    protected:
        vector<string> sender;
        vector<string> payee;
        vector<int> amount;
        vector<string> ID;
        vector<int> put_to_block;
        friend class Block;
    public:
		void generate_transactions(User& users) {
            srand((unsigned int)time(NULL));
            int random;
            for(int i=0; i<TransNum; i++) {
                string some_string;
                int r = UserNumb-1;
                random = rand() % r;
                some_string = users.publicKey[random];
                sender.push_back(some_string);
                random = rand() % r;
                some_string = users.publicKey[random];
                do {
                    random = rand() % r;
                    some_string = users.publicKey[random];
                }while(sender[sender.size()]==some_string);
                payee.push_back(some_string);
                random = rand() % 1000000;
                amount.push_back(random);
            }
        }
        void Get_id() {
            string fields;
            for(int i=0; i<TransNum; i++) {
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
        void Choose_transactions() {
            int temp;
            srand((unsigned int)time(NULL));
            for(int i=0; i<transfers_to_block; i++) {
                put_to_block.push_back(rand() % TransNum);
            }
            ofstream out("to_block.txt");
            for(int i=0; i<transfers_to_block; i++) {
                temp = put_to_block[i];
                out<<ID[temp]<<" "<<sender[temp]<<" "<<amount[temp]<<" "<<payee[temp]<<endl;
            }
        }
};
class Block {
    private: 
        string PrevBlockHash;
        string Hash;
        string timestamp;
        int Version;
        string MerkleRootHash;//gaunasi
        int Nonce;
        int Difficulty; 
        friend class Chain;
    public:
        void MerkleRoot(Transactions& tr) {
            string toHash;
            int times;
            vector<string> first;
            vector<string> second, third;
            int temp;
            for(int i=0; i<transfers_to_block; i++) {
                temp = tr.put_to_block[i];
                toHash = tr.sender[temp] + to_string(tr.amount[temp]) + tr.payee[temp];
                toHash = HASHING2(toHash);
                first.push_back(toHash);
            }
            times = transfers_to_block;
            for(int j=0; j<7; j++) {
                for(int ii=0; ii<times; ii++) {
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
            MerkleRootHash=first[0];
        } 
};
class Chain {
    public:
        void Mining() {
            srand((unsigned int)time(NULL));
            int duration, mine, diff;
            string genesys, stringDate, toHash, hashh, to_block;
            Block block;
            if(Block_num==0) {
                genesys="0000000000000000000000000000000000000000000000000000000000000000"; //64 nuliai
                block.PrevBlockHash=genesys;
                block.Difficulty=1000;//lengviausias imanomas sudetingumas yra toks, kuris sutampa 
                //--------------------------su galimu atsitikriniu skaiciu aibe arba yra uz ja didesnis
                auto start = std::chrono::steady_clock::now();
                while(mine>block.Difficulty){
                    mine=rand()% 1000;
                };
                duration=chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - start).count();
                block.Nonce=mine;
                cout<<"NEW NONCE FOUND!"<<endl;
                toHash=to_string(mine);
                hashh=HASHING2(toHash);
                block.Hash=hashh;           
                time_t now = time(0);
                char* date_time = ctime(&now);
                stringDate=date_time;//stringDate.append(date_time);
                start=std::chrono::steady_clock::now();
                block.timestamp=date_time;
                block.Version=2;
                cout<<Block_num<<" block header: "<<endl;
                cout<<"Previous Block Hash: "<<block.PrevBlockHash<<endl;//yra
                cout<<"Hash: "<<block.Hash<<endl;//yra
                cout<<"Timestamp: "<<block.timestamp;//yra
                cout<<"Version: "<<block.Version<<endl;//yra
                cout<<"Merkle Root Hash: "<<block.MerkleRootHash<<endl;//yra
                cout<<"Nonce: "<<block.Nonce<<endl;//yra
                cout<<"Difficulty target: "<<block.Difficulty<<endl;//yra
                diff=(duration*hashrate)/64;//2 pakelta 10 yra 1024 emiau paprastesni 
                //-------------------------------skaiciu, kad algoritmas nebutu per sudetingas
                block.Difficulty=diff;
                Block_num++;
                TransNum-=transfers_to_block;
            }
        }
};