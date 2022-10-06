/*
 * Исходный код руководителя проекта Клименко Александра Дмитриевича
 * Использовался стандарт языка С++17 и сторонняя библиотека для работы с json:
 * nlohmann json с открытым исходным кодом - "https://github.com/nlohmann/json"
 * Данная программа решает задачу о поиске в исходном файле transactions.json
 * Транзакций, попадающих под 5 и 6 fraud-паттерны соответсвенно
 * Результат выполнения программы - два файла "BIG_RES_5.txt" и "BIG_RES_5.txt"
 * в "BIG_RES_5.txt" находятся все транзакции попавшие под 5 паттерн
 * в "BIG_RES_6.txt" находятся все транзакции попавшие под 6 паттерн
 * Так же данный код можно найти в Git репозитории:
 * "https://github.com/Mervon/C_plus_plus_projects/tree/main/Opportunity%20Cup%202022"
*/

#include <iostream>
#include <windows.h>
#include <fstream>
#include <set>
#include <cmath>
/*
 * сторонняя библиотека для работа с json в C++, чтобы она заработала, нужно создать папку, куда будем её
 * скачивать, далле запустить git bash и перейти в эту папку посредством команды "cd <Полный путь до созданной папки>"
 * далее прописать команду "git clone https://github.com/nlohmann/json.git"
 * ждать пока скачается и потом подключить библиотеку посредством двух #include директив
*/
#include "C:\GitRepos\Json\json\single_include\nlohmann\json.hpp"
#include "C:\GitRepos\Json\json\single_include\nlohmann\json_fwd.hpp"

using namespace std;
using json = nlohmann::json;

void SortByClient(const json& document, const string& filename) {
    json result;

    for (auto& item : document["transactions"sv].items()) {
        std::string key;
        std::string transaction = item.key();

        for (auto& items : item.value().items()) {
            if (items.key() == "client"sv)   {
                key = items.value().get<std::string>();
            }
        }

        auto a = item.value();
        a.push_back({"transaction", transaction});
        result["transactions"sv][key].push_back(a);
    }

    std::ofstream res_file(filename, ios_base::trunc);

    res_file << result.dump(4);
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
    }
    catch(exception& e) {
        cerr << "DateToNumber() fall with that date\n:" << date << ":" << endl;
    }
    return year + month + day + hour + minute + sec;
}

bool DateIsNight(const string& date) {
    return stoi(date.substr(11, 2)) >= 0 && stoi(date.substr(11, 2)) < 6;
}

void Fraud_5(const string& filename, long long int interval) {
    ifstream ifs(filename);
    json data = json::parse(ifs);

    vector<string> result;

    for (auto& item_1 : data["transactions"].items()) {
        string prev_data, current_data;
        string prev_city, current_city;
        string prev_transaction, curr_transaction;

        bool skip_first = true;

        for (auto& item_2 : item_1.value().items()) {
            if (skip_first) {
                for (auto &item_3: item_2.value().items()) {
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
                for (auto& item_3 : item_2.value().items()) {
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

    for (auto& item : result) {
        res.insert(item);
    }
    ofstream ofs_2("BIG_RES_5.txt");

    bool is_first = false;

    for (auto& item : res) {
        if (is_first) {
            ofs_2 << ", ";
        }
        is_first = true;
        ofs_2 << item;
    }
}

void Fraud_6(const string& filename) {
    ifstream ifs(filename);
    json data = json::parse(ifs);

    set<string> result;

    for (auto& item_1 : data["transactions"].items()) {
        string prev_data, current_data;
        string prev_city, current_city;
        string prev_transaction, curr_transaction;
        string date;
        vector<string> transactions;

        bool is_good = true;

        for (auto& item_2 : item_1.value().items()) {
            for (auto& item_3 : item_2.value().items()) {
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
            for (auto& item : transactions) {
                result.insert(item);
            }
        }
    }

    ofstream ofs_2("BIG_RES_6.txt");

    bool is_first = false;

    for (auto& item : result) {
        if (is_first) {
            ofs_2 << ", ";
        }
        is_first = true;
        ofs_2 << item;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string data_filename = "transactions.json";

    ifstream ifs(data_filename);

    json data = json::parse(ifs);

    string data_sorted_by_client_filename = "sortedByClient.json";

    SortByClient(data, data_sorted_by_client_filename);

    Fraud_5(data_sorted_by_client_filename, 900);
    Fraud_6(data_sorted_by_client_filename);
}