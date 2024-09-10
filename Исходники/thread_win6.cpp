	void shared_mutex::unlock() {
		bool ex = d->ex;
		if(ex) {
			d->ex=false;
			ReleaseSRWLockExclusive(&d->m);
		}
		else 
			ReleaseSRWLockShared(&d->m);
	}