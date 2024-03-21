
#include <iostream>
#include <string>

void  CodeWriterCppFile(std::string format) {
    //Какой-то код
}


std::string CodeWriterCppFile(std::string format, bool ints = false) {
    if (ints) {
        //Какой-то код
    }
    return "stroka";
}

typedef std::string(*CodeWriterCppFilePtr)(std::string, bool);
std::string CodeWriterCppFile(CodeWriterCppFilePtr func, std::string format, bool ints = false) {
    std::string result = func(format, ints);
    return result;
}



int main()
{
    std::string text = "";
    std::string result1 = CodeWriterCppFile(CodeWriterCppFile, text); // stroka
    std::string result2 = CodeWriterCppFile(CodeWriterCppFile, text, true); // stroka
    std::string result3 = CodeWriterCppFile(CodeWriterCppFile, text, false); // stroka

    return 0;
}