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

    std::string codeOne = R"(
    __classes.Parent = _ctrl_createchildparent(__SCALE(GlobalData->GetInt("service_classes", "visual.width", 860)));
    __classes.Tab = new OctetBilixServiceClasses(*__classes.Parent, this);
    __classes.Tab->Width = __SCALE(GlobalData->GetInt("service_classes", "visual.width", 860));
    __childs.push_back(__classes.Tab);
)";
 
    std::string codeTwo = R"(
#include <vector>
#include <string>
class ParentClass {
public:
    ParentClass(int width) : width(width) {}
    int width;
};
class OctetBilixServiceClasses {
public:
    OctetBilixServiceClasses(ParentClass& parent, void* context) : parent(parent), context(context) {}
    int Width;
private:
    ParentClass& parent;
    void* context;
};
class GlobalDataClass {
public:
    int GetInt(const std::string& section, const std::string& key, int defaultValue) {
        return defaultValue;
    }
};
GlobalDataClass* GlobalData;
ParentClass* _ctrl_createchildparent(int width) {
    return new ParentClass(width);
}
int __SCALE(int value) {
    return value;
}
struct ClassesContainer {
    ParentClass* Parent;
    OctetBilixServiceClasses* Tab;
};
class OctetBaseClases
{
public:
    void OctetClases();
};
void OctetBaseClases::OctetClases()
{
    ClassesContainer __classes;
    std::vector<OctetBilixServiceClasses*> __childs;

    __classes.Parent = _ctrl_createchildparent(__SCALE(GlobalData->GetInt("service_classes", "visual.width", 860)));
    __classes.Tab = new OctetBilixServiceClasses(*__classes.Parent, this);
    __classes.Tab->Width = __SCALE(GlobalData->GetInt("service_classes", "visual.width", 860));
    __childs.push_back(__classes.Tab);

    delete __classes.Tab;
    delete __classes.Parent;
}
int main() {
    OctetBaseClases* __Octet = new OctetBaseClases();
    __Octet->OctetClases();
    delete __Octet;
    return 0;
}
)";

    std::string escapedCode = escapeJson(codeOne);
    std::cout << escapedCode << std::endl;
    escapedCode = escapeJson(codeTwo);
    std::cout << escapedCode << std::endl;


    //std::string code1 = unescapeJson(escapedCode);
    //std::cout << code1 << std::endl;


    return 0;
}