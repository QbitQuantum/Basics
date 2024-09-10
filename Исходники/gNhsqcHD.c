pulsesequence()
{

/* DECLARE AND LOAD VARIABLES */

void        makeHHdec(), makeCdec(); 	                /* utility functions */

char        f1180[MAXSTR],   		      /* Flag to start t1 @ halfdwell */
            mag_flg[MAXSTR],      /* magic-angle coherence transfer gradients */
	    C13refoc[MAXSTR],		/* C13 sech/tanh pulse in middle of t1*/
	    NH2only[MAXSTR],		       /* spectrum of only NH2 groups */
	    T1[MAXSTR],				/* insert T1 relaxation delay */
	    T1rho[MAXSTR],		     /* insert T1rho relaxation delay */
	    T2[MAXSTR],				/* insert T2 relaxation delay */
	    TROSY[MAXSTR],			    /* do TROSY on N15 and H1 */
	    Hdecflg[MAXSTR],                       /* HH-h**o decoupling flag */
	    Cdecflg[MAXSTR];                /* low power C-13 decoupling flag */
 
int         icosel,          			  /* used to get n and p type */
            ihh=1,       /* used in HH decouling to improve water suppression */
            t1_counter,  		        /* used for states tppi in t1 */
	    rTnum,			/* number of relaxation times, relaxT */
	    rTcounter;		    /* to obtain maximum relaxT, ie relaxTmax */

double      tau1,         				         /*  t1 delay */
	    lambda = 0.91/(4.0*getval("JNH")), 	   /* 1/4J H1 evolution delay */
	    tNH = 1.0/(4.0*getval("JNH")),	  /* 1/4J N15 evolution delay */
	    relaxT = getval("relaxT"),		     /* total relaxation time */
	    rTarray[1000], 	    /* to obtain maximum relaxT, ie relaxTmax */
            maxrelaxT = getval("maxrelaxT"),    /* maximum relaxT in all exps */
	    ncyc,			 /* number of pulsed cycles in relaxT */
            pwr_dly,                 /* power delay */
        
/* the sech/tanh pulse is automatically calculated by the macro "proteincal", */  
/* and is called directly from your shapelib.                  		      */
   pwClvl = getval("pwClvl"), 	  	        /* coarse power for C13 pulse */
   pwC = getval("pwC"),     	      /* C13 90 degree pulse length at pwClvl */
   rf0,            	          /* maximum fine power when using pwC pulses */
   rfst,	                           /* fine power for the stCall pulse */

   compH = getval("compH"),        /* adjustment for H1 amplifier compression */
   compN = getval("compN"),       /* adjustment for N15 amplifier compression */
   compC = getval("compC"),       /* adjustment for C13 amplifier compression */

	calH = getval("calH"), /* multiplier on a pw pulse for H1 calibration */
   	tpwrsf = getval("tpwrsf"),    /* fine power adustment for soft pulse  */
   	pwHs = getval("pwHs"),	        /* H1 90 degree pulse length at tpwrs */
   	pwHH = 0.0,                     /* pwHH = pwHs for HH h**o-decoupling */
   	tpwrs,	  	              /* power for the pwHs ("H2Osinc") pulse */

	pwNlvl = getval("pwNlvl"),	              /* power for N15 pulses */
        pwN = getval("pwN"),          /* N15 90 degree pulse length at pwNlvl */
	calN = getval("calN"),   /* multiplier on a pwN pulse for calibration */
	slNlvl,					   /* power for N15 spin lock */
        slNrf = 1500.0,        /* RF field in Hz for N15 spin lock at 600 MHz */

	sw1 = getval("sw1"),

	gt1 = getval("gt1"),  		       /* coherence pathway gradients */
        gzcal = getval("gzcal"),               /* dac to G/cm conversion      */
	gzlvl1 = getval("gzlvl1"),
	gzlvl2 = getval("gzlvl2"),
        BPpwrlimits,                        /*  =0 for no limit, =1 for limit */

	gt0 = getval("gt0"),				   /* other gradients */
	gt3 = getval("gt3"),
	gt4 = getval("gt4"),
	gt5 = getval("gt5"),
	gstab = getval("gstab"),
	gzlvl0 = getval("gzlvl0"),
	gzlvl3 = getval("gzlvl3"),
	gzlvl4 = getval("gzlvl4"),
	gzlvl5 = getval("gzlvl5");

    P_getreal(GLOBAL,"BPpwrlimits",&BPpwrlimits,1);

    getstr("f1180",f1180);
    getstr("mag_flg",mag_flg);
    getstr("C13refoc",C13refoc);
    getstr("NH2only",NH2only);
    getstr("T1",T1);
    getstr("T1rho",T1rho);
    getstr("T2",T2);
    getstr("TROSY",TROSY);
    getstr("Hdecflg", Hdecflg);
    getstr("Cdecflg", Cdecflg);

/*   LOAD PHASE TABLE    */
	
        settable(t3,2,phi3);
	settable(t4,1,phx);
   if (TROSY[A]=='y')
       {settable(t1,1,ph_x);
	settable(t9,1,phx);
 	settable(t10,1,phy);
	settable(t11,1,phx);
	settable(t12,2,recT);}
    else
       {settable(t1,1,phx);
	settable(t9,8,phi9);
 	settable(t10,1,phx);
	settable(t11,1,phy);
	settable(t12,4,rec);}



/*   INITIALIZE VARIABLES   */

/* maximum fine power for pwC pulses (and initialize rfst) */
	rf0 = 4095.0;    rfst=0.0;

/* 180 degree adiabatic C13 pulse from 0 to 200 ppm */
     if (C13refoc[A]=='y')
       {rfst = (compC*4095.0*pwC*4000.0*sqrt((30.0*sfrq/600.0+7.0)/0.35));   
	rfst = (int) (rfst + 0.5);
	if ( 1.0/(4000.0*sqrt((30.0*sfrq/600.0+7.0)/0.35)) < pwC )
           { text_error( " Not enough C13 RF. pwC must be %f usec or less.\n", 
	    (1.0e6/(4000.0*sqrt((30.0*sfrq/600.0+7.0)/0.35))) ); psg_abort(1); }}

/* selective H20 one-lobe sinc pulse */
    if(pwHs > 1e-6)
      tpwrs = tpwr - 20.0*log10(pwHs/(compH*pw*1.69));  /* needs 1.69 times more */
    else                    	                    /* power than a square pulse */
      tpwrs = 0.0;
    tpwrs = (int) (tpwrs);    
    if (tpwrsf<4095.0) tpwrs = tpwrs + 6.0;
    if (tpwrsf < 4095.0) 
    {
      tpwrs = tpwrs + 6.0;   
      pwr_dly = POWER_DELAY + PWRF_DELAY;
    }
    else pwr_dly = POWER_DELAY;

/* power level for N15 spinlock (90 degree pulse length calculated first) */
	slNlvl = 1/(4.0*slNrf*sfrq/600.0) ;
	slNlvl = pwNlvl - 20.0*log10(slNlvl/(pwN*compN));
	slNlvl = (int) (slNlvl + 0.5);

/* use 1/8J times for relaxation measurements of NH2 groups */
  if ( (NH2only[A]=='y') && ((T1[A]=='y') || (T1rho[A]=='y') || (T2[A]=='y')) )	
     {  tNH = tNH/2.0;  }

/* reset calH and calN for 2D if inadvertently left at 2.0 */
  if (ni>1.0) {calH=1.0; calN=1.0;}

/* make shapes and set up parameters for HH h**o-decoupling */
    if(Cdecflg[0] == 'y') makeCdec();
    if(Hdecflg[0] == 'y') makeHHdec();
    if(Hdecflg[0] != 'n')
    { 
      pwHH = pwHs; 
      pwHs = 0.0; 
    }


/* CHECK VALIDITY OF PARAMETER RANGES */

  if ((TROSY[A]=='y') && (gt1 < -2.0e-4 + pwHs + 1.0e-4 + 2.0*POWER_DELAY))
  { text_error( " gt1 is too small. Make gt1 equal to %f or more.\n",    
    (-2.0e-4 + pwHs + 1.0e-4 + 2.0*POWER_DELAY) ); psg_abort(1); }

  if((dm[A] == 'y' || dm[B] == 'y' || dm[C] == 'y' ))
  { text_error("incorrect dec1 decoupler flags! Should be 'nnn' "); psg_abort(1); }

  if((dm2[A] == 'y' || dm2[B] == 'y'))
  { text_error("incorrect dec2 decoupler flags! Should be 'nny' "); psg_abort(1); }

  if( dpwr2 > 50 )
  { text_error("don't fry the probe, DPWR2 too large!  ");   	    psg_abort(1); }

  if( pw > 50.0e-6 )
  { text_error("dont fry the probe, pw too high ! ");               psg_abort(1); } 
  
  if( pwN > 100.0e-6 )
  { text_error("dont fry the probe, pwN too high ! ");              psg_abort(1); }



/*  RELAXATION TIMES AND FLAGS */  

/* evaluate maximum relaxT, relaxTmax chosen by the user */
  rTnum = getarray("relaxT", rTarray);
  relaxTmax = rTarray[0];
  for (rTcounter=1; rTcounter<rTnum; rTcounter++)
      if (relaxTmax < rTarray[rTcounter]) relaxTmax = rTarray[rTcounter];


/* compare relaxTmax with maxrelaxT */
  if (maxrelaxT > relaxTmax)  relaxTmax = maxrelaxT; 


if ( ((T1rho[A]=='y') || (T2[A]=='y')) && (relaxTmax > d1) )
{ text_error("Maximum relaxation time, relaxT, is greater than d1 ! "); psg_abort(1);}

if ( ((T1[A]=='y') && (T1rho[A]=='y'))   ||   ((T1[A]=='y') && (T2[A]=='y')) ||
    ((T1rho[A]=='y') && (T2[A]=='y')) )
{ text_error("Choose only one relaxation measurement ! ");          psg_abort(1); } 


if ( ((T1[A]=='y') || (T1rho[A]=='y')) && 
       ((relaxT*100.0 - (int)(relaxT*100.0+1.0e-4)) > 1.0e-6) )
 { text_error("Relaxation time, relaxT, must be zero or multiple of 10msec"); psg_abort(1);}
 

 if ( (T2[A]=='y') && 
           (((relaxT+0.01)*50.0 - (int)((relaxT+0.01)*50.0+1.0e-4)) > 1.0e-6) )
{ text_error("Relaxation time, relaxT, must be odd multiple of 10msec"); psg_abort(1);}

if ( ((T1rho[A]=='y') || (T2[A]=='y'))  &&  (relaxTmax > 0.25) && (ix==1) ) 
{ printf("WARNING, sample heating will result for relaxT>0.25sec"); }

if ( ((T1rho[A]=='y') ||  (T2[A]=='y'))  &&  (relaxTmax > 0.5) ) 
{ text_error("relaxT greater than 0.5 seconds will heat sample"); psg_abort(1);}


if ( ((NH2only[A]=='y') || (T1[A]=='y') || (T1rho[A]=='y') || (T2[A]=='y'))
   &&  (TROSY[A]=='y') ) 
{ text_error("TROSY not implemented with NH2 spectrum, or relaxation exps."); psg_abort(1);} 


if ((TROSY[A]=='y') && (dm2[C] == 'y'))
{ text_error("Choose either TROSY='n' or dm2='n' ! ");              psg_abort(1); }
/* PHASES AND INCREMENTED TIMES */

/*  Phase incrementation for hypercomplex 2D data, States-Haberkorn element */

    if (TROSY[A]=='y')
	 {  if (phase1 == 2)   				      icosel = -1;
            else 	  {  tsadd(t4,2,4);  tsadd(t10,2,4);  icosel = +1;  }
	 }
    else {  if (phase1 == 2)  {tsadd(t10,2,4); icosel = +1;}
            else 			       icosel = -1;    
	 }

    if(Hdecflg[0] != 'n') ihh = icosel;

/*  Set up f1180  */
   
    tau1 = d2;
    if((f1180[A] == 'y') && (ni > 1.0)) 
	{ tau1 += ( 1.0 / (2.0*sw1) ); if(tau1 < 0.2e-6) tau1 = 0.0; }
    tau1 = tau1/2.0;



/* Calculate modifications to phases for States-TPPI acquisition          */

   if( ix == 1) d2_init = d2;
   t1_counter = (int) ( (d2-d2_init)*sw1 + 0.5 );
   if(t1_counter % 2) 
	{ tsadd(t3,2,4); tsadd(t12,2,4); }



/*  Correct inverted signals for NH2 only spectra  */

   if ((NH2only[A]=='y') && (T1[A]=='n')  &&  (T1rho[A]=='n')  && (T2[A]=='n'))
      { tsadd(t3,2,4); }



/* BEGIN PULSE SEQUENCE */

status(A);

	obspower(tpwr);
	decpower(pwClvl);
	decpwrf(rf0);
 	dec2power(pwNlvl);
	txphase(zero);
        decphase(zero);
        dec2phase(zero);
        if(Hdecflg[0] != 'n')
        {
          delay(5.0e-5);
          rgpulse(pw,zero,rof1,0.0);                 
          rgpulse(pw,one,0.0,rof1);                 
          zgradpulse(1.5*gzlvl0, 0.5e-3);
          delay(5.0e-4);
          rgpulse(pw,zero,rof1,0.0);                 
          rgpulse(pw,one,0.0,rof1);                 
          zgradpulse(-gzlvl0, 0.5e-3);
        }
        
	delay(d1);

 
/*  xxxxxxxxxxxxxxxxx  CONSTANT SAMPLE HEATING FROM N15 RF xxxxxxxxxxxxxxxxx  */

 if  (T1rho[A]=='y')
 	{dec2power(slNlvl);
         dec2rgpulse(relaxTmax-relaxT, zero, 0.0, 0.0);
    	 dec2power(pwNlvl);}
	
 if  (T2[A]=='y')      
 	{ncyc = 8.0*100.0*(relaxTmax - relaxT);
         if (BPpwrlimits > 0.5)
          {
           dec2power(pwNlvl-3.0);    /* reduce for probe protection */
           pwN=pwN*compN*1.4;
          }
    	 if (ncyc > 0)
       	    {initval(ncyc,v1);
             loop(v1,v2);
       	     delay(0.625e-3 - pwN);
      	     dec2rgpulse(2*pwN, zero, 0.0, 0.0);
      	     delay(0.625e-3 - pwN);
            endloop(v2);}
         if (BPpwrlimits > 0.5)
          {
           dec2power(pwNlvl);         /* restore normal value */
           pwN=getval("pwN");
          }
 	}
/*  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  */
        rcvroff();
	if (TROSY[A]=='n')   
	dec2rgpulse(pwN, zero, 0.0, 0.0);   /*destroy N15 magnetization*/
	zgradpulse(gzlvl0, 0.5e-3);
	delay(1.0e-4);
	if (TROSY[A]=='n')    dec2rgpulse(pwN, one, 0.0, 0.0);
	zgradpulse(0.7*gzlvl0, 0.5e-3);
	decpwrf(rfst);
	txphase(t1);
	delay(5.0e-4);

      if ( dm3[B] == 'y' )     /* begins optional 2H decoupling */
        {
          lk_hold();
          dec3rgpulse(1/dmf3,one,10.0e-6,2.0e-6);
          dec3unblank();
          dec3phase(zero);
          delay(2.0e-6);
          setstatus(DEC3ch, TRUE, 'w', FALSE, dmf3);
        }

   	rgpulse(calH*pw,t1,0.0,0.0);                 /* 1H pulse excitation */

	txphase(zero);
   	dec2phase(zero);
	zgradpulse(gzlvl0, gt0);
	delay(lambda - gt0 - pwHH);
	
	if(Hdecflg[0] != 'n')
	{
	  obspower(tpwrs);
          if (tpwrsf<4095.0) obspwrf(tpwrsf); 
	  shaped_pulse("H2Osinc", pwHH, two, 5.0e-5, 0.0);
	  obspower(tpwr);
          if (tpwrsf<4095.0) obspwrf(4095.0);
   	  sim3pulse(2.0*pw, 0.0, 2.0*pwN, zero, zero, zero, 0.0, 0.0);
   	  obspower(tpwrs);
          if (tpwrsf<4095.0) obspwrf(tpwrsf);
   	  shaped_pulse("H2Osinc", pwHH, two, 5.0e-5, 0.0);
   	  obspower(tpwr);
          if (tpwrsf<4095.0) obspwrf(4095.0); 
   	}
   	else 
   	  sim3pulse(2.0*pw, 0.0, 2.0*pwN, zero, zero, zero, 0.0, 0.0);
   	
   	txphase(one);
	zgradpulse(gzlvl0, gt0);
	delay(lambda - gt0 - pwHH);        
 	rgpulse(pw, one, 0.0, 0.0);
	txphase(two);
        obspower(tpwrs);
        if (tpwrsf<4095.0) obspwrf(tpwrsf);
        shaped_pulse("H2Osinc", pwHs, two, 5.0e-5, 0.0);
	obspower(tpwr);
	if (tpwrsf<4095.0) obspwrf(4095.0);

        if (TROSY[A]=='y')
	  zgradpulse(ihh*gzlvl3, gt3);           
	else
	  zgradpulse(-ihh*gzlvl3, gt3);
	dec2phase(t3);
	delay(2.0e-4);
   	dec2rgpulse(calN*pwN, t3, 0.0, 0.0);
	txphase(zero);
	decphase(zero);

/*  xxxxxxxxxxxxxxxxxx    OPTIONS FOR N15 RELAXATION    xxxxxxxxxxxxxxxxxxxx  */

if ( (T1[A]=='y') || (T1rho[A]=='y') || (T2[A]=='y') )
   {
    dec2phase(one);
    zgradpulse(gzlvl4, gt4);				/* 2.0*GRADIENT_DELAY */
    delay(tNH - gt4 - 2.0*GRADIENT_DELAY);

    sim3pulse(2.0*pw, 0.0, 2.0*pwN, zero, zero, one, 0.0, 0.0);

    zgradpulse(gzlvl4, gt4);				/* 2.0*GRADIENT_DELAY */
    delay(tNH - gt4 - 2.0*GRADIENT_DELAY);
   }

		/*   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    */

if  (T1[A]=='y')
   {
    dec2rgpulse(pwN, one, 0.0, 0.0);
    dec2phase(three);

    zgradpulse(gzlvl0, gt0);				/* 2.0*GRADIENT_DELAY */
    delay(2.5e-3 - gt0 - 2.0*GRADIENT_DELAY - pw);
    rgpulse(2.0*pw, zero, 0.0, 0.0);
    delay(2.5e-3 - pw);

    ncyc = (100.0*relaxT);
    initval(ncyc,v4);
    if (ncyc > 0)
	{loop(v4,v5);

	 delay(2.5e-3 - pw);
    	 rgpulse(2.0*pw, two, 0.0, 0.0);
   	 delay(2.5e-3 - pw);

	 delay(2.5e-3 - pw);
    	 rgpulse(2.0*pw, zero, 0.0, 0.0);
   	 delay(2.5e-3 - pw);

	 endloop(v5);}

    dec2rgpulse(pwN, three, 0.0, 0.0);
   }

		/*   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    */

			     /* Theory suggests 8.0 is better than 2PI as RF  */
			     /* field multiplier and experiment confirms this.*/
if  (T1rho[A]=='y')          /* Shift evolution of 2.0*pwN/PI for one pulse   */
   {		             /* at end left unrefocused as for normal sequence*/
    delay(1.0/(8.0*slNrf) - pwN);
    decrgpulse(pwN, zero, 0.0, 0.0);
    dec2power(slNlvl);
           				   /* minimum 5ms spinlock to dephase */
    dec2rgpulse((2.5e-3-pw), zero, 0.0, 0.0);	         /*  spins not locked */
    sim3pulse(2.0*pw, 0.0, 2.0*pw, zero, zero, zero, 0.0, 0.0);
    dec2rgpulse((2.5e-3-pw), zero, 0.0, 0.0);

    ncyc = 100.0*relaxT;
    initval(ncyc,v4);	    if (ncyc > 0)
	  {loop(v4,v5);
           dec2rgpulse((2.5e-3-pw), zero, 0.0, 0.0);
   	   sim3pulse(2.0*pw, 0.0, 2.0*pw, two, zero, zero, 0.0, 0.0);
           dec2rgpulse((2.5e-3-pw), zero, 0.0, 0.0);
           dec2rgpulse((2.5e-3-pw), zero, 0.0, 0.0);
   	   sim3pulse(2.0*pw, 0.0, 2.0*pw, zero, zero, zero, 0.0, 0.0);
           dec2rgpulse((2.5e-3-pw), zero, 0.0, 0.0);
           endloop(v5);} 

    dec2power(pwNlvl);	
    decrgpulse(pwN, zero, 0.0, 0.0);
    delay(1.0/(8.0*slNrf) + 2.0*pwN/PI - pwN);
   }
		/*   xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx    */

if  (T2[A]=='y')
   {
    dec2phase(zero);
    initval(0.0,v3);   initval(180.0,v4);
    if (BPpwrlimits > 0.5)
     {
      dec2power(pwNlvl-3.0);    /* reduce for probe protection */
      pwN=pwN*compN*1.4;
     }

    ncyc = 100.0*relaxT;
    initval(ncyc,v5);

    loop(v5,v6);

      initval(3.0,v7);
      loop(v7,v8);
       	delay(0.625e-3 - pwN);
      	dec2rgpulse(2.0*pwN, zero, 0.0, 0.0);
      	delay(0.625e-3 - pwN);
      endloop(v8);

      delay(0.625e-3 - pwN - SAPS_DELAY);
      add(v4,v3,v3);  obsstepsize(1.0);  xmtrphase(v3);	   	/* SAPS_DELAY */
      dec2rgpulse(2.0*pwN, zero, 0.0, 0.0);
      delay(0.625e-3 - pwN - pw);

      rgpulse(2*pw, zero, 0.0, 0.0);

      delay(0.625e-3 - pwN - pw );
      dec2rgpulse(2.0*pwN, zero, 0.0, 0.0);
      xmtrphase(zero);						/* SAPS_DELAY */
      delay(0.625e-3 - pwN - SAPS_DELAY);
  
      initval(3.0,v9);
      loop(v9,v10);
      	delay(0.625e-3 - pwN);
      	dec2rgpulse(2.0*pwN, zero, 0.0, 0.0);
      	delay(0.625e-3 - pwN);
      endloop(v10);

    endloop(v6);
    if (BPpwrlimits > 0.5)
     {
      dec2power(pwNlvl);    /* restore normal value */
      pwN=getval("pwN");
     }
   }

/*  xxxxxxxxxxxxxxxxxx    OPTIONS FOR N15 EVOLUTION    xxxxxxxxxxxxxxxxxxxxx  */
	txphase(zero);
	dec2phase(t9);

if ( (NH2only[A]=='y') || (T1[A]=='y') || (T1rho[A]=='y') || (T2[A]=='y') )	
{      
    	delay(tau1);
         			  /* optional sech/tanh pulse in middle of t1 */
    	if (C13refoc[A]=='y') 				   /* WFG_START_DELAY */
           {decshaped_pulse("stC200", 1.0e-3, zero, 0.0, 0.0);
            delay(tNH - 1.0e-3 - WFG_START_DELAY - 2.0*pw);}
    	else
           {delay(tNH - 2.0*pw);}
    	rgpulse(2.0*pw, zero, 0.0, 0.0);
    	if (tNH < gt1 + 1.99e-4)  delay(gt1 + 1.99e-4 - tNH);

    	delay(tau1);

    	dec2rgpulse(2.0*pwN, t9, 0.0, 0.0);

        if (mag_flg[A] == 'y')  magradpulse(gzcal*gzlvl1, gt1);
        else  zgradpulse(gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	txphase(t4);
    	dec2phase(t10);
   	if (tNH > gt1 + 1.99e-4)  delay(tNH - gt1 - 2.0*GRADIENT_DELAY);
   	else   delay(1.99e-4 - 2.0*GRADIENT_DELAY);
}

else if (TROSY[A]=='y')
{
  	if ( (C13refoc[A]=='y') && (tau1 > 0.5e-3 + WFG2_START_DELAY) )
           {delay(tau1 - 0.5e-3 - WFG2_START_DELAY);     /* WFG2_START_DELAY */
            decshaped_pulse("stC200", 1.0e-3, zero, 0.0, 0.0);
            delay(tau1 - 0.5e-3);}
	else    delay(2.0*tau1);

        if (mag_flg[A] == 'y')  magradpulse(gzcal*gzlvl1, gt1);
        else  zgradpulse(gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	delay(2.0e-4 - 2.0*GRADIENT_DELAY);

	dec2rgpulse(2.0*pwN, t9, 0.0, 0.0);

	txphase(three);

        delay(gt1 + 2.0e-4 - pwHs - 1.0e-4 - 2.0*pwr_dly);
        obspower(tpwrs);
	if (tpwrsf<4095.0) obspwrf(tpwrsf);
        shaped_pulse("H2Osinc", pwHs, three, 5.0e-5, 0.0);
        obspower(tpwr);
	if (tpwrsf<4095.0) obspwrf(4095.0);

	txphase(t4);
	delay(5.0e-5);
}

else
{					  	    /* fully-coupled spectrum */
        if (dm2[C]=='n')  {rgpulse(2.0*pw, zero, 0.0, 0.0);  pw=0.0;}		

  	if ( (C13refoc[A]=='y') && (tau1 > 0.5e-3 + WFG2_START_DELAY) )
           {delay(tau1 - 0.5e-3 - WFG2_START_DELAY);     /* WFG2_START_DELAY */
            simshaped_pulse("", "stC200", 2.0*pw, 1.0e-3, zero, zero, 0.0, 0.0);
            delay(tau1 - 0.5e-3);
            delay(gt1 + 2.0e-4);}
	else
           {delay(tau1);
            rgpulse(2.0*pw, zero, 0.0, 0.0);
            delay(gt1 + 2.0e-4 - 2.0*pw);
            delay(tau1);} 
 
	pw=getval("pw");
	dec2rgpulse(2.0*pwN, t9, 0.0, 0.0);

        if (mag_flg[A] == 'y')  magradpulse(gzcal*gzlvl1, gt1);
        else  zgradpulse(gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	txphase(t4);
	dec2phase(t10);
	delay(2.0e-4 - 2.0*GRADIENT_DELAY);
}

	if  (T1rho[A]=='y')   delay(POWER_DELAY); 


/*  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  */
	if (TROSY[A]=='y')  rgpulse(pw, t4, 0.0, 0.0);
	else                sim3pulse(pw, 0.0, pwN, t4, zero, t10, 0.0, 0.0);

	txphase(zero);
	dec2phase(zero);
	zgradpulse(gzlvl5, gt5);
	if (TROSY[A]=='y')   delay(lambda - 0.65*(pw + pwN) - gt5);
	else   delay(lambda - 1.3*pwN - gt5);

	sim3pulse(2.0*pw, 0.0, 2.0*pwN, zero, zero, zero, 0.0, 0.0);

	zgradpulse(gzlvl5, gt5);
	txphase(one);
	dec2phase(t11);
	delay(lambda - 1.3*pwN - gt5);

	sim3pulse(pw, 0.0, pwN, one, zero, t11, 0.0, 0.0);

	txphase(zero);
	dec2phase(zero);
	zgradpulse(1.5*gzlvl5, gt5);
	delay(lambda - 1.3*pwN - gt5);

        sim3pulse(2.0*pw, 0.0, 2.0*pwN, zero, zero, zero, 0.0, 0.0);

	dec2phase(t10);
	zgradpulse(1.5*gzlvl5, gt5);
	if (TROSY[A]=='y')   delay(lambda - 1.6*pwN - gt5);
	else   delay(lambda - 0.65*pwN - gt5);

	if (TROSY[A]=='y')   dec2rgpulse(pwN, t10, 0.0, 0.0); 
	else    	     rgpulse(pw, zero, 0.0, 0.0); 

	delay((gt1/10.0) + 1.0e-4 +gstab - 0.65*pw + 2.0*GRADIENT_DELAY + POWER_DELAY);

        if ( dm3[B] == 'y' )   /* turns off 2H decoupling  */
           {
           setstatus(DEC3ch, FALSE, 'c', FALSE, dmf3);
           dec3rgpulse(1/dmf3,three,2.0e-6,2.0e-6);
           dec3blank();
           lk_autotrig();   /* resumes lock pulsing */
           }

	rgpulse(2.0*pw, zero, 0.0, 0.0);

	dec2power(dpwr2);				       /* POWER_DELAY */
        if (mag_flg[A] == 'y')	  magradpulse(icosel*gzcal*gzlvl2, 0.1*gt1);
        else   zgradpulse(icosel*gzlvl2, 0.1*gt1);		/* 2.0*GRADIENT_DELAY */
        

        if(Cdecflg[0] == 'y')
        {
          delay(gstab-2.0*POWER_DELAY-PRG_START_DELAY+rof2);
          rcvron();
                           
          statusdelay(C,1.0e-4);		

          if (dm3[B] == 'y') 
          {
            delay(1/dmf3); 
            lk_sample();
          }
	  setreceiver(t12);
          pbox_decon(&Cdseq);
          
          if(Hdecflg[0] == 'y')
            homodec(&HHdseq);  
        }
        else
        {
          delay(gstab+rof2);
          rcvron();
                             
          statusdelay(C,1.0e-4);		

          if (dm3[B] == 'y') 
          {
            delay(1/dmf3); 
            lk_sample();
          }
	  setreceiver(t12);

          if(Hdecflg[0] == 'y')
            homodec(&HHdseq);        
        }
}		 