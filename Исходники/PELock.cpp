BOOL CPELock::IsPELockPresent2()
{
	return ( LockFile(NULL, 128, 0, 512, 0) == 1 ? TRUE : FALSE );
}