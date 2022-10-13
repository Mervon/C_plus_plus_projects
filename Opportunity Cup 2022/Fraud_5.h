#pragma once

#include <string>

#include "common.h"

class Fraud_5 : public Solver {
public:
    static std::string Solve(const json& data, long long int interval);
};
