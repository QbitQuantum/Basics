#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#include <iostream>
#include <string>

std::string unescapeJson(const std::string& input) {
    std::string output;
    for (size_t i = 0; i < input.size(); ++i) {
        if (input[i] == '\\') {
            if (i + 1 < input.size()) {
                switch (input[i + 1]) {
                case '\\': output += '\\'; break;
                case '"': output += '"'; break;
                case 'n': output += '\n'; break;
                case 'r': output += '\r'; break;
                case 't': output += '\t'; break;
                default: output += input[i + 1]; break;
                }
                ++i; // Skip the escaped character
            }
        }
        else {
            output += input[i];
        }
    }
    return output;
}


std::string escapeJson(const std::string& input) {
    std::ostringstream oss;
    for (char ch : input) {
        switch (ch) {
        case '\\': oss << "\\\\"; break;
        case '"': oss << "\\\""; break;
        case '\b': oss << "\\b"; break;
        case '\f': oss << "\\f"; break;
        case '\n': oss << "\\n"; break;
        case '\r': oss << "\\r"; break;
        case '\t': oss << "\\t"; break;
        default:
            if ('\x00' <= ch && ch <= '\x1f') {
                oss << "\\u" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(ch);
            }
            else {
                oss << ch;
            }
        }
    }
    return oss.str();
}



int main() {
    /*
    std::string code = R"(
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
)";
    */
    std::string code = R"(
__adding.Value[_field("num")] = BilixFlights->EnumerateActHeadNumber(YearOf(__adding.Element[_field("date.begin")]->DateTime));
)";

    std::string escapedCode = escapeJson(code);
    std::cout << escapedCode << std::endl;

    //std::string code1 = unescapeJson(escapedCode);
    //std::cout << code1 << std::endl;


    return 0;
}