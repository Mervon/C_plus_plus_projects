#include "common.h"

class Testing {
public:
    constexpr static const double EPSILON = -0.0001;

    static bool TestCorrectJson(std::ifstream& input);
    static bool TestCorrectData(const json& data);
private:
    static void TestDate(const std::string& date);
    static bool IsRange(int value, int min, int max);
    static int isLeapYear(int year);
    static bool CheckDate(int day, int month, int year);

    static void TestPassportDate(std::string passport_date);

    static void TestAccountDate(std::string account_date);

    static void TestClient(const std::string& client);

};
