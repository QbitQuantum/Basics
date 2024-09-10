		IFACEMETHODIMP LockServer(BOOL fLock) final
		{
			CoLockObjectExternal(this, fLock, TRUE);
			return S_OK;
		}