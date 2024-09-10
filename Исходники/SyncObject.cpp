PLuint SyncObject::SetSpinCount(PLuint spin_count)
{
	return SetCriticalSectionSpinCount(&csCriticalSection, spin_count);
}