/*
 * timeRDTSC()
 * This routine sets up PIT counter 2 to count down 1/20 of a second.
 * It pauses until the value is latched in the counter
 * and then reads the time stamp counter to return to the caller.
 */
uint64_t timeRDTSC(void)
{
    int		attempts = 0;
    uint64_t    latchTime;
    uint64_t	saveTime,intermediate;
    unsigned int timerValue, lastValue;
    //boolean_t	int_enabled;
    /*
     * Table of correction factors to account for
     *	 - timer counter quantization errors, and
     *	 - undercounts 0..5
     */
#define SAMPLE_CLKS_EXACT	(((double) CLKNUM) / 20.0)
#define SAMPLE_CLKS_INT		((int) CLKNUM / 20)
#define SAMPLE_NSECS		(2000000000LL)
#define SAMPLE_MULTIPLIER	(((double)SAMPLE_NSECS)*SAMPLE_CLKS_EXACT)
#define ROUND64(x)		((uint64_t)((x) + 0.5))
    uint64_t	scale[6] = {
		ROUND64(SAMPLE_MULTIPLIER/(double)(SAMPLE_CLKS_INT-0)), 
		ROUND64(SAMPLE_MULTIPLIER/(double)(SAMPLE_CLKS_INT-1)), 
		ROUND64(SAMPLE_MULTIPLIER/(double)(SAMPLE_CLKS_INT-2)), 
		ROUND64(SAMPLE_MULTIPLIER/(double)(SAMPLE_CLKS_INT-3)), 
		ROUND64(SAMPLE_MULTIPLIER/(double)(SAMPLE_CLKS_INT-4)), 
		ROUND64(SAMPLE_MULTIPLIER/(double)(SAMPLE_CLKS_INT-5))
    };
    
    //int_enabled = ml_set_interrupts_enabled(FALSE);
    
restart:
    if (attempts >= 9) // increase to up to 9 attempts.
    {
        // This will flash-reboot. TODO: Use tscPanic instead.
        printf("Timestamp counter calibation failed with %d attempts\n", attempts);
    }
    attempts++;
    enable_PIT2();		// turn on PIT2
    set_PIT2(0);		// reset timer 2 to be zero
    latchTime = rdtsc64();	// get the time stamp to time 
    latchTime = get_PIT2(&timerValue) - latchTime; // time how long this takes
    set_PIT2(SAMPLE_CLKS_INT);	// set up the timer for (almost) 1/20th a second
    saveTime = rdtsc64();	// now time how long a 20th a second is...
    get_PIT2(&lastValue);
    get_PIT2(&lastValue);	// read twice, first value may be unreliable
    do {
		intermediate = get_PIT2(&timerValue);
		if (timerValue > lastValue)
        {
			// Timer wrapped
			set_PIT2(0);
			disable_PIT2();
			goto restart;
		}
		lastValue = timerValue;
    } while (timerValue > 5);
    printf("timerValue	  %d\n",timerValue);
    printf("intermediate 0x%016llx\n",intermediate);
    printf("saveTime	  0x%016llx\n",saveTime);
    
    intermediate -= saveTime;		// raw count for about 1/20 second
    intermediate *= scale[timerValue];	// rescale measured time spent
    intermediate /= SAMPLE_NSECS;	// so its exactly 1/20 a second
    intermediate += latchTime;		// add on our save fudge
    
    set_PIT2(0);			// reset timer 2 to be zero
    disable_PIT2();			// turn off PIT 2

    //ml_set_interrupts_enabled(int_enabled);
    return intermediate;
}