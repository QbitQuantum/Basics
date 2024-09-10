status_t
Inode::Open(int mode, OpenFileCookie* cookie)
{
	ASSERT(cookie != NULL);

	MutexLocker locker(fStateLock);

	OpenDelegationData data;
	data.fType = OPEN_DELEGATE_NONE;
	if (fOpenState == NULL) {
		RevalidateFileCache();

		OpenState* state = new(std::nothrow) OpenState;
		if (state == NULL)
			return B_NO_MEMORY;

		state->fInfo = fInfo;
		state->fFileSystem = fFileSystem;
		state->fMode = mode & O_RWMASK;
		status_t result = OpenFile(state, mode, &data);
		if (result != B_OK) {
			delete state;
			return result;
		}

		fFileSystem->AddOpenFile(state);
		fOpenState = state;
		cookie->fOpenState = state;
		locker.Unlock();
	} else {
		fOpenState->AcquireReference();
		cookie->fOpenState = fOpenState;
		locker.Unlock();

		int newMode = mode & O_RWMASK;
		int oldMode = fOpenState->fMode & O_RWMASK;
		if (oldMode != newMode && oldMode != O_RDWR) {
			if (oldMode == O_RDONLY)
				RecallReadDelegation();

			status_t result = OpenFile(fOpenState, O_RDWR, &data);
			if (result != B_OK) {
				locker.Lock();
				ReleaseOpenState();
				return result;
			}
			fOpenState->fMode = O_RDWR;
		} else {
			int newMode = mode & O_RWMASK;
			uint32 allowed = 0;
			if (newMode == O_RDWR || newMode == O_RDONLY)
				allowed |= R_OK;
			if (newMode == O_RDWR || newMode == O_WRONLY)
				allowed |= W_OK;

			status_t result = Access(allowed);
			if (result != B_OK) {
				locker.Lock();
				ReleaseOpenState();
				return result;
			}
		}
	}

	if ((mode & O_TRUNC) == O_TRUNC) {
		struct stat st;
		st.st_size = 0;
		WriteStat(&st, B_STAT_SIZE);
		file_cache_set_size(fFileCache, 0);
	}

	cookie->fFileSystem = fFileSystem;
	cookie->fMode = mode;
	cookie->fLocks = NULL;

	if (data.fType != OPEN_DELEGATE_NONE) {
		Delegation* delegation
			= new(std::nothrow) Delegation(data, this, fOpenState->fClientID);
		if (delegation != NULL) {
			delegation->fInfo = fOpenState->fInfo;
			delegation->fFileSystem = fFileSystem;
			SetDelegation(delegation);
		}
	}

	return B_OK;
}