	bool wait() {
		BOOL result = SleepConditionVariableSRW( &condition, &lock, INFINITE, 0 );
		bool ret = false;
		if( result == TRUE ) {
			down();
			ReleaseSRWLockExclusive( &lock );
			ret = true;
		}
		return ret;
	}