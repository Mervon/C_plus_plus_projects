#pragma once

#include <string>

#include "common.h"

class Fraud_4 : public Solver {
public:
    static std::string Solve(const json& data, int interval, int amount);
};

