	inline void    unlock()
	{
	    if ((mlocked >0)  && (mLockThreadId == getThreadId())) 
	    {
	         mlocked --;
		 if( mlocked <=0 )
	 	{
	 		mlocked = 0;
			mLockThreadId = 0;
			mLock.unlock();	 	  
	 	}
	    }
	}