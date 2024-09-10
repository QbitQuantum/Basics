void asCLockableSharedBool::Unlock() const
{
	LEAVECRITICALSECTION(lock);
}