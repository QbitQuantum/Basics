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



/*
//  2.
    __classes.Parent = _ctrl_createchildparent(__SCALE(GlobalData->GetInt("service_classes", "visual.width", 860)));
    __classes.Tab = new OctetBilixServiceClasses(*__classes.Parent, this);
    __classes.Tab->Width = __SCALE(GlobalData->GetInt("service_classes", "visual.width", 860));
    __childs.push_back(__classes.Tab);
*/
/*
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
*/



