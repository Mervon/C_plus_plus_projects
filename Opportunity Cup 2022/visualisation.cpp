#include "visualisation.h"

using namespace std;

void Visualisation::MakeDataForPython(const json& data) {
    map<int, int> result;

    for (auto& item_1 : data["transactions"].items()) {
        string date;

        for (auto& item_2 : item_1.value().items()) {
            if (item_2.key() == "date") {
                date = item_2.value();
            }
        }

        result[GetHoursFromDate(date)]++;
    }

    ofstream ofs("DateVis.txt");

    for (auto& item: result) {
        ofs << item.first << ":" << item.second << endl;
    }
}

void Visualisation::MakeDataForPython_2(const json& data) {
    set<string> all_bad_transaction = GetAllBadTransactions();

    map<int, int> res;

    for (auto& item : all_bad_transaction) {
        for (auto& item_2 : data["transactions"][item].items()) {
            if (item_2.key() == "date") {
                res[GetHoursFromDate(item_2.value())]++;
            }
        }
    }

    ofstream ofs("DateVis_2.txt");

    for (auto& item : res) {
        ofs << item.first << ":" << item.second << endl;
    }

}