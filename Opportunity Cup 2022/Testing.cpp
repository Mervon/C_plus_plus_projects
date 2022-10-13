#include "Testing.h"

using namespace std;

bool Testing::TestCorrectJson(ifstream& input) {
    bool good = true;
    try {
        json a = json::parse(input);
    } catch (...) {
        cerr << "Bad_json_file" << endl;
        return !good;
    }
    return good;
}

bool Testing::TestCorrectData(const json& data) {
    try {
        for (auto& item_1: data["transactions"s].items()) {
            int size = 0;
            for (auto& item_2: item_1.value().items()) {
                size++;
            }

            if (size != 19) {
                cerr << "Transaction size is incorrect" << endl;
                throw std::runtime_error("");
            }
            string test_str;
            for (auto& item_2: item_1.value().items()) {
                if (item_2.key() != "amount" && item_2.key() != "passport") {
                    try {
                        test_str = item_2.value().get<string>();
                    } catch (...) {
                        cerr << "Wrong type for key" << endl;
                        throw std::runtime_error("");
                    }
                }
            }

            string date, oper_type, oper_result, account_valid_to, passport_valid_to, client;
            double amount;
            for (auto& item_2: item_1.value().items()) {

                if (item_2.key() == "date"s) {
                    date = item_2.value();
                }

                if (item_2.key() == "oper_type"s) {
                    oper_type = item_2.value();
                }

                if (item_2.key() == "oper_result"s) {
                    oper_type = item_2.value();
                }

                if (item_2.key() == "amount"s) {
                    amount = item_2.value();
                }

                if (item_2.key() == "passport_valid_to"s) {
                    passport_valid_to = item_2.value();
                }

                if (item_2.key() == "account_valid_to"s) {
                    account_valid_to = item_2.value();
                }

                if (item_2.key() == "client"s) {
                    client = item_2.value();
                }

            }

            TestDate(date);
            if (!(oper_type != "Оплата" || oper_type != "Пополнение" || oper_type != "Снятие")) {
                cerr << "oper_result is incorrect\n<" << oper_type
                     << ">\nshould be \"Оплата\" or \"Пополнение\" or \"Снятие\"" << endl;
                throw std::runtime_error("");
            }
            if (!(oper_result != "Успешно" || oper_result != "Отказ")) {
                cerr << "oper_result is incorrect\n<" << oper_result << ">\nshould be \"Успешно\" or \"Отказ\"" << endl;
                throw std::runtime_error("");
            }
            if (amount < EPSILON) {
                cerr << "amount cannot be negative\n<" + to_string(amount) + ">" << endl;
                throw std::runtime_error("");
            }
            TestPassportDate(passport_valid_to);
            TestAccountDate(account_valid_to);
            TestClient(client);
        }
    } catch (...) {
        cout << "Given data is invalid, check it carefully!" << endl;
        return false;
    }
    cout << "Testing done, data is safe!" << endl;
    return true;
}

void Testing::TestClient(const string& client) {
    if (client.size() != 7) {
        cerr << "Client is incorrect\n<" << client << ">" << endl;
        throw std::runtime_error("");
    }

    int a, b;

    string a_, b_;
    a_ = client.substr(0, 1);
    b_ = client.substr(2, 5);
    for (char c: a_) {
        if (!std::isdigit(c)) {
            cerr << "Client is incorrect\n<" << client << ">" << endl;
            throw std::runtime_error("");
        }
    }
    for (char c: b_) {
        if (!std::isdigit(c)) {
            cerr << "Client is incorrect\n<" << client << ">" << endl;
            throw std::runtime_error("");
        }
    }

    try {
        a = stoi(client.substr(0, 1));
        b = stoi(client.substr(2, 5));
    } catch (...) {
        cerr << "Client is incorrect\n<" << client << ">" << endl;
        throw std::runtime_error("");
    }
    if (a + b > 23) {
        a = a + 2;
    }

    if (string(client.substr(1, 1)) != "-"s) {
        cerr << "Client is incorrect\n<" << client << ">" << endl;
        throw std::runtime_error("");
    }
}

void Testing::TestPassportDate(string passport_date) {
    if (passport_date.size() != 10) {
        if (passport_date.size() != 19) {
            cerr << "PassportDate is incorrect\n<" << passport_date << ">" << endl;
            throw std::runtime_error("");
        }
    }

    if (passport_date.size() == 19) {
        passport_date = passport_date.substr(0,10);
    }

    int year, month, day;

    string year_, month_, day_;
    year_ = passport_date.substr(0, 4);
    month_ = passport_date.substr(5, 2);
    day_ = passport_date.substr(8, 2);
    for (char c: year_) {
        if (!std::isdigit(c)) {
            cerr << "PassportDate is incorrect\n<" << passport_date << ">" << endl;
            throw std::runtime_error("");
        }
    }
    for (char c: month_) {
        if (!std::isdigit(c)) {
            cerr << "PassportDate is incorrect\n<" << passport_date << ">" << endl;
            throw std::runtime_error("");
        }
    }
    for (char c: day_) {
        if (!std::isdigit(c)) {
            cerr << "PassportDate is incorrect\n<" << passport_date << ">" << endl;
            throw std::runtime_error("");
        }
    }

    try {
        year = stoi(passport_date.substr(0, 4));
        month = stoi(passport_date.substr(5, 2));
        day = stoi(passport_date.substr(8, 2));
    }
    catch (exception& e) {
        cerr << "PassportDate is incorrect\n<" << passport_date << ">" << endl;
        throw std::runtime_error("");
    }

    if (string(passport_date.substr(4, 1)) != "-"s) {
        cerr << "PassportDate is incorrect\n<" << passport_date << ">" << endl;
        throw std::runtime_error("");
    }

    if (string(passport_date.substr(7, 1)) != "-"s) {
        cerr << "PassportDate is incorrect\n<" << passport_date << ">" << endl;
        throw std::runtime_error("");
    }

    if (CheckDate(day, month, year)) {
        return;
    }

    cerr << "PassportDate is incorrect\n<" << passport_date << ">" << endl;
    throw std::runtime_error("");
}

void Testing::TestAccountDate(string account_date) {
    if (account_date.size() != 10) {
        if (account_date.size() != 19) {
            cerr << "AccountDate is incorrect\n<" << account_date << ">" << endl;
            throw std::runtime_error("");
        }
    }

    if (account_date.size() == 19) {
        account_date = account_date.substr(0,10);
    }

    int year, month, day;

    string year_, month_, day_;
    year_ = account_date.substr(0, 4);
    month_ = account_date.substr(5, 2);
    day_ = account_date.substr(8, 2);
    for (char c: year_) {
        if (!std::isdigit(c)) {
            cerr << "AccountDate is incorrect\n<" << account_date << ">" << endl;
            throw std::runtime_error("");
        }
    }
    for (char c: month_) {
        if (!std::isdigit(c)) {
            cerr << "AccountDate is incorrect\n<" << account_date << ">" << endl;
            throw std::runtime_error("");
        }
    }
    for (char c: day_) {
        if (!std::isdigit(c)) {
            cerr << "AccountDate is incorrect\n<" << account_date << ">" << endl;
            throw std::runtime_error("");
        }
    }

    try {
        year = stoi(account_date.substr(0, 4));
        month = stoi(account_date.substr(5, 2));
        day = stoi(account_date.substr(8, 2));
    }
    catch (exception& e) {
        cerr << "AccountDate is incorrect\n<" << account_date << ">" << endl;
        throw std::runtime_error("");
    }

    if (string(account_date.substr(4, 1)) != "-"s) {
        cerr << "AccountDate is incorrect\n<" << account_date << ">" << endl;
        throw std::runtime_error("");
    }

    if (string(account_date.substr(7, 1)) != "-"s) {
        cerr << "AccountDate is incorrect\n<" << account_date << ">" << endl;
        throw std::runtime_error("");
    }

    if (CheckDate(day, month, year)) {
        return;
    }

    cerr << "AccountDate is incorrect\n<" << account_date << ">" << endl;
    throw std::runtime_error("");
}

void Testing::TestDate(const string& date) {
    if (date.size() != 19) {
        cerr << "Date is incorrect\n<" << date << ">" << endl;
        throw std::runtime_error("");
    }

    int year, month, day, hour, minute, sec;

    string year_, month_, day_, hour_, minute_, sec_;
    year_ = date.substr(0, 4);
    month_ = date.substr(5, 2);
    day_ = date.substr(8, 2);
    hour_ = date.substr(11, 2);
    minute_ = date.substr(14, 2);
    sec_ = date.substr(17, 2);
    for (char c: year_) {
        if (!std::isdigit(c)) {
            cerr << "Date is incorrect\n<" << date << ">" << endl;
            throw std::runtime_error("");
        }
    }
    for (char c: month_) {
        if (!std::isdigit(c)) {
            cerr << "Date is incorrect\n<" << date << ">" << endl;
            throw std::runtime_error("");
        }
    }
    for (char c: day_) {
        if (!std::isdigit(c)) {
            cerr << "Date is incorrect\n<" << date << ">" << endl;
            throw std::runtime_error("");
        }
    }
    for (char c: hour_) {
        if (!std::isdigit(c)) {
            cerr << "Date is incorrect\n<" << date << ">" << endl;
            throw std::runtime_error("");
        }
    }
    for (char c: minute_) {
        if (!std::isdigit(c)) {
            cerr << "Date is incorrect\n<" << date << ">" << endl;
            throw std::runtime_error("");
        }
    }
    for (char c: sec_) {
        if (!std::isdigit(c)) {
            cerr << "Date is incorrect\n<" << date << ">" << endl;
            throw std::runtime_error("");
        }
    }
    try {
        year = stoi(date.substr(0, 4));
        month = stoi(date.substr(5, 2));
        day = stoi(date.substr(8, 2));
        hour = stoi(date.substr(11, 2));
        minute = stoi(date.substr(14, 2));
        sec = stoi(date.substr(17, 2));

    }
    catch (exception& e) {
        cerr << "Date is incorrect\n<" << date << ">" << endl;
        throw std::runtime_error("");
    }

    if (string(date.substr(10, 1)) != "T"s) {
        cerr << "Date is incorrect\n<" << date << ">" << endl;
        throw std::runtime_error("");
    }

    if (string(date.substr(4, 1)) != "-"s) {
        cerr << "Date is incorrect\n<" << date << ">" << endl;
        throw std::runtime_error("");
    }

    if (string(date.substr(7, 1)) != "-"s) {
        cerr << "Date is incorrect\n<" << date << ">" << endl;
        throw std::runtime_error("");
    }

    if (string(date.substr(13, 1)) != ":"s) {
        cerr << "Date is incorrect\n<" << date << ">" << endl;
        throw std::runtime_error("");
    }

    if (string(date.substr(16, 1)) != ":"s) {
        cerr << "Date is incorrect\n<" << date << ">" << endl;
        throw std::runtime_error("");
    }

    if (CheckDate(day, month, year) && IsRange(hour, 0, 23) && IsRange(minute, 0, 59) && IsRange(sec, 0, 59)) {
        return;
    }

    cerr << "Date is incorrect\n<" << date << ">" << endl;
    throw std::runtime_error("");
}

bool Testing::IsRange(int value, int min, int max) {
    return value >= min && value <= max;
}

int Testing::isLeapYear(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 1 : 0;
}

bool Testing::CheckDate(int day, int month, int year) {
    const int months[] = {1, 3, 5, 7, 8, 10, 12, 4, 6, 9, 11};
    const int MONTH_WITH_31 = 7;

    if (year < 1)
        return false;
    if (month < 1 || month > 12)
        return false;
    if (month == 2)
        return IsRange(day, 1, 28 + isLeapYear(year));
    return IsRange(day, 1, 30 + (std::find(months, months + MONTH_WITH_31, month) != std::end(months)));
}