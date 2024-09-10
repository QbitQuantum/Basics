void CSummInfo::StartEditTimeCount()
{
	FILETIME now;
	CoFileTimeNow(&now);
	startEdit = *(__int64*)&now;
}