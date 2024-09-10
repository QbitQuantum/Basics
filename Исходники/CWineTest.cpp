/**
 * Runs a Wine test and captures the output
 *
 * @param TestInfo
 * Pointer to a CTestInfo object containing information about the test.
 * Will contain the test log afterwards if the user wants to submit data.
 */
void
CWineTest::RunTest(CTestInfo* TestInfo)
{
    bool BreakLoop = false;
    DWORD BytesAvailable;
    DWORD Temp;
    stringstream ss, ssFinish;
    DWORD StartTime = GetTickCount();
    float TotalTime;
    string tailString;

    ss << "Running Wine Test, Module: " << TestInfo->Module << ", Test: " << TestInfo->Test << endl;
    StringOut(ss.str());

    StartTime = GetTickCount();

    {
        /* Execute the test */
        CProcess Process(TestInfo->CommandLine, &m_StartupInfo);

        /* Receive all the data from the pipe */
        do
        {
            /* When the application finished, make sure that we peek the pipe one more time, so that we get all data.
               If the following condition would be the while() condition, we might hit a race condition:
                  - We check for data with PeekNamedPipe -> no data available
                  - The application outputs its data and finishes
                  - WaitForSingleObject reports that the application has finished and we break the loop without receiving any data
            */
            if(WaitForSingleObject(Process.GetProcessHandle(), 0) != WAIT_TIMEOUT)
                BreakLoop = true;

            if(!PeekNamedPipe(m_hReadPipe, NULL, 0, NULL, &BytesAvailable, NULL))
                FATAL("PeekNamedPipe failed for the test run\n");

            if(BytesAvailable)
            {
                /* There is data, so get it and output it */
                auto_array_ptr<char> Buffer(new char[BytesAvailable + 1]);

                if(!ReadFile(m_hReadPipe, Buffer, BytesAvailable, &Temp, NULL))
                    FATAL("ReadFile failed for the test run\n");

                /* Output text through StringOut, even while the test is still running */
                Buffer[BytesAvailable] = 0;
                tailString = StringOut(tailString.append(string(Buffer)), false);

                if(Configuration.DoSubmit())
                    TestInfo->Log += Buffer;
            }
        }
        while(!BreakLoop);
    }

    /* Print what's left */
    if(!tailString.empty())
        StringOut(tailString);

    TotalTime = ((float)GetTickCount() - StartTime)/1000;
    ssFinish << "Test " << TestInfo->Test << " completed in ";
    ssFinish << setprecision(2) << fixed << TotalTime << " seconds." << endl;
    StringOut(ssFinish.str());
}