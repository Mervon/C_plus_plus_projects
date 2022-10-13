#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <set>
#include <vector>
#include <filesystem>
#include <cctype>

/*
 * сторонняя библиотека для работа с json в C++, чтобы она заработала, нужно создать папку, куда будем её
 * скачивать, далле запустить git bash и перейти в эту папку посредством команды "cd <Полный путь до созданной папки>"
 * далее прописать команду "git clone https://github.com/nlohmann/json.git"
 * ждать пока скачается и потом подключить библиотеку посредством двух #include директив
*/

#include "libs\JSON_lib\single_include\nlohmann\json.hpp"
#include "libs\JSON_lib\single_include\nlohmann\json_fwd.hpp"
using json = nlohmann::json;

/*
 * сторонняя библиотека для работы с xlxs в C++, аналогичные действия что и с nhloman json,
 * ссылка на открытый гит-репозиторий автора: "https://github.com/troldal/OpenXLSX"
 */

#include "OpenXLSX.hpp"
using namespace OpenXLSX;

class Solver {
public:
    static int GetNumberOfOutputs() {
        return GLOBAL_NUMBER_OF_OUTPUTS;
    }
    static std::set<std::string> GetAllBadTransactions();
protected:
    inline static int GLOBAL_NUMBER_OF_OUTPUTS = 1;
};

std::string SortDataByKey(const nlohmann::json& document, const std::string& sorting_key);

std::string SortDataByKeyForAnalise(const json& document, const std::string& sorting_key);

long long int DateToNumber(const std::string& date);

bool DateIsNight(const std::string& date);

long long int convertStringDateToSeconds(const std::string& stringDate);

void DumpAllToXlsx(std::vector<std::string>& res_filenames);

int GetHoursFromDate(const std::string& date);

struct input_data {
    int value_for_1_pattern = 15;
    int value_for_4_pattern_1 = 900, value_for_4_pattern_2 = 15;
    int value_for_5_pattern = 900;
    int value_for_6_pattern = 10;
    int value_for_7_pattern_1 = 120, value_for_7_pattern_2 = 300000, value_for_7_pattern_3 = 10;
};