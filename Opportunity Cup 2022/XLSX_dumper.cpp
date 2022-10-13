#include "XLSX_dumper.h"

using namespace std;

void XLSX_dumper::DumpAllToXlsx(std::vector<std::string>& res_filenames, const input_data& id) {
    string xlsx_filename = "Otchet.xlsx";
    if (filesystem::exists(xlsx_filename)) {
        filesystem::remove(xlsx_filename);
    }
    XLDocument doc;
    doc.create(xlsx_filename);

    int value_for_1_pattern = id.value_for_1_pattern;
    int value_for_4_pattern_1 = id.value_for_4_pattern_1, value_for_4_pattern_2 = id.value_for_4_pattern_2;
    int value_for_5_pattern = id.value_for_5_pattern;
    int value_for_6_pattern = id.value_for_6_pattern;
    int value_for_7_pattern_1 = id.value_for_7_pattern_1, value_for_7_pattern_2 = id.value_for_7_pattern_2, value_for_7_pattern_3 = id.value_for_7_pattern_3;

    auto work_book = doc.workbook();
    work_book.addWorksheet("Фрауд паттерны");
    work_book.addWorksheet("Транзакции");
    work_book.deleteSheet("Sheet1");
    auto wks_1 = work_book.worksheet("Фрауд паттерны");
    wks_1.cell("B1").value() = "Выявленные фрод паттерны";
    wks_1.cell("B2").value() = "Описание";
    wks_1.cell("B3").value() = "\"Подозрительная активность, похожая на фишинговую\" - \n"
                               "мы отследили людей с большим количеством транзакций и \n"
                               "посмотрели на количество уникальных карт с которых эти транзакции совершались. \n"
                               "Если число уникальных карт пользователя превысило " + to_string(value_for_1_pattern) +
                               ", то все транзакции данного пользователя мы считаем подозрительными.";
    wks_1.cell("B4").value() = "\"Успешные транзакции с просроченных карт\" - мы проанализировали все транзакции, \n"
                               "и среди них отобрали те, статус которых «успешно», но при этом карта уже не валидна.";
    wks_1.cell(
            "B5").value() = "\"Успешные операции клиентов с просроченными паспортами\" - мы проанализировали все транзакции,\n"
                            " и среди них отобрали те, статус которых «успешно», но при этом паспорт просрочен.";
    wks_1.cell("B6").value() = "\"Шаблонное поведение\" - мы отследили подряд идущие транзакции пользователей, \n"
                               "и если временной промежуток между ними был менее " +
                               to_string((value_for_4_pattern_1 / 60)) + " минут, и таких транзакций было более " +
                               to_string(value_for_4_pattern_2) + "\n"
                                                                  "то всю эту череду транзакций мы относили к подозрительным.";
    wks_1.cell("B7").value() =
            "\"Физически невозможные перемещения между городами\" - мы проанализировали все транзакции каждого отдельно взятого человека\n"
            " и нашли среди этих транзакций такие, что время между их совершением менее " +
            to_string((value_for_5_pattern / 60)) + " минут, \n"
                                                     "при этом они совершены из разных городов, обе транзакции считались подозрительными.";
    wks_1.cell("B8").value() =
            "\"Подозрительная активность в ночное время\" - мы проанализировали все транзакции каждого отдельно взятого человека \n"
            "и нашли среди клиентов таких, что все их транзакции совершены ночью, и общее количество транзакций пользователя более " +
            to_string((value_for_6_pattern));
    wks_1.cell("B9").value() =
            "\"Большие убытки после череды транзакций\" - мы отследили подряд идущие транзакции пользователей, \n"
            "и если временной промежуток между ними был менее " + to_string((value_for_7_pattern_1 / 60)) +
            " минут, и таких транзакций было более " + to_string((value_for_7_pattern_3)) + "\n"
                                                                                      "то если убыток составил более " +
            to_string((value_for_7_pattern_2)) + " рублей, вся череда считалась подозрительной";
    wks_1.cell("A2").value() = "№ паттерна";

    auto wks_2 = work_book.worksheet("Транзакции");
    wks_2.cell("B1").value() = "Транзакции";
    wks_2.cell("B2").value() = "Номера транзакций, попадающих под паттерн";
    wks_2.cell("A2").value() = "№ паттерна";
    int i = 3;
    for (const string& filename: res_filenames) {
        ifstream ifs(filename);
        string result = "[";
        string line;
        while (getline(ifs, line)) {
            result += line;
        }
        result += "]";
        wks_1.cell("A" + to_string(i)).value() = i - 2;
        wks_2.cell("A" + to_string(i)).value() = i - 2;
        wks_2.cell("B" + to_string(i++)).value().set(result);

        ifs.close();
    }

    doc.save();
    doc.close();
    filesystem::create_directory("result/");
    if (filesystem::exists("result/" + xlsx_filename)) {
        filesystem::remove("result/" + xlsx_filename);
    }
    filesystem::rename(xlsx_filename, "result/" + xlsx_filename);
}