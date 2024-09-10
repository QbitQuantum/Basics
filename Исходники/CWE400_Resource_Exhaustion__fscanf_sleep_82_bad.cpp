void CWE400_Resource_Exhaustion__fscanf_sleep_82_bad::action(int count)
{
    /* POTENTIAL FLAW: Sleep function using count as the parameter with no validation */
    SLEEP(count);
    printLine("Sleep time possibly too long");
}