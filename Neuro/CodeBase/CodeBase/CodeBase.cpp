// 1. __adding.Value[_field("num")] = BilixFlights->EnumerateActHeadNumber(YearOf(__adding.Element[_field("date.begin")]->DateTime));

/*
#include <iostream>
#include <map>
#include <string>
#include <ctime>
#include <vector>
typedef int TDateTime;
const TDateTime EMPTY_DATE = 0;
struct BaseDataElement {
    std::string Generic;
    TDateTime DateTime = EMPTY_DATE;
    std::vector<std::string> Array;
    void Clear() {
        Generic.clear();
        DateTime = EMPTY_DATE;
        Array.clear();
    }
};
class OctetBilixFlights {
public:
    int EnumerateActHeadNumber(int year) {
        return year;    
    }
};
struct __adding {
    std::map<std::string, int> Value;
    std::map<std::string, BaseDataElement*> Element;
};
std::string _field(const std::string& key) {
    return key;
}
int YearOf(TDateTime dateTime) {
    return dateTime;
}
void InitializeElementAndSetDate(__adding& adding, const std::string& key, TDateTime dateTime) {
    adding.Element[_field(key)] = new BaseDataElement();
    adding.Element[_field(key)]->DateTime = dateTime;
}
void DeleteElement(__adding& adding, const std::string& key) {
    delete adding.Element[_field(key)];
    adding.Element.erase(_field(key));
}
int main() {
    __adding __adding;
    OctetBilixFlights* BilixFlights = new OctetBilixFlights();
    std::time_t now = std::time(nullptr);
    std::tm now_tm;
    localtime_s(&now_tm, &now);
    InitializeElementAndSetDate(__adding, "date.begin", now_tm.tm_year + 1900);
    __adding.Value[_field("num")] = BilixFlights->EnumerateActHeadNumber(YearOf(__adding.Element[_field("date.begin")]->DateTime));
    DeleteElement(__adding, "date.begin");
    delete BilixFlights;
    return 0;
}

*/

// 2.