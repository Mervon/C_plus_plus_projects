#pragma once

#include <string>

#include "common.h"

class Fraud_6 : public Solver {
public:
    static std::string Solve(const json& data, int amount);
};

