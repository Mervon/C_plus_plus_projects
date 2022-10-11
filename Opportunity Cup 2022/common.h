#pragma once

#include <string>

#include "C:\GitRepos\Json\json\single_include\nlohmann\json.hpp"
#include "C:\GitRepos\Json\json\single_include\nlohmann\json_fwd.hpp"

std::string SortDataByKey(const nlohmann::json& document, const std::string& sorting_key);

long long int DateToNumber(const std::string& date);

bool DateIsNight(const std::string& date);

