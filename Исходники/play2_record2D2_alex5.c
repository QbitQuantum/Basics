double_buffer( InfoStruct *recInfo, float *leadSnds[], float *lagSnds[], float *locations, float *azimuths, float *rove, float *scalesLead, float *scalesLag, float *attensLead, int nSignal )
{
FILE	*fptr;
long	seekpos = 0;
float	preloadScale = .2;
int		i, j;

char	OutFNA [MAX_FILENAME_LEN];
char	OutFNB [MAX_FILENAME_LEN];

float	temp;

int		record = recInfo->record;
int		cnt = 1;

unsigned int DEC_FACT = recInfo->decimateFactor;
unsigned int SignalPlayFlag = 0;
unsigned int signalScale = 0, Signalcnt = 0, readflag = 0;
unsigned int MAX_SIGNAL_JITTER = recInfo->max_signal_jitter;
unsigned int NUM_CARRIERS_TO_ROVE = recInfo->num_carriers;
unsigned int rove_id;
unsigned int TRIALS_TO_SHOW = 3;

long	NPTS = recInfo->buf_pts;

/* just for plotting PDR trace in real time */
long	DEC_PTS = ceil(NPTS / pow(2, DEC_FACT));
long	ONSET = ceil(recInfo->sound_onset / pow(2, DEC_FACT));
long	NPTS_totalplay = recInfo->nptsTotalPlay;
long	templ;
long	buffer_cnt=0;
float	HAB_LOC = recInfo->hab_loc;

int		src[3];
float	sf[3];

div_t	div_result;

int		loc;

/* Display output variables: */
int     t0,t1, n;
float	elapsed_time;
float	rem_time;
int		min;
float	sec, cntdown;
char	str[100] = { '\0' };
float	pdrBuffer[DEFAULT_PTS];
int		len;
float	xy[2];

/* select SS1 output */
int		ss_id, out_port;

srand( (unsigned)time( NULL ) );

/* setup session info display */
len = ceil(NPTS * (SRATE/1E3));

// was commented out - put back in on Sep 14, 2009
if (record)
{
	play0_record0(recInfo->outFN1, recInfo->outFN2);
	remove(recInfo->outFN1);
	remove(recInfo->outFN2);
	//remove(recInfo->AD_FN);
}
// end comment out


if(!S2init(0, INIT_SECONDARY, 20000))
	mexErrMsgTxt("S2init failed");

if(!APlock(200, 0))
{
	S2close();
	mexErrMsgTxt("APLock failed");
}

if(!XBlock(200, 0))
{
	APunlock(0);
	S2close();
	mexErrMsgTxt("XBlock failed");
}

trash();
dropall();

// set up buffers
allot16( PLAY_SPEC, 10);
allot16( CHA_SEQ, 10);
allot16( BUF_A1, NPTS);
allot16( BUF_A2, NPTS);
allot16( CHB_SEQ, 10);
allot16( BUF_B1, NPTS);
allot16( BUF_B2, NPTS);

// play specification list
dpush(10);
value(0);
make(0,CHA_SEQ);
make(1,CHB_SEQ);
make(2,0);
qpop16(PLAY_SPEC);

// playsequence for ChanA
dpush(10);
value(0);
make(0,BUF_A1);
make(1,1);
make(2,BUF_A2);
make(3,1);
make(4,0);
qpop16(CHA_SEQ);
// playsequence for ChanB
dpush(10);
value(0);
make(0,BUF_B1);
make(1,1);
make(2,BUF_B2);
make(3,1);
make(4,0);
qpop16(CHB_SEQ);


if (record)			// record eye signal
{
	// set up buffers
	allot16( REC_SPEC, 10);
	allot16( RECCHA_SEQ, 10);
	allot16( RECBUF_A1, NPTS);
	allot16( RECBUF_A2, NPTS);
	allot16( RECCHB_SEQ, 10);
	allot16( RECBUF_B1, NPTS);
	allot16( RECBUF_B2, NPTS);

	temp = ceil(NPTS / pow(2, DEC_FACT));
	allot16( DECBUF_A, temp);
	allot16( DECBUF_B, temp);

	// record specification list
	dpush(10);
	value(0);
	make(0,RECCHA_SEQ);
	make(1,RECCHB_SEQ);
	make(2,0);
	qpop16(REC_SPEC);

	// recordsequence for ChanA
	dpush(10);
	value(0);
	make(0,RECBUF_A1);
	make(1,1);
	make(2,RECBUF_A2);
	make(3,1);
	make(4,0);
	qpop16(RECCHA_SEQ);
	// recordsequence for ChanB
	dpush(10);
	value(0);
	make(0,RECBUF_B1);
	make(1,1);
	make(2,RECBUF_B2);
	make(3,1);
	make(4,0);
	qpop16(RECCHB_SEQ);
}

// allot and load buffers for LEAD SOUNDS
for( j=0; j<NUM_CARRIERS_TO_ROVE; j++ ) {
	allotf( BUF_LEAD(j), NPTS);
	pushf(leadSnds[j], NPTS);
	qpopf(BUF_LEAD(j));
}

// allot and load buffers for LAG SOUNDS
for( j=0; j<NUM_CARRIERS_TO_ROVE; j++ ) {
	allotf( BUF_LAG(j), NPTS);
	pushf(lagSnds[j], NPTS);
	qpopf(BUF_LAG(j));
}

// setup PD1
PD1clear(1);
PD1srate(1,SRATE);
PD1npts(1,-1);

PD1resetDSP(1,0xFFF);
dropall();
PD1clrsched(1);
PD1nstrms(1, 2, record*2);

PD1addsimp(1, IREG[0], DAC[0]);  
PD1specIB (1, IB[0],   IREG[0]);

PD1addsimp(1, IREG[1], DAC[1]);  
PD1specIB (1, IB[1],   IREG[1]);

if (record)
{
	PD1specOB (1, OB[1], ADC[1]);
	PD1specOB (1, OB[0], ADC[0]);
}

PF1freq(1,12000,0);
PF1freq(2,12000,0);

dropall();

/* set LED thresholds */
PD1setIO(1,0.01,9.99,0.01,9.99);

/* setup signal switchers */

/* SWITCH BETWEEN 8 LAG SPEAKERS (Nos. 2, 3, 4, ... 9) */
/* (NOTE: Speaker #1 is reserved for the lead sound) */

SS1clear(1); /* left SS1 (LAG) */
SS1mode(1, QUAD_2_1); /* inputs 1, 3, 5, 7 => outputs A,B,C,D */
SS1select(1,0,1); /* Default Lag Output is A (Hab Location) */

// set attenuation
PA4atten(1,0); /* lead channel */
PA4atten(2,0); /* lag ch */

// ready,set,go!!
dropall();

// nothing to chanA (LEAD)
dpush(NPTS);
value(0);
qpop16(BUF_A1);

dpush(NPTS);
value(0);
qpop16(BUF_A2);
		
// nothing to chanB (LAG)
dpush(NPTS);
value(0);
qpop16(BUF_B1);
				
dpush(NPTS);
value(0);
qpop16(BUF_B2);				
			
seqplay(PLAY_SPEC);
if (record)
	seqrecord(REC_SPEC);
		
PD1arm (1);
pfireall();
PD1go (1);

do
{
 	do{}while (playseg(1)==BUF_A1);		// wait for #1 buffers to finish
	
	t0 = clock();

	SignalPlayFlag = 0;

	if(signalScale >0)
	{
		readflag = 1;
	}
	else if(readflag)
	{
		readflag = 0;
		SignalPlayFlag = 1;
	}
	

	
	/* count down to next test trial */
	cntdown = (recInfo->ISI - cnt)*(NPTS*SRATE/1E6);
	for(i=0; i<(recInfo->n_trials - Signalcnt); i++) {
		if(locations[Signalcnt+i]!=HAB_LOC)
			break;
		cntdown += (recInfo->ISI+1)*(NPTS*SRATE/1E6);

	}
		
		
	/* display session info */
	
	elapsed_time = seekpos*(SRATE/1E6);
	div_result = div( elapsed_time, 60 );
	min = div_result.quot; sec = elapsed_time - (60*min);
	memset(str,'\0',sizeof(str));
	n=sprintf(str,"session.elapsed_time(1)=%i; session.elapsed_time(2)=%.3f;",min,sec);
	mexEvalString(str);
	rem_time = NPTS_totalplay*(SRATE/1E6) - elapsed_time;
	div_result = div( rem_time, 60 );
	min = div_result.quot; sec = rem_time - (60*min);
	memset(str,'\0',sizeof(str));
	n=sprintf(str,"session.rem_time(1)=%i; session.rem_time(2)=%.3f;",min,sec);
	mexEvalString(str);
	div_result = div( cntdown, 60 );
	min = div_result.quot; sec = cntdown - (60*min);
	memset(str,'\0',sizeof(str));
	n=sprintf(str,"session.next_test_trial(1)=%i; session.next_test_trial(2)=%.3f;",min,sec);
	mexEvalString(str);
	mexEvalString("sessionPlots('Update Session Info');");
	
	
	// re-loading #1 playbuffers
	// LEAD to chanA LAG to chanB
	dropall();
	if (cnt==recInfo->ISI)
	{
		// Jitter trial presentation
		if (MAX_SIGNAL_JITTER > 0)
		{
			cnt = ( rand() % (2*MAX_SIGNAL_JITTER+1) ) - MAX_SIGNAL_JITTER; // gives a range of +/- MAX_SIGNAL_JITTER
		} else
		{
			cnt = 0;
		}
		

		loc = locations[Signalcnt];
		/* location series indicates lag speaker # (2, 3, 4, ... 9) */

	
		// set attenuation
		PA4atten(1,attensLead[loc-2]); /* lead channel */
		PA4atten(2,0); /* lag ch */

		SS1clear(1); SS1clear(2);
		if (loc < 6) {
			ss_id = 1; /* use left SS1 */
			out_port = loc - 2; /* decrement by 2 for output selection */
		}
		else {
			ss_id = 2; /* use right SS1 */
			out_port = loc - 6; /* decrement by 6 for output selection */
		}
		
		SS1mode(ss_id, QUAD_2_1); /* inputs 1, 3, 5, 7 => outputs A,B,C,D */
		SS1select(ss_id,out_port,1); /* Chan B (LAG) location ( speakers A...D = 0...3 ) */


		
		/* plot a marker on trial sequence plot */
		memset(str,'\0',sizeof(str));
		n=sprintf(str,"session.trialcnt=%i; session.trialval=%10.1f;sessionPlots('Update Trial Plot');",Signalcnt+1,azimuths[loc-1]);
		mexEvalString(str);
		
		
		rove_id = rove[Signalcnt ++] - 1; /* decrement by 1 for C indexing */
		
		signalScale=scalesLead[loc-2];
		qpushf(BUF_LEAD(rove_id));
		scale(signalScale); /* always scale with first speaker scaling value */
		qpop16(BUF_A1);	

		signalScale=scalesLag[loc-2];
		qpushf(BUF_LAG(rove_id));
		scale(signalScale); /* decrement by 1 to get appropriate speaker scale value */
		qpop16(BUF_B1);

	}
	else
	{
		signalScale = 0;
		cnt++;
		dpush(NPTS);
		value(0);
		qpop16(BUF_A1);

		dpush(NPTS);
		value(0);
		qpop16(BUF_B1);	
	}

	
	if(record)
	{		// downloading  #1 recordbuffers
		qpush16 (RECBUF_A1);    
		decimate (DEC_FACT);
		make(0, SignalPlayFlag);
		make(1, loc);
		qpop16   (DECBUF_A);
		dama2disk16 (DECBUF_A, recInfo->outFN1, 1);

		qpush16 (RECBUF_B1);
		decimate (DEC_FACT);
		// plot PDR trace
		qdup();
		popf(pdrBuffer);
		// store last buffer in matlab variable for plotting
		for(i=0; i<DEC_PTS; i++) {
			memset(str,'\0',sizeof(str));
			n=sprintf(str,"session.last_buffer(%i+1)= %.5f;",i,pdrBuffer[i]);
			mexEvalString(str);
		}
		
		if(SignalPlayFlag) {
			if(locations[Signalcnt-1]==HAB_LOC) {
				mexEvalString("session.test_flag=1;");
			}
			else {
				mexEvalString("session.test_flag=Inf;");
			}
		}
		else {
			mexEvalString("session.test_flag=0;");
		}
		
		// tell sessionPlots to update trace
		mexEvalString("sessionPlots('Update Trace Plot');");
		make(0, SignalPlayFlag);
		make(1, loc);
		qpop16   (DECBUF_B);
		dama2disk16 (DECBUF_B, recInfo->outFN2, 1);
		dropall ();
		
	}
	
	/* processing time */
	
	t1=clock();
	memset(str,'\0',sizeof(str));
	n = sprintf(str,"session.proc_time = [session.proc_time %.3f];",((float) (t1-t0))/CLOCKS_PER_SEC);
	mexEvalString(str);
	mexEvalString("sessionPlots('Update Session Info');");
	
	seekpos += NPTS;
	if(seekpos < NPTS_totalplay)
	{
		// wait for #2 buffers to finish
		do{}while (playseg(1)==BUF_A2);		// wait for #2 buffers to finish

     	t0=clock();
     	
		SignalPlayFlag = 0;
	
		if(signalScale >0)
		{
			readflag = 1;
		}
		else if(readflag)
		{
			readflag = 0;
			SignalPlayFlag = 1;
		}
		
	/* count down to next test trial */
	cntdown = (recInfo->ISI - cnt)*(NPTS*SRATE/1E6);
	for(i=0; i<(recInfo->n_trials - Signalcnt); i++) {
		if(locations[Signalcnt+i]!=HAB_LOC)
			break;
		cntdown += (recInfo->ISI+1)*(NPTS*SRATE/1E6);

	}
		
		
	/* display session info */
	
	elapsed_time = seekpos*(SRATE/1E6);
	div_result = div( elapsed_time, 60 );
	min = div_result.quot; sec = elapsed_time - (60*min);
	memset(str,'\0',sizeof(str));
	n=sprintf(str,"session.elapsed_time(1)=%i; session.elapsed_time(2)=%.3f;",min,sec);
	mexEvalString(str);
	rem_time = NPTS_totalplay*(SRATE/1E6) - elapsed_time;
	div_result = div( rem_time, 60 );
	min = div_result.quot; sec = rem_time - (60*min);
	memset(str,'\0',sizeof(str));
	n=sprintf(str,"session.rem_time(1)=%i; session.rem_time(2)=%.3f;",min,sec);
	mexEvalString(str);
	div_result = div( cntdown, 60 );
	min = div_result.quot; sec = cntdown - (60*min);
	memset(str,'\0',sizeof(str));
	n=sprintf(str,"session.next_test_trial(1)=%i; session.next_test_trial(2)=%.3f;",min,sec);
	mexEvalString(str);
	mexEvalString("sessionPlots('Update Session Info');");

		// reload #2 playbuffers    LEAD to chanA LAG to chanB
		dropall();
		if (cnt==recInfo->ISI)
		{
			if (MAX_SIGNAL_JITTER > 0)
			{
				cnt = ( rand() % (2*MAX_SIGNAL_JITTER+1) ) - MAX_SIGNAL_JITTER; // gives a range of +/- MAX_SIGNAL_JITTER
			} else
			{
				cnt = 0;
			}
			
			loc = locations[Signalcnt];
			/* location series indicates lag speaker # (2, 3, 4, ... 9) */
	
			// set attenuation
			PA4atten(1,attensLead[loc-2]); /* lead channel */
			PA4atten(2,0); /* lag ch */
			
			SS1clear(1); SS1clear(2);
			if (loc < 6) {
				ss_id = 1; /* use left SS1 */
				out_port = loc - 2; /* decrement by 2 for output selection */
			}
			else {
				ss_id = 2; /* use right SS1 */
				out_port = loc - 6; /* decrement by 6 for output selection */
			}
		
			SS1mode(ss_id, QUAD_2_1); /* inputs 1, 3, 5, 7 => outputs A,B,C,D */
			SS1select(ss_id,out_port,1); /* Chan B (LAG) location ( speakers A...D = 0...3 ) */
		
			/* plot a marker on trial sequence plot */
			memset(str,'\0',sizeof(str));
			n=sprintf(str,"session.trialcnt=%i; session.trialval=%10.1f;sessionPlots('Update Trial Plot');",Signalcnt+1,azimuths[loc-1]);
			mexEvalString(str);

			rove_id = rove[Signalcnt ++] - 1; /* decrement by 1 for C indexing */
			
			signalScale=scalesLead[loc-2];
			qpushf(BUF_LEAD(rove_id));
			scale(signalScale); /* always scale with first speaker scaling value */
			qpop16(BUF_A2);	
	
			signalScale=scalesLag[loc-2];
			qpushf(BUF_LAG(rove_id));
			scale(signalScale); /* decrement by 1 to get appropriate speaker scale value */
			qpop16(BUF_B2);

		}
		else
		{
			signalScale = 0;
			cnt++;
			dpush(NPTS);
			value(0);;
			qpop16(BUF_A2);

			dpush(NPTS);
			value(0);
			qpop16(BUF_B2);
		}
		
		
		if (record)
		{		// download #2 recordbuffers
			qpush16 (RECBUF_A2);    
			decimate (DEC_FACT);
			make(0,SignalPlayFlag);
			make(1,loc);
			qpop16	(DECBUF_A);
			dama2disk16 (DECBUF_A, recInfo->outFN1, 1);

			qpush16 (RECBUF_B2);
			decimate (DEC_FACT);
			// plot PDR trace
			qdup();
			popf(pdrBuffer);
			// store last buffer in matlab variable for plotting
			for(i=0; i<DEC_PTS; i++) {
				memset(str,'\0',sizeof(str));
				n=sprintf(str,"session.last_buffer(%i+1)= %.5f;",i,pdrBuffer[i]);
				mexEvalString(str);
			}

			if(SignalPlayFlag) {
				if(locations[Signalcnt-1]==HAB_LOC) {
					mexEvalString("session.test_flag=1;");
				}
				else {
					mexEvalString("session.test_flag=Inf;");
				}
			}
			else {
				mexEvalString("session.test_flag=0;");
			}

			// tell sessionPlots to update trace
			mexEvalString("sessionPlots('Update Trace Plot');");
			make(0,SignalPlayFlag);
			make(1,loc);
			qpop16   (DECBUF_B);
			dama2disk16 (DECBUF_B, recInfo->outFN2, 1);
			dropall ();
		
		}

		if (playseg(1) !=BUF_A1)
		{
			PD1stop(1);
			mexPrintf("got to %d percent of the way\n",seekpos/NPTS_totalplay);
			mexErrMsgTxt(" APcard too slow? or outFNs incorrect?");
		}

		/* processing time */
	
		t1=clock();
		memset(str,'\0',sizeof(str));
		n = sprintf(str,"session.proc_time = [session.proc_time %.3f];",((float) (t1-t0))/CLOCKS_PER_SEC);
		mexEvalString(str);
		mexEvalString("sessionPlots('Update Session Info');");
		
	    seekpos += NPTS;
	}
	if (Signalcnt > nSignal)
		Signalcnt = 0;

} while(seekpos < NPTS_totalplay);

do{}while (playseg(1)==BUF_A1);		/* wait for last 2 buffers to finish */
do{}while (playseg(1)==BUF_A2);



PA4mute(1);
PA4mute(2);

PD1stop(1);
PD1clrIO(1);
PD1clear(1);

mexEvalString("sessionPlots('Finish Session');");

trash();
dropall();

APunlock(0);
XBunlock(0);
S2close();

}