void limitMem( size_t limit )
{
    static HANDLE hJob = NULL;
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION jobInfo;

    jobInfo.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_PROCESS_MEMORY;
    jobInfo.ProcessMemoryLimit = limit? limit*MByte : 2*MByte*1024;
    if (NULL == hJob) {
        if (NULL == (hJob = CreateJobObject(NULL, NULL))) {
            REPORT("Can't assign create job object: %ld\n", GetLastError());
            exit(1);
        }
        if (0 == AssignProcessToJobObject(hJob, GetCurrentProcess())) {
            REPORT("Can't assign process to job object: %ld\n", GetLastError());
            exit(1);
        }
    }
    if (0 == SetInformationJobObject(hJob, JobObjectExtendedLimitInformation,
                                     &jobInfo, sizeof(jobInfo))) {
        REPORT("Can't set limits: %ld\n", GetLastError());
        exit(1);
    }
}