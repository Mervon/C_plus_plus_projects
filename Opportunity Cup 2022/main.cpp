#include <iostream>
#include <windows.h>
#include <fstream>
#include <set>
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

void GetAllTransactionsTypes(const json& document, const std::string& filename) {
    std::set<string> result;

    for (auto& item : document["transactions"sv].items()) {
        for (auto& items : item.value().items()) {
            if (items.key() == "oper_type"sv) {
                result.insert(items.value().get<std::string>());
            }
        }
    }

    std::ofstream res_file(filename, ios_base::trunc);

    bool is_first = true;

    for (auto& item : result) {
        if (!is_first) {
            res_file << '\n';
        }

        is_first = false;

        res_file << item;
    }
}

void DeleteAddOperationsFromSource(const json& document, const string& filename) {
    json result = {
            {"transactions"sv, {}}
    };

    for (auto& item : document["transactions"sv].items()) {
        for (auto& items : item.value().items()) {
            if (items.key() == "oper_type"sv) {
                if (items.value().get<std::string>() == "Пополнение"sv) {
                    continue;
                }

                result["transactions"sv].push_back({item.key(), item.value()});
            }
        }
    }

    std::ofstream res_file(filename, ios_base::trunc);

    res_file << result.dump(4);
}

void GetOnlySuccesOperations(const json& document, const string& filename) {
    json result = {
            {"transactions"sv, {}}
    };

    for (auto& item : document["transactions"sv].items()) {
        bool flag1 = false, flag2 = false;
        for (auto& items : item.value().items()) {

            if (items.key() == "oper_type"sv) {
                if (items.value().get<std::string>() == "Оплата"sv || items.value().get<std::string>() == "Снятие"sv) {
                    flag1 = true;
                }
            } else if (items.key() == "oper_result"sv) {
                if (items.value().get<std::string>() == "Успешно"sv) {
                    flag2 = true;
                }
            }
        }

        if (flag1 && flag2) {
            result["transactions"sv].push_back({item.key(), item.value()});
        }
    }

    std::ofstream res_file(filename, ios_base::trunc);

    res_file << result.dump(4);
}

void SortByUser(const json& document, const string& filename) {
    json result;

    for (auto& item : document["transactions"sv].items()) {
        std::string key;

        for (auto& items : item.value().items()) {
            if (items.key() == "account"sv)   {
                key = items.value().get<std::string>();
            }
        }

        result["transactions"sv][key].push_back(item.value());
    }

    std::ofstream res_file(filename, ios_base::trunc);

    res_file << result.dump(4);
}


void SearchForMaxUsers(const string& filename) {
    ifstream ifs(filename);
    json data = json::parse(ifs);

    map<string, int> check;
    for (auto& item : data["transactions"sv].items()) {
        check[item.key()] = item.value().size();
    }

    ofstream ofs("res2.txt");

    for (auto& item : check) {
        if (item.second > 2) {
            ofs << item.first << ":" << item.second << endl;
        }
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string input_file_name = "transactions.json";

    std::ifstream input_file(input_file_name);
    json data = json::parse(input_file);

    GetAllTransactionsTypes(data, "TransactionsTypes.txt");
    DeleteAddOperationsFromSource(data, "result_after_deleting_add.json");
    GetOnlySuccesOperations(data, "OnlySuccesOperations.json");
    SortByUser(data, "sorted.json");
    SearchForMaxUsers("sorted.json");
}


