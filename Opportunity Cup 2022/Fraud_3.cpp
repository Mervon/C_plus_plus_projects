#include "Fraud_3.h"
#include "common.h"

using namespace std;

string Fraud_3::Solve(const json& data, const string& expiredKey) {
    map<string, string> check;

    long long int max = -1;
    string transaction;
    string max_transaction;

    for (auto& item : data["transactions"sv].items()) {
        string keyValidTo;

        transaction = item.key();

        for (auto &item_1: item.value().items())
        {
            if(item_1.key() == "oper_result" && item_1.value().get<string>() == "Успешно")
                for (auto &item_2: item.value().items()) {
                    if (item_2.key() == expiredKey) {
                        keyValidTo = item_2.value().get<string>();
                        for (auto &item_3: item.value().items()) {
                            if (item_3.key() == "date") {
                                if (convertStringDateToSeconds(keyValidTo) <
                                    convertStringDateToSeconds(item_3.value().get<string>())) {
                                    if (max < DateToNumber(item_3.value().get<string>()) - DateToNumber(keyValidTo)) {
                                        max = DateToNumber(item_3.value().get<string>()) - DateToNumber(keyValidTo);
                                        max_transaction = transaction;
                                    }
                                    check[item.key()] = keyValidTo + " " + item_3.value().get<string>();
                                }
                            }
                        }
                    }
                }
        }
    }

    string res_filename = "BIG_RES_" + to_string(GLOBAL_NUMBER_OF_OUTPUTS++) + ".txt";

    ofstream ofs(res_filename, ios_base::trunc);

    ofs << check.begin()->first;
    for (auto it = next(check.begin()); it != check.end(); ++it) {
        ofs << ", " << it->first;
    }

    //cout << max_transaction << endl;

    return res_filename;
}