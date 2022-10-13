#pragma once
#include "common.h"
#include <string>

class Fraud_2 : public Solver {
public:
    static std::string Solve(const json& data, const std::string& expiredKey = "account_valid_to");
};
