#include "Fraud_7.h"

using namespace std;

string Fraud_7::Solve(const json& data, int interval, int suspicious_start, int amount) {
    map<string,vector<map<string, vector<string>>>> transactions_save;
    set<string> res;

    for (auto& item : data["transactions"].items()) {
        map<string, vector<string>> transactions;
        for (auto& item2 : item.value().items())
            for(auto& item3 : item2.value().items())
                if ((string) item3.key() == "date")
                    for (auto& item4 : item2.value().items())
                        if((string)item4.key() == "transaction")
                            for(auto& item5 : item2.value().items())
                                if((string)item5.key() == "oper_type")
                                    for(auto& item6 : item2.value().items())
                                        if((string)item6.key() == "oper_result")
                                            for(auto& item7 : item2.value().items())
                                                if((string)item7.key() == "amount")
                                                    transactions[item4.value().get<string>()] = { item3.value().get<string>(), item5.value().get<string>(), item6.value().get<string>(), to_string(item7.value().get<double>()) };
        int lengthOfInterval = 1;
        pair<string, vector<string>> previd;
        map<string, vector<string>> transactions2;
        double sum = 0;
        for (auto item2 : transactions) {
            if (!previd.second.empty()) {
                if (abs(convertStringDateToSeconds(item2.second.at(0))-convertStringDateToSeconds(previd.second.at(0))) <= interval) {
                    if (lengthOfInterval++ == 1) {
                        transactions2[previd.first] = previd.second;
                    }
                    transactions2[item2.first] = item2.second;
                } else {
                    if (lengthOfInterval > amount) {
                        for (auto &item3 : transactions2) {
                            if((item3.second.at(1) == "Снятие" || item3.second.at(1) == "Оплата") && item3.second.at(2) == "Успешно")
                                sum -= atof(item3.second.at(3).c_str());
                            if(item3.second.at(1) == "Пополнение" && item3.second.at(2) == "Успешно")
                                sum += atof(item3.second.at(3).c_str());
                        }
                    }
                    if(sum < 0)
                        transactions_save[item.key()].push_back(transactions2);
                    transactions2.clear();
                    lengthOfInterval = 1;
                }
            }
            previd = item2;
        }
        if (lengthOfInterval > amount) {
            for (auto &item3 : transactions2) {
                if((item3.second.at(1) == "Снятие" || item3.second.at(1) == "Оплата") && item3.second.at(2) == "Успешно")
                    sum -= atof(item3.second.at(3).c_str());
                if(item3.second.at(1) == "Пополнение" && item3.second.at(2) == "Успешно")
                    sum += atof(item3.second.at(3).c_str());
            }
        }
        if(sum < -1 * suspicious_start) {
            transactions_save[item.key()].push_back(transactions2);
        }
        if (sum < -1 * suspicious_start) {
            for (auto &item2 : transactions2) {
                res.insert(item2.first);
            }
        }
    }

    string res_filename = "BIG_RES_" + to_string(GLOBAL_NUMBER_OF_OUTPUTS++) + ".txt";

    ofstream ofs(res_filename, ios_base::trunc);

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