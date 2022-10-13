#include "common.h"

class Fraud_7 : public Solver {
public:
    static std::string Solve(const json& data, int interval, int suspicious_start, int amount);
};
