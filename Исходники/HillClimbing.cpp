    /// <summary>
    ///     Logs the hill climbing decision.
    /// </summary>
    /// <param name="recommendedSetting">
    ///     The control setting to be established.
    /// </param>
    /// <param name="transition">
    ///     The transition that is recommended by hill climbing.
    /// </param>
    /// <param name="numberOfSamples">
    ///     The number of sample points in this measurement, including invalid ones.
    /// </param>
    /// <param name="completionRate">
    ///     The number of completed units or work in that period of time.
    /// </param>
    /// <param name="arrivalRate">
    ///     The number of incoming units or work in that period of time.
    /// </param>
    /// <param name="queueLength">
    ///     The total length of the work queue.
    /// </param>
    /// <param name="throughput">
    ///     The throughput of the given instance.
    /// </param>
    void HillClimbing::LogData(unsigned int recommendedSetting, HillClimbingStateTransition transition, unsigned int numberOfSamples,
        unsigned int completionRate, unsigned int arrivalRate, unsigned int queueLength, double throughput)
    {
        //
        // First, log to memory so we can see it in the debugger
        //
        int index = (HillClimbingLogFirstIndex + HillClimbingLogSize) % HillClimbingLogCapacity;
        if (HillClimbingLogSize == HillClimbingLogCapacity)
        {
            HillClimbingLogFirstIndex = (HillClimbingLogFirstIndex + 1) % HillClimbingLogCapacity;
            HillClimbingLogSize--; //hide this slot while we update it
        }

        HillClimbingLogEntry * entry = &HillClimbingLog[index];
        unsigned int minimumSetting = m_pSchedulerProxy->MinHWThreads();
        unsigned int maximumSetting = m_pSchedulerProxy->DesiredHWThreads();

        entry->sampleCount = m_sampleCount;
        entry->currentTotalSampleCount = numberOfSamples;
        entry->throughput = throughput;
        entry->transition = transition;
        entry->currentControlSetting = m_currentControlSetting;
        entry->lastControlSetting = m_lastControlSetting;

        MeasuredHistory * currentHistory = GetHistory(m_currentControlSetting);
        entry->currentHistoryCount = currentHistory->Count();
        entry->currentHistoryMean = currentHistory->Mean();
        entry->currentHistoryStd = currentHistory->StandardDeviation();

        MeasuredHistory * lastHistory = GetHistory(m_lastControlSetting);
        entry->lastHistoryCount = lastHistory->Count();
        entry->lastHistoryMean = lastHistory->Mean();
        entry->lastHistoryStd = lastHistory->StandardDeviation();

        HillClimbingLogSize++;

        const int bufferSize = 180;
        const wchar_t * delim = L"*******************************************************";

        wchar_t dateBuffer[bufferSize];
        SYSTEMTIME time;
        GetLocalTime(&time);
        int dateLen = GetDateFormatEx(LOCALE_NAME_USER_DEFAULT, DATE_SHORTDATE, &time, NULL, dateBuffer, bufferSize);
        dateBuffer[dateLen-1] = L' ';
        GetTimeFormatEx(LOCALE_NAME_USER_DEFAULT, TIME_FORCE24HOURFORMAT | TIME_NOTIMEMARKER, &time, NULL, dateBuffer + dateLen, bufferSize - dateLen);

        TRACE(CONCRT_TRACE_HILLCLIMBING, L"%ls\n Process: %u\n Scheduler: %d\n Date: %ls\n Number of samples: %d\n Number of samples in this measurement (including invalid): %d\n Completions: %d\n Arrivals: %d\n Queue length: %d\n Throughput: %.4f\n Transition: %ls\n Next random move: %ls\n Minimum: %d\n Maximum: %d\n Current setting: %d\n  * count: %d mean: %g dev: %g varm: %g\n Last setting: %d\n  * count: %d mean: %g dev: %g varm: %g\n -----\n Recommended setting: %d\n%ls\n",
            delim,
            GetCurrentProcessId(),
            m_id,
            dateBuffer,
            m_sampleCount,
            numberOfSamples,
            completionRate,
            arrivalRate,
            queueLength,
            throughput,
            HillClimbingTransitionNames[transition],
            m_nextRandomMoveIsUp ? L"Up" : L"Down",
            minimumSetting,
            maximumSetting,
            m_currentControlSetting,
            currentHistory->Count(),
            currentHistory->Mean(),
            currentHistory->StandardDeviation(),
            currentHistory->CoefficientOfVariationMean(),
            m_lastControlSetting,
            lastHistory->Count(),
            lastHistory->Mean(),
            lastHistory->StandardDeviation(),
            lastHistory->CoefficientOfVariationMean(),
            recommendedSetting,
            delim);
    }