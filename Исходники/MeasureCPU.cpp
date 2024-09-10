/*
** Updates the current CPU utilization value.
**
*/
bool CMeasureCPU::Update()
{
    if (!CMeasure::PreUpdate()) return false;

    if (m_Processor == 0)
    {
        BOOL status;
        FILETIME ftIdleTime, ftKernelTime, ftUserTime;

        // get new CPU's idle/kernel/user time
        status = GetSystemTimes(&ftIdleTime, &ftKernelTime, &ftUserTime);
        if (status == 0) return false;

        CalcUsage(Ft2Double(ftIdleTime),
                  Ft2Double(ftKernelTime) + Ft2Double(ftUserTime));
    }
    else if (c_NtQuerySystemInformation)
    {
        LONG status;
        ULONG bufSize = c_BufferSize;
        BYTE* buf = (bufSize > 0) ? new BYTE[bufSize] : NULL;

        int loop = 0;

        do
        {
            ULONG size = 0;

            status = c_NtQuerySystemInformation(SystemProcessorPerformanceInformation, buf, bufSize, &size);
            if (status == STATUS_SUCCESS || status != STATUS_INFO_LENGTH_MISMATCH) break;

            else  // status == STATUS_INFO_LENGTH_MISMATCH
            {
                if (size == 0)  // Returned required buffer size is always 0 on Windows 2000/XP.
                {
                    if (bufSize == 0)
                    {
                        bufSize = sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION) * c_NumOfProcessors;
                    }
                    else
                    {
                        bufSize += sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION);
                    }
                }
                else
                {
                    if (size != bufSize)
                    {
                        bufSize = size;
                    }
                    else  // ??
                    {
                        bufSize += sizeof(SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION);
                    }
                }

                delete [] buf;
                buf = new BYTE[bufSize];
            }
            ++loop;
        }
        while (loop < 5);

        if (status != STATUS_SUCCESS)  // failed
        {
            delete [] buf;
            return false;
        }

        if (bufSize != c_BufferSize)
        {
            // Store the new buffer size
            c_BufferSize = bufSize;
        }

        SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION* systemPerfInfo = (SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION*)buf;

        int processor = m_Processor - 1;

        CalcUsage(Li2Double(systemPerfInfo[processor].IdleTime),
                  Li2Double(systemPerfInfo[processor].KernelTime) + Li2Double(systemPerfInfo[processor].UserTime));

        delete [] buf;
    }
    else
    {
        return false;
    }

    return PostUpdate();
}