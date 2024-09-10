void CWE511_Logic_Time_Bomb__time_12_bad()
{
    if(globalReturnsTrueOrFalse())
    {
        {
            time_t currentTime;
            /* FLAW: After a certain date, delete a file */
            time(&currentTime);
            if (currentTime > TIME_CHECK)
            {
                UNLINK("important_file.txt");
            }
        }
    }
    else
    {
        {
            time_t currentTime;
            /* FIX: After a certain date, print to the console */
            time(&currentTime);
            if (currentTime > TIME_CHECK)
            {
                printLine("Happy New Year!");
            }
        }
    }
}