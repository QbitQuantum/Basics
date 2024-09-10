void badSink(list<wchar_t *> dataList)
{
    /* copy data out of dataList */
    wchar_t * data = dataList.back();
    /* POTENTIAL FLAW: Set a new environment variable with a path that is possibly insecure */
    PUTENV(data);
}