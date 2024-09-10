void CWE606_Unchecked_Loop_Condition__wchar_t_listen_socket_22_badSink(wchar_t * data)
{
    if(CWE606_Unchecked_Loop_Condition__wchar_t_listen_socket_22_badGlobal)
    {
        {
            int i, n, intVariable;
            if (swscanf(data, L"%d", &n) == 1)
            {
                /* POTENTIAL FLAW: user-supplied value 'n' could lead to very large loop iteration */
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