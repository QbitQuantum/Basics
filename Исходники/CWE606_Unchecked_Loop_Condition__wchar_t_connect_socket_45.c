/* goodB2G() uses the BadSource with the GoodSink */
static void goodB2GSink()
{
    wchar_t * data = CWE606_Unchecked_Loop_Condition__wchar_t_connect_socket_45_goodB2GData;
    {
        int i, n, intVariable;
        if (swscanf(data, L"%d", &n) == 1)
        {
            /* FIX: limit loop iteration counts */
            if (n < MAX_LOOP)
            {
                intVariable = 0;
                for (i = 0; i < n; i++)
                {
                    /* INCIDENTAL: CWE 561: Dead Code - non-avoidable if n <= 0 */
                    intVariable++; /* avoid a dead/empty code block issue */
                }
                printIntLine(intVariable);
            }
        }
    }
}