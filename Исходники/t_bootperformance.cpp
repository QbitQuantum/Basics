void CTzBootPerformanceTest::TestBootupPerformanceL()
	{
	TTime startTime;
	TTime endTime;
	startTime.UniversalTime();

	RTz tz;
	User::LeaveIfError(tz.Connect());
	endTime.UniversalTime();
	tz.Close();
	
	TTimeIntervalMicroSeconds micros = endTime.MicroSecondsFrom(startTime);
	_LIT(KBootTime, "Time to connect time zone server = %d (ms) \n");
	test.Printf(KBootTime,micros);
	
#ifndef __WINS__
	
#ifdef GetPerformanceBaseline
	bootTimeBaseLine = micros.Int64();
	_LIT(KBootTimeBaseLine, "The baseline of boot-up time = %d (ms) \n");
	test.Printf(KBootTimeBaseLine,bootTimeBaseLine);
#else
	test((micros.Int64()-bootTimeBaseLine)/bootTimeBaseLine<0.1);
#endif
	
#endif
	}