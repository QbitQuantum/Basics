bool CSpinLock::try_lock()
{
#pragma warning(suppress:4800)
	return !(bool)_InterlockedExchange8(reinterpret_cast<char volatile *>(&spin_), (char)true);
}