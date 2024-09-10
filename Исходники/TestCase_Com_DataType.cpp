void TestCase_Com_DataType::StringBaseTest()
{
    LLBC_PrintLine("String base functions test:");

    LLBC_String testStr;
    testStr.format("%s", "hello world!");
    testStr.append_format("%s", "hello world!");
    LLBC_PrintLine("LLBC_String::format/append_format test: %s", testStr.c_str());

    LLBC_String testStr2;
    for(int i = 0; i < 1000; i++)
    {
        testStr.append("hello world!");
    }

    testStr2.append_format("%s", testStr.c_str());
    LLBC_PrintLine("LLBC_String:format large string test: %s", testStr2.c_str());

    // tolower/toupper test.
    testStr = "Hello WoRlD!";
    LLBC_PrintLine("'%s' to lower: '%s'", testStr.c_str(), testStr.tolower().c_str());
    LLBC_PrintLine("'%s' to upper: '%s'", testStr.c_str(), testStr.toupper().c_str());

    // isalpha/isupper/islower.
    LLBC_String str("HELLO");
    LLBC_PrintLine("%s islower?%d, isupper?%d, isalpha?%d", 
        str.c_str(), str.islower(), str.isupper(), str.isalpha());
    str = "hello";
    LLBC_PrintLine("%s islower?%d, isupper?%d, isalpha?%d", 
        str.c_str(), str.islower(), str.isupper(), str.isalpha());
    str = "HeLlO";
    LLBC_PrintLine("%s islower?%d, isupper?%d, isalpha?%d", 
        str.c_str(), str.islower(), str.isupper(), str.isalpha());
    str = "hello123";
    LLBC_PrintLine("%s islower?%d, isupper?%d, isalpha?%d", 
        str.c_str(), str.islower(), str.isupper(), str.isalpha());
    str = "HELLO123";
    LLBC_PrintLine("%s islower?%d, isupper?%d, isalpha?%d", 
        str.c_str(), str.islower(), str.isupper(), str.isalpha());
    str = "Hello123";
    LLBC_PrintLine("%s islower?%d, isupper?%d, isalpha?%d", 
        str.c_str(), str.islower(), str.isupper(), str.isalpha());
    str = "H";
    LLBC_PrintLine("%s islower?%d, isupper?%d, isalpha?%d", 
        str.c_str(), str.islower(), str.isupper(), str.isalpha());
    str = "h";
    LLBC_PrintLine("%s islower?%d, isupper?%d, isalpha?%d", 
        str.c_str(), str.islower(), str.isupper(), str.isalpha());
    str = "3";
    LLBC_PrintLine("%s islower?%d, isupper?%d, isalpha?%d", 
        str.c_str(), str.islower(), str.isupper(), str.isalpha());

    LLBC_PrintLine("\n");
}