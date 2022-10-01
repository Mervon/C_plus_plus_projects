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
        std::string aa, dd, ee, ff, gg, key;
        std::string bb;
        std::string cc;

        for (auto& items : item.value().items()) {
            if (items.key() == "last_name"sv)   {
                aa = items.value().get<std::string>();
            }
            if (items.key() == "first_name"sv)   {
                bb = items.value().get<std::string>();
            }
            if (items.key() == "patronymic"sv)   {
                cc = items.value().get<std::string>();
            }
            if (items.key() == "passport"sv)   {
                if (items.value().type_name() == "string") {
                    dd = items.value().get<std::string>();
                } else {
                    dd = to_string(items.value().get<int>());
                }
            }
            if (items.key() == "date_of_birth"sv)   {
                ee = items.value().get<std::string>();
            }
            if (items.key() == "phone"sv)   {
                ff = items.value().get<std::string>();
            }
            if (items.key() == "client"sv)   {
                key = items.value().get<std::string>();
            }



        }

        aa += bb;
        aa += cc;
        aa += dd;
        aa += ee;
        aa += ff;

        auto a = item.value();
        a.erase("last_name");
        a.erase("first_name");
        a.erase("patronymic");
        a.erase("phone");
        a.erase("first_name");
        a.erase("passport_valid_to");
        a.erase("passport");
        //a.erase("account");
        a.erase("account_valid_to");
        a.erase("date_of_birth");
        //a.erase("card");
        //a.erase("client");

        result["transactions"sv][key].push_back(a);
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
    std::set<std::pair<int, std::string>> s;  // The new (temporary) container.

    for (auto const &kv : check)
        s.emplace(kv.second, kv.first);  // Flip the pairs.

    ofstream ofs("res2_2.txt");

    for (auto it = --s.end(); it != s.begin(); --it) {
        ofs << it->second << ":" << it->first << endl;
    }
    ofs << s.begin()->second << ":" << s.begin()->first << endl;
}

void SearchForMaxUsersAndUniqueCards(const string& filename) {
    ifstream ifs(filename);
    json data = json::parse(ifs);

    map<string, set<string>> check;
    for (auto& item : data["transactions"sv].items()) {
        for (auto& item_2 : item.value().items()) {
            cout << item_2.key() << endl;
        }
    }

    cout << 1 << endl;
    std::set<std::pair<int, std::string>> s;  // The new (temporary) container.
    cout << 1 << endl;
    for (auto const &kv : check)
        s.emplace(kv.second.size(), kv.first);  // Flip the pairs.
    cout << 1 << endl;
    ofstream ofs("res2_3.txt");
    cout << 1 << endl;
    for (auto it = --s.end(); it != s.begin(); --it) {
        ofs << it->second << ":" << it->first << endl;
    }
    cout << 1 << endl;
    ofs << s.begin()->second << ":" << s.begin()->first << endl;
    cout << 1 << endl;
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
    SortByUser(data, "sorted_2.json");
    SearchForMaxUsers("sorted_2.json");
    SearchForMaxUsersAndUniqueCards("sorted_2.json");
}


