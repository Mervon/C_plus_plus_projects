#include "Fraud_4.h"

using namespace std;

string Fraud_4::Solve(const json& data, int interval, int amount) {
    set<pair<string, long long int>> result;

    std::vector<string> res;

    for (auto& item: data["transactions"].items()) {
        set<pair<string, long long int>> transactions;
        for (auto& item2: item.value().items())
            for (auto& item3: item2.value().items())
                if ((string) item3.key() == "date")
                    for (auto& item4: item2.value().items())
                        if ((string) item4.key() == "transaction")
                            transactions.insert(
                                    {(string) item4.value(), DateToNumber((string) item3.value())});
        long long int lengthOfInterval = 1;
        long long int prev = -1;
        string previd = "0";
        vector<string> transactions2;
        for (auto item_2 = transactions.begin(); item_2 != transactions.end(); ++item_2) {
            if (prev > 0) {
                if ((item_2->second - prev <= interval)) {
                    if (lengthOfInterval++ == 1)
                        transactions2.push_back(previd);
                    transactions2.push_back(item_2->first);
                } else {
                    if (lengthOfInterval >= amount) {

                        /*
                        ofs << item.key() << endl;
                        ofs << "    " << lengthOfInterval << ":" << endl << "       ";
                        for(auto& str : transactions2)
                            ofs << str << " ";
                        ofs << endl;*/
                        //sorted output

                        for (auto& trans : transactions2) {
                            res.push_back(trans);
                        }
                    }
                    transactions2.clear();
                    lengthOfInterval = 1;
                }
            }
            prev = item_2->second;
            previd = item_2->first;
        }

        if (lengthOfInterval > amount) {
           /* ofs << item.key() << endl;
            ofs << "    " << lengthOfInterval << ":" << endl << "       ";
            for(auto& str : transactions2)
                ofs << str << " ";
            ofs << endl;*/

            for (auto& trans : transactions2) {
                res.push_back(trans);
            }
        }
    }

    string res_filename = "BIG_RES_" + to_string(GLOBAL_NUMBER_OF_OUTPUTS++) + ".txt";

    ofstream ofs(res_filename, ios::ios_base::trunc);

    bool is_first = false;

    for (auto& item : res) {
        if (is_first) {
            ofs << ", ";
        }
        is_first = true;

        ofs << item;
    }

    return res_filename;
}