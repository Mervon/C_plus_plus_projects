#include "common.h"

#include <iostream>

using namespace std;
using json = nlohmann::json;

string SortDataByKey(const json& document, const string& sorting_key) {
    json result;

    for (auto& item: document["transactions"sv].items()) {
        std::string key;
        std::string transaction = item.key();

        for (auto& items: item.value().items()) {
            if (items.key() == sorting_key) {
                if (items.value().is_string()) {
                    key = items.value().get<std::string>();
                } else {
                    key = to_string(items.value().get<int>());
                }
            }
        }

        auto a = item.value();
        a.push_back({"transaction", transaction});
        result["transactions"sv][key].push_back(a);
    }

    string result_filename = "Sorted_by_" + sorting_key + ".json";

    std::ofstream res_file(result_filename, ios_base::trunc);

    res_file << result.dump(4);

    return result_filename;
}

long long int DateToNumber(const string& date) {
    long long int year, month, day, hour, minute, sec;
    try {
        year = stoi(date.substr(0, 4)) * 365 * 24 * 3600;
        month = stoi(date.substr(5, 2)) * 30 * 24 * 3600;
        day = stoi(date.substr(8, 2)) * 24 * 3600;
        hour = stoi(date.substr(11, 2)) * 3600;
        minute = stoi(date.substr(14, 2)) * 60;
        sec = stoi(date.substr(17, 2));
        return year + month + day + hour + minute + sec;
    }
    catch (exception& e) {
        cerr << "DateToNumber() fall with that date\n:" << date << ":" << endl;
        throw;
    }
}

bool DateIsNight(const string& date) {
    long long int hour;
    try {
        hour = stoi(date.substr(11, 2)) * 3600;
    } catch (exception& e) {
        cerr << "DateIsNight() fall with that date\n:" << date << ":" << endl;
        throw;
    }
    return hour >= 0 && hour < 6;
}