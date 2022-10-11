#include "Fraud_6.h"
#include "common.h"

#include <fstream>
#include <vector>
#include <set>

#include "C:\GitRepos\Json\json\single_include\nlohmann\json.hpp"
#include "C:\GitRepos\Json\json\single_include\nlohmann\json_fwd.hpp"

using namespace std;
using json = nlohmann::json;

void Fraud_6::Solve(const string& filename) {
    ifstream ifs(filename);
    json data = json::parse(ifs);

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

        if (is_good && transactions.size() > 2) {
            for (auto& item: transactions) {
                result.insert(item);
            }
        }
    }

    ofstream ofs_2("BIG_RES_6.txt");

    bool is_first = false;

    for (auto& item: result) {
        if (is_first) {
            ofs_2 << ", ";
        }
        is_first = true;
        ofs_2 << item;
    }
}