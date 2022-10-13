#include "common.h"

using namespace std;

set<string> Solver::GetAllBadTransactions() {
    set<string> all_bad_transaction;
    int i = 1;
    while (i <= GLOBAL_NUMBER_OF_OUTPUTS) {
        string filename = "BIG_RES_" + to_string(i++) + ".txt";
        ifstream ifs(filename);
        string line;
        getline(ifs, line);
        string str;
        for (char c : line) {
            if (c == ',') {
                all_bad_transaction.insert(str);
                str = "";
                continue;
            } else if (c == ' ') {
                continue;
            }

            str += c;
        }
        ifs.close();
    }

    return all_bad_transaction;
}

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

string SortDataByKeyForAnalise(const json& document, const string& sorting_key) {
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
        a.erase("passport_valid_to");
        a.erase("account_valid_to");
        a.erase("first_name");
        a.erase("patronymic");
        a.erase("last_name");
        a.erase("card");
        a.erase("passport");
        a.erase("phone");
        a.erase("client");
        a.erase("date_of_birth");
        a.erase("terminal_type");
        result["transactions"sv][key].push_back(a);
    }

    string result_filename = "Sorted_by_" + sorting_key + "_for_analise.json";

    std::ofstream res_file(result_filename, ios_base::trunc);

    res_file << result.dump(4);

    return result_filename;
}

long long int DateToNumber(const string& date) {
    long long int year, month, day, hour, minute, sec;
    try {
        year = stoi(date.substr(0, 4)) * 365ll * 24ll * 3600ll;
        month = stoi(date.substr(5, 2)) * 30ll * 24ll * 3600ll;
        day = stoi(date.substr(8, 2)) * 24ll * 3600ll;
        hour = stoi(date.substr(11, 2)) * 3600ll;
        minute = stoi(date.substr(14, 2)) * 60ll;
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
        hour = GetHoursFromDate(date);
    } catch (exception& e) {
        cerr << "DateIsNight() fall with that date\n:" << date << ":" << endl;
        throw;
    }
    return hour >= 0 && hour < 6;
}

long long int convertStringDateToSeconds(const string& stringDate) {
    long long int res = (stringDate[2] - '0') * 365 * 24 * 10 * 3600 + (stringDate[3] - '0') * 365 * 24 * 3600 +
                        (stringDate[5] - '0') * 30 * 24 * 10 * 3600 + (stringDate[6] - '0') * 30 * 24 * 3600 +
                        (stringDate[8] - '0') * 24 * 10 * 3600 + (stringDate[9] - '0') * 24 * 3600;
    if (stringDate.length() > 11) {
        res += (stringDate[11] - '0') * 10 * 3600 + (stringDate[12] - '0') * 3600 + (stringDate[14] - '0') * 10 * 60 +
               (stringDate[15] - '0') * 60 + (stringDate[17] - '0') * 10 + (stringDate[18] - '0');
    }
    return res;
}

int GetHoursFromDate(const std::string& date) {
    int hour;
    try {
        hour = stoi(date.substr(11, 2));
    } catch (exception& e) {
        cerr << "GetHoursFromDate() fall with that date\n:" << date << ":" << endl;
        throw;
    }
    return hour;
}