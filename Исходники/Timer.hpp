	NativeTimer(){
		MMRESULT result = timeGetDevCaps(&timeCaps_,sizeof(TIMECAPS));
		if( result != TIMERR_NOERROR ){
			timeCaps_.wPeriodMin = 1;
			isUseTimeGetTime_ = false;
			return;
		}
		if( timeCaps_.wPeriodMin >= 10 ){
			timeCaps_.wPeriodMin = 1;
			isUseTimeGetTime_ = false;
		}else{
			::timeBeginPeriod( timeCaps_.wPeriodMin );
			isUseTimeGetTime_ = true;
		}
	}