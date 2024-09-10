void ProcessChildStdOut(const CommandLine::Options& o,
                        char*                       stdoutFilename,
                        int*                        loaded,
                        int*                        jitted,
                        int*                        failed,
                        int*                        diffs,
                        bool*                       usageError)
{
    char buff[MAX_LOG_LINE_SIZE];

    FILE* fp = fopen(stdoutFilename, "r");

    if (fp == NULL)
    {
        LogError("Unable to open '%s'.", stdoutFilename);
        goto Cleanup;
    }

    while (fgets(buff, MAX_LOG_LINE_SIZE, fp) != NULL)
    {
        // get rid of the '\n' at the end of line
        size_t buffLen = strlen(buff);
        if (buff[buffLen - 1] == '\n')
            buff[buffLen - 1] = 0;

        if (strncmp(buff, "MISSING: ", 9) == 0)
            LogMissing("%s", &buff[9]); // log as Missing and remove the "MISSING: " in front
        else if (strncmp(buff, "ISSUE: ", 7) == 0)
        {
            if (strncmp(&buff[7], "<ASM_DIFF> ", 11) == 0)
                LogIssue(ISSUE_ASM_DIFF, "%s", &buff[18]); // log as Issue and remove the "ISSUE: <ASM_DIFF>" in front
            else if (strncmp(&buff[7], "<ASSERT> ", 9) == 0)
                LogIssue(ISSUE_ASSERT, "%s", &buff[16]); // log as Issue and remove the "ISSUE: <ASSERT>" in front
        }
        else if (strncmp(buff, g_SuperPMIUsageFirstLine, strlen(g_SuperPMIUsageFirstLine)) == 0)
        {
            *usageError = true; // Signals that we had a SuperPMI command line usage error

            // Read the entire stdout file and printf it
            printf("%s", buff);
            while (fgets(buff, MAX_LOG_LINE_SIZE, fp) != NULL)
            {
                printf("%s", buff);
            }
            break;
        }
        else if (strncmp(buff, g_AllFormatStringFixedPrefix, strlen(g_AllFormatStringFixedPrefix)) == 0)
        {
            if (o.applyDiff)
            {
                int temp1 = 0, temp2 = 0, temp3 = 0, temp4 = 0;
                int converted = sscanf_s(buff, g_AsmDiffsSummaryFormatString, &temp1, &temp2, &temp3, &temp4);
                if (converted != 4)
                {
                    LogError("Couldn't parse status message: \"%s\"", buff);
                }
                else
                {
                    *loaded += temp1;
                    *jitted += temp2;
                    *failed += temp3;
                    *diffs += temp4;
                }
            }
            else
            {
                int temp1 = 0, temp2 = 0, temp3 = 0;
                int converted = sscanf_s(buff, g_SummaryFormatString, &temp1, &temp2, &temp3);
                if (converted != 3)
                {
                    LogError("Couldn't parse status message: \"%s\"", buff);
                }
                else
                {
                    *loaded += temp1;
                    *jitted += temp2;
                    *failed += temp3;
                    *diffs = -1;
                }
            }
        }
    }

Cleanup:
    if (fp != NULL)
        fclose(fp);
}