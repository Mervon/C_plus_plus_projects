#pragma once

#include <string>

#include "common.h"

class Fraud_3 : public Solver {
public:
    static std::string Solve(const json& data, const std::string& expiredKey = "passport_valid_to");
};
