HANDLE EngineProcess::mainJob()
{
	QMutexLocker locker(&s_mutex);
	if (s_job)
		return s_job;

	s_job = CreateJobObject(NULL, NULL);
	JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli;

	memset(&jeli, 0, sizeof(JOBOBJECT_EXTENDED_LIMIT_INFORMATION));

	jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
	SetInformationJobObject(s_job, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli));

	return s_job;
}