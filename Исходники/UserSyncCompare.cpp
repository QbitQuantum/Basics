void WINAPI SRWLockReadCallback() {
	AcquireSRWLockShared(&g_srwLock);
	gv_value = 0;
	ReleaseSRWLockShared(&g_srwLock);
}