/*
 * Исходный код руководителя проекта Клименко Александра Дмитриевича
 * Использовался стандарт языка С++17 и пара сторонних библиотек:
 * библиотека для работы с json:
 * nlohmann json с открытым исходным кодом - "https://github.com/nlohmann/json"
 * библиотека для работы с xlsx:
 * OpenXLSX с открытым исходным кодом - "https://github.com/troldal/OpenXLSX"
 * Данная программа решает задачу о поиске в исходном файле transactions.json
 * Транзакций, попадающих под 1, 2, 3, 4, 5 и 6 fraud-паттерны соответсвенно
 * Результат выполнения программы - файлы "BIG_RES_1.txt", "BIG_RES_2.txt",
 * "BIG_RES_3.txt", "BIG_RES_4.txt", BIG_RES_5.txt" и "BIG_RES_6.txt"
 * в "BIG_RES_1.txt" находятся все транзакции, попавшие под 1 паттерн
 * в "BIG_RES_2.txt" находятся все транзакции, попавшие под 2 паттерн
 * в "BIG_RES_3.txt" находятся все транзакции, попавшие под 3 паттерн
 * в "BIG_RES_4.txt" находятся все транзакции, попавшие под 4 паттерн
 * в "BIG_RES_5.txt" находятся все транзакции, попавшие под 5 паттерн
 * в "BIG_RES_6.txt" находятся все транзакции, попавшие под 6 паттерн
 * Так же данный код можно найти в Git репозитории:
 * "https://github.com/Mervon/C_plus_plus_projects/tree/main/Opportunity%20Cup%202022"
*/

#include "Fraud_1.h"
#include "Fraud_2.h"
#include "Fraud_3.h"
#include "Fraud_4.h"
#include "Fraud_5.h"
#include "Fraud_6.h"
#include "Fraud_7.h"
#include "Testing.h"
#include "visualisation.h"
#include "common.h"
#include "XLSX_dumper.h"

using namespace std;

vector<string> SolveAll(const json& data, const json& sorted_data, const input_data& id) {
    vector<string> res_filenames;

    int value_for_1_pattern = id.value_for_1_pattern;
    int value_for_4_pattern_1 = id.value_for_4_pattern_1, value_for_4_pattern_2 = id.value_for_4_pattern_2;
    int value_for_5_pattern = id.value_for_5_pattern;
    int value_for_6_pattern = id.value_for_6_pattern;
    int value_for_7_pattern_1 = id.value_for_7_pattern_1, value_for_7_pattern_2 = id.value_for_7_pattern_2, value_for_7_pattern_3 = id.value_for_7_pattern_3;

    res_filenames.push_back(Fraud_1::Solve(sorted_data, value_for_1_pattern));
    res_filenames.push_back(Fraud_2::Solve(data));
    res_filenames.push_back(Fraud_3::Solve(data));
    res_filenames.push_back(
            Fraud_4::Solve(sorted_data, value_for_4_pattern_1, value_for_4_pattern_2)); // magic consts 85 and 105
    res_filenames.push_back(Fraud_5::Solve(sorted_data, value_for_5_pattern));
    res_filenames.push_back(Fraud_6::Solve(sorted_data, value_for_6_pattern));
    res_filenames.push_back(
            Fraud_7::Solve(sorted_data, value_for_7_pattern_1, value_for_7_pattern_2, value_for_7_pattern_3));

    return res_filenames;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string data_otbor = "transactions.json"s;
    string data_final = "transactions_final.json"s;
    string data_big_final = ""s;

    ifstream ifs_1(data_final);

    json data;

    if (Testing::TestCorrectJson(ifs_1)) {
        ifstream ifs_2(data_final);
        data = json::parse(ifs_2);
        ifs_2.close();
    } else {
        cout << "Given JSON is invalid, check it carefully!" << endl;
        return 0;
    }
    ifs_1.close();

    if (!Testing::TestCorrectData(data)) {
        return 0;
    }

    string sorting_key = "client"s;
    SortDataByKeyForAnalise(data, sorting_key);
    string sorted_data_filename = SortDataByKey(data, sorting_key);
    ifstream ifs_2(sorted_data_filename);
    json sorted_data = json::parse(ifs_2);
    ifs_2.close();

    input_data default_input_data = input_data{};

    vector<string> res_paths = SolveAll(data, sorted_data, default_input_data);
    XLSX_dumper::DumpAllToXlsx(res_paths, default_input_data);

    Visualisation::MakeDataForPython(data);
    Visualisation::MakeDataForPython_2(data);
}