#include "Fraud_1.h"

using namespace std;

string Fraud_1::Solve(const json& data, int amount) {
    set<string> bad_transactions;

    for (auto& item: data["transactions"].items()) {
        set<string> unique_cards;
        vector<string> cards;
        vector<string> transactions;
        for (auto& item2: item.value().items()) {

            for (auto& item3: item2.value().items()) {
                if (item3.key() == "card") {
                    unique_cards.insert(item3.value());
                    cards.push_back(item3.value());
                }

                if (item3.key() == "transaction") {
                    transactions.push_back(item3.value());
                }
            }
        }

        if (unique_cards.size() > amount) {
            for (auto& transaction: transactions) {
                bad_transactions.insert(transaction);
            }
        }

        transactions.clear();
        unique_cards.clear();
        cards.clear();
    }

    string res_filename = "BIG_RES_" + to_string(GLOBAL_NUMBER_OF_OUTPUTS++) + ".txt";

    ofstream ofs(res_filename);

    bool is_first = false;

    for (auto& item: bad_transactions) {
        if (is_first) {
            ofs << ", ";
        }
        is_first = true;
        ofs << item;
    }

    return res_filename;
}