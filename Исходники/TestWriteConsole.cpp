void TestWriteConsole::test1()
{
    //㘵
    HANDLE std_output = GetStdHandle( STD_OUTPUT_HANDLE );
    std::wstring ws = L"㘵中华人民共和国abc\n";
    WriteConsoleW( std_output, ws.c_str(), ws.size(), NULL, NULL );
}