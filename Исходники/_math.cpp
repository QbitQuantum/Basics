	void Detect	()
	{
		// General CPU identification
		if (!_cpuid	(&ID))	
		{
			// Core.Fatal		("Fatal error: can't detect CPU/FPU.");
			abort				();
		}

		// Timers & frequency
		u64			start,end;
		u32			dwStart,dwTest;

		SetPriorityClass		(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);

		// Detect Freq
		dwTest	= timeGetTime();
		do { dwStart = timeGetTime(); } while (dwTest==dwStart);
		start	= GetCLK();
		while (timeGetTime()-dwStart<1000) ;
		end		= GetCLK();
		clk_per_second = end-start;

		// Detect RDTSC Overhead
		clk_overhead	= 0;
		u64 dummy		= 0;
		for (int i=0; i<256; i++)	{
			start			=	GetCLK();
			clk_overhead	+=	GetCLK()-start-dummy;
		}
		clk_overhead		/=	256;

		// Detect QPC Overhead
		QueryPerformanceFrequency	((PLARGE_INTEGER)&qpc_freq)	;
		qpc_overhead	= 0;
		for (int i=0; i<256; i++)	{
			start			=	QPC();
			qpc_overhead	+=	QPC()-start-dummy;
		}
		qpc_overhead		/=	256;

		SetPriorityClass	(GetCurrentProcess(),NORMAL_PRIORITY_CLASS);

		clk_per_second	-=	clk_overhead;
		clk_per_milisec	=	clk_per_second/1000;
		clk_per_microsec	=	clk_per_milisec/1000;

		_control87	( _PC_64,   MCW_PC );
//		_control87	( _RC_CHOP, MCW_RC );
		double a,b;
		a = 1;		b = double(clk_per_second);
		clk_to_seconds = float(double(a/b));
		a = 1000;	b = double(clk_per_second);
		clk_to_milisec = float(double(a/b));
		a = 1000000;b = double(clk_per_second);
		clk_to_microsec = float(double(a/b));
	}