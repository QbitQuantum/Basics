/* goodG2B uses the GoodSource with the BadSink */
static void goodG2BSink(int count)
{
    /* POTENTIAL FLAW: Sleep function using count as the parameter with no validation */
    SLEEP(count);
    printLine("Sleep time possibly too long");
}