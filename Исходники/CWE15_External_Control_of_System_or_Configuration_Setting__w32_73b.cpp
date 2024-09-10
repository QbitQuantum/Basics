/* goodG2B uses the GoodSource with the BadSink */
void goodG2BSink(list<char *> dataList)
{
    char * data = dataList.back();
    /* POTENTIAL FLAW: set the hostname to data obtained from a potentially external source */
    if (!SetComputerNameA(data))
    {
        printLine("Failure setting computer name");
        exit(1);
    }
}