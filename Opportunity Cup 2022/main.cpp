/*
 * Исходный код руководителя проекта Клименко Александра Дмитриевича
 * Использовался стандарт языка С++17 и сторонняя библиотека для работы с json:
 * nlohmann json с открытым исходным кодом - "https://github.com/nlohmann/json"
 * Данная программа решает задачу о поиске в исходном файле transactions.json
 * Транзакций, попадающих под 5 и 6 fraud-паттерны соответсвенно
 * Результат выполнения программы - два файла "BIG_RES_5.txt" и "BIG_RES_6.txt"
 * в "BIG_RES_5.txt" находятся все транзакции попавшие под 5 паттерн
 * в "BIG_RES_6.txt" находятся все транзакции попавшие под 6 паттерн
 * Так же данный код можно найти в Git репозитории:
 * "https://github.com/Mervon/C_plus_plus_projects/tree/main/Opportunity%20Cup%202022"
*/

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

#include "Fraud_5.h"
#include "Fraud_6.h"
#include "common.h"

using namespace std;
using json = nlohmann::json;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    string data_filename = "transactions.json";

    ifstream ifs(data_filename);
    json data = json::parse(ifs);

    string sorting_key = "client"s;

    string sorted_data_filename = SortDataByKey(data, sorting_key);

    Fraud_5::Solve(sorted_data_filename, 900);
    Fraud_6::Solve(sorted_data_filename);
}