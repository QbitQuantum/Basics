			//	 A function responsible for releasing a SlimReadWriter lock and putting the calling thread to sleep.
			inline bool	ConditionVariable::sleep( SRWLOCK& slim_read_writer_lock , const DWORD milliseconds , bool shared )
			{
				return ( SleepConditionVariableSRW(&_variable,&slim_read_writer_lock,milliseconds, ( shared  ?  CONDITION_VARIABLE_LOCKMODE_SHARED : 0 ) ) > FALSE  ?  true : false );
			};