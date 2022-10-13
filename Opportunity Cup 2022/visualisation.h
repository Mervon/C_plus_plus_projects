#pragma once

#include "common.h"
class Visualisation : Solver {
public:
    static void MakeDataForPython(const json& data);
    static void MakeDataForPython_2(const json& data);
};