#include "Fraud_6.h"

using namespace std;

string Fraud_6::Solve(const json& data, int amount) {
    set<string> result;

    for (auto& item_1: data["transactions"].items()) {
        string prev_data, current_data;
        string prev_city, current_city;
        string prev_transaction, curr_transaction;
        string date;
        vector<string> transactions;

        bool is_good = true;

        for (auto& item_2: item_1.value().items()) {
            for (auto& item_3: item_2.value().items()) {
                if (item_3.key() == "date") {
                    date = item_3.value();
                } else if (item_3.key() == "transaction") {
                    transactions.push_back(item_3.value());
                }
            }

            if (!DateIsNight(date)) {
                is_good = false;
                break;
            }
        }

        if (is_good && transactions.size() > amount) {
            for (auto& item: transactions) {
                result.insert(item);
            }
        }
    }

    string res_filename = "BIG_RES_" + to_string(GLOBAL_NUMBER_OF_OUTPUTS++) + ".txt";

    ofstream ofs_2(res_filename, ios_base::trunc);

    bool is_first = false;

    for (auto& item: result) {
        if (is_first) {
            ofs_2 << ", ";
        }
        is_first = true;
        ofs_2 << item;
    }

    return res_filename;
}