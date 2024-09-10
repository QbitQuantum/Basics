JobObject::JobObject(void)
:
	m_hJobObject(NULL)
{
	HANDLE jobObject = CreateJobObject(NULL, NULL);
	if((jobObject != NULL) && (jobObject != INVALID_HANDLE_VALUE))
	{
		JOBOBJECT_EXTENDED_LIMIT_INFORMATION jobExtendedLimitInfo;
		memset(&jobExtendedLimitInfo, 0, sizeof(JOBOBJECT_EXTENDED_LIMIT_INFORMATION));
		memset(&jobExtendedLimitInfo.BasicLimitInformation, 0, sizeof(JOBOBJECT_BASIC_LIMIT_INFORMATION));
		jobExtendedLimitInfo.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE | JOB_OBJECT_LIMIT_DIE_ON_UNHANDLED_EXCEPTION;
		if(SetInformationJobObject(jobObject, JobObjectExtendedLimitInformation, &jobExtendedLimitInfo, sizeof(JOBOBJECT_EXTENDED_LIMIT_INFORMATION)))
		{
			m_hJobObject = jobObject;
		}
		else
		{
			qWarning("Failed to set job object information!");
			CloseHandle(jobObject);
		}
	}
	else
	{
		qWarning("Failed to create the job object!");
	}
}