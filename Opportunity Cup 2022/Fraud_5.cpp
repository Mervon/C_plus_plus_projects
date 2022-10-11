#include "Fraud_5.h"
#include "common.h"

#include <string>
#include <fstream>
#include <vector>
#include <set>
#include "C:\GitRepos\Json\json\single_include\nlohmann\json.hpp"
#include "C:\GitRepos\Json\json\single_include\nlohmann\json_fwd.hpp"

using namespace std;
using json = nlohmann::json;

void Fraud_5::Solve(const string& filename, long long int interval) {
    ifstream ifs(filename);
    json data = json::parse(ifs);

    vector<string> result;

    for (auto& item_1: data["transactions"].items()) {
        string prev_data, current_data;
        string prev_city, current_city;
        string prev_transaction, curr_transaction;

        bool skip_first = true;

        for (auto& item_2: item_1.value().items()) {
            if (skip_first) {
                for (auto& item_3: item_2.value().items()) {
                    if (item_3.key() == "date") {
                        prev_data = item_3.value();
                    } else if (item_3.key() == "city") {
                        prev_city = item_3.value();
                    } else if (item_3.key() == "transaction") {
                        prev_transaction = item_3.value();
                    }
                }
                skip_first = false;
                continue;
            } else {
                for (auto& item_3: item_2.value().items()) {
                    if (item_3.key() == "date") {
                        current_data = item_3.value();
                    } else if (item_3.key() == "city") {
                        current_city = item_3.value();
                    } else if (item_3.key() == "transaction") {
                        curr_transaction = item_3.value();
                    }
                }

                long long int prev = DateToNumber(prev_data);
                long long int curr = DateToNumber(current_data);

                if (std::abs(curr - prev) <= interval && current_city != prev_city) {
                    result.push_back(prev_transaction);
                    result.push_back(curr_transaction);

                }

                prev_data = current_data;
                prev_transaction = curr_transaction;
                prev_city = current_city;
            }
        }
    }

    std::set<string> res;

    for (auto& item: result) {
        res.insert(item);
    }
    ofstream ofs_2("BIG_RES_5.txt");

    bool is_first = false;

    for (auto& item: res) {
        if (is_first) {
            ofs_2 << ", ";
        }
        is_first = true;
        ofs_2 << item;
    }
}
