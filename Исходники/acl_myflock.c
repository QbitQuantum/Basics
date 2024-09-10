/* use LockFileEx/UnlockFileEx */
int acl_myflock(ACL_FILE_HANDLE fd, int lock_style acl_unused, int operation)
{
	const char *myname = "acl_myflock";
	DWORD size = 0xFFFFFFFF;
	char  ebuf[256];
	unsigned char lock_op;
	OVERLAPPED ovlp;
	DWORD flags;

	if ((operation & (ACL_FLOCK_OP_BITS)) != operation)
		acl_msg_panic("myflock: improper operation type: 0x%x", operation);

	memset(&ovlp, 0, sizeof(ovlp));

	ovlp.Offset = 0;
	lock_op = operation & ~ACL_FLOCK_OP_NOWAIT;
	if (lock_op == ACL_FLOCK_OP_NONE) {
		if(UnlockFileEx(fd, 0, 1, 0, &ovlp))
			return (0);
		acl_msg_error("%s(%d): unlock error(%s)",
			myname, __LINE__, acl_last_strerror(ebuf,sizeof(ebuf)));
		return (-1);
	} else if (lock_op == ACL_FLOCK_OP_SHARED) {
		while (1) {
			flags = 0;
			if ((operation & ACL_FLOCK_OP_NOWAIT))
				flags |= LOCKFILE_FAIL_IMMEDIATELY;

			if(LockFileEx(fd, flags, 0, 1, 0, &ovlp))
				return (0);
			if ((operation & ACL_FLOCK_OP_NOWAIT)) {
				acl_msg_error("%s(%d): lock error(%s)", myname, __LINE__,
					acl_last_strerror(ebuf,sizeof(ebuf)));
				return (-1);
			}
			sleep(1);
		}
	} else if (lock_op == ACL_FLOCK_OP_EXCLUSIVE) {
		while (1) {
			flags = LOCKFILE_EXCLUSIVE_LOCK;
			if ((operation & ACL_FLOCK_OP_NOWAIT))
				flags |= LOCKFILE_FAIL_IMMEDIATELY;

			if(LockFileEx(fd, flags, 0, 1, 0, &ovlp))
				return (0);

			if ((operation & ACL_FLOCK_OP_NOWAIT)) {
				acl_msg_error("%s(%d): lock error(%s)", myname, __LINE__,
					acl_last_strerror(ebuf,sizeof(ebuf)));
				return (-1);
			}
			sleep(1);
		}
	}

	acl_msg_error("%s(%d): invalid lock_op(%d)", myname, __LINE__, lock_op);
	return (-1);
}