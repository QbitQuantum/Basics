void pulsesequence()
{



/* DECLARE AND LOAD VARIABLES */

char        f1180[MAXSTR],   		      /* Flag to start t1 @ halfdwell */
            f2180[MAXSTR],    		      /* Flag to start t2 @ halfdwell */
            mag_flg[MAXSTR],      /* magic-angle coherence transfer gradients */
 	    TROSY[MAXSTR],			    /* do TROSY on N15 and H1 */
	    CT_c[MAXSTR],
	    h1dec[MAXSTR];
 
int         icosel,          			  /* used to get n and p type */
            t1_counter=getval("t1_counter"),      /* used for states tppi in t1 */
            t2_counter=getval("t2_counter"),      /* used for states tppi in t2 */
            nli = getval("nli"),
            nli2 = getval("nli2");

double      tau1,         				         /*  t1 delay */
            tau2,        				         /*  t2 delay */
	    tauCC = 7.0e-3, 		   /* delay for Ca to Cb cosy */
	    tauC = 13.3e-3,	           /* constantTime for 13Cb evolution */
            timeTN = getval("timeTN"),     /* constant time for 15N evolution */
	    kappa = 5.4e-3,
	    lambda = 2.4e-3,
	    zeta = 3.0e-3,
	    taud = 1.7e-3,
            
	pwClvl = getval("pwClvl"), 	        /* coarse power for C13 pulse */
        pwC = getval("pwC"),          /* C13 90 degree pulse length at pwClvl */
	rf0,            	  /* maximum fine power when using pwC pulses */

/* 90 degree pulse at Cab (46ppm), first off-resonance null at CO (174ppm)    */
        pwC1,		              /* 90 degree pulse length on C13 at rf1 */
        rf1,		       /* fine power for 5.1 kHz rf for 600MHz magnet */

/* 180 degree pulse at Ca (46ppm), first off-resonance null at CO(174ppm)     */
        pwC2,		                    /* 180 degree pulse length at rf2 */
        rf2,		      /* fine power for 11.4 kHz rf for 600MHz magnet */

/* the following pulse lengths for SLP pulses are automatically calculated    */
/* by the macro "proteincal".  SLP pulse shapes, "offC7" etc are called       */
/* directly from your shapelib.                    			      */
   pwC7 = getval("pwC7"),  /*180 degree pulse at CO(174ppm) null at Ca(56ppm) */
   pwC7a = getval("pwC7a"),    /* pwC7a=pwC7, but not set to zero when pwC7=0 */
   phshift7,            /* phase shift induced on Cab by pwC7 ("offC7") pulse */
   pwZ,					   /* the largest of pwC7 and 2.0*pwN */
   pwZ1,                /* the larger of pwC7a and 2.0*pwN for 1D experiments */
   rf7,	                           /* fine power for the pwC7 ("offC7") pulse */

/* the following pulse lengths for SLP pulses are automatically calculated    */
/* by the macro "proteincal".  SLP pulse shapes, "offC5" etc are called       */
/* directly from your shapelib.                                               */
   pwC5 = getval("pwC5"),  /*180 degree pulse at CO(174ppm) null at Ca(56ppm) */
   rf5,                            /* fine power for the pwC7 ("offC7") pulse */

/* g3 inversion pulse in the t1 period (centred at 150ppm)                     */
	pwCgCO_lvl = getval("pwCgCO_lvl"),
	pwCgCO = getval("pwCgCO"),



   compH = getval("compH"),       /* adjustment for C13 amplifier compression */
   compC = getval("compC"),       /* adjustment for C13 amplifier compression */

   	pwHs = getval("pwHs"),	        /* H1 90 degree pulse length at tpwrs */
   	tpwrs,	  	              /* power for the pwHs ("H2Osinc") pulse */

   	pwHd,	    		        /* H1 90 degree pulse length at tpwrd */
   	tpwrd,	  	                   /* rf for WALTZ decoupling */
        waltzB1 = getval("waltzB1"),  /* waltz16 field strength (in Hz)     */

	pwNlvl = getval("pwNlvl"),	              /* power for N15 pulses */
        pwN = getval("pwN"),          /* N15 90 degree pulse length at pwNlvl */

	sw1 = getval("sw1"),
	sw2 = getval("sw2"),

        gstab = getval("gstab"),
	gt1 = getval("gt1"),  		       /* coherence pathway gradients */
        gzcal = getval("gzcal"),             /* g/cm to DAC conversion factor */
	gzlvl1 = getval("gzlvl1"),
	gzlvl2 = getval("gzlvl2"),

	gt0 = getval("gt0"),				   /* other gradients */
	gt3 = getval("gt3"),
	gt4 = getval("gt4"),
	gt5 = getval("gt5"),
	gt7 = getval("gt7"),
	gt8 = getval("gt8"),
	gzlvl0 = getval("gzlvl0"),
	gzlvl3 = getval("gzlvl3"),
	gzlvl4 = getval("gzlvl4"),
	gzlvl5 = getval("gzlvl5"),
	gzlvl6 = getval("gzlvl6"),
	gzlvl7 = getval("gzlvl7"),
	gzlvl8 = getval("gzlvl8");

    getstr("f1180",f1180);
    getstr("f2180",f2180);
    getstr("mag_flg",mag_flg);
    getstr("TROSY",TROSY);
    getstr("CT_c",CT_c);
    getstr("h1dec",h1dec);



/*   LOAD PHASE TABLE    */

	settable(t2,1,phy);
	settable(t3,2,phi3);
	settable(t4,1,phx);
	settable(t5,4,phi5);
   if (TROSY[A]=='y')
       {settable(t8,1,phy);
	settable(t9,1,phx);
 	settable(t10,1,phy);
	settable(t11,1,phx);
	settable(t12,4,recT);}
    else
       {settable(t8,1,phx);
	settable(t9,8,phi9);
	settable(t10,1,phx);
	settable(t11,1,phy);
	settable(t12,4,rec);}




/*   INITIALIZE VARIABLES   */

    if( dpwrf < 4095 )
	{ printf("reset dpwrf=4095 and recalibrate C13 90 degree pulse");
	  psg_abort(1); }

    /* maximum fine power for pwC pulses */
	rf0 = 4095.0;

    /* 90 degree pulse on Cab, null at CO 128ppm away */
	pwC1 = sqrt(15.0)/(4.0*128.0*dfrq);
        rf1 = (compC*4095.0*pwC)/pwC1;
	rf1 = (int) (rf1 + 0.5);

    /* 180 degree pulse on Cab, null at CO 128ppm away */
        pwC2 = sqrt(3.0)/(2.0*128.0*dfrq);
	rf2 = (4095.0*compC*pwC*2.0)/pwC2;
	rf2 = (int) (rf2 + 0.5);	
	if( rf2 > 4095 )
	      { printf("Recalibrate so that C13 90 <22us*600/sfrq"); psg_abort(1);}

    /* 180 degree one-lobe sinc pulse on CO, null at Ca 118ppm away */
	rf7 = (compC*4095.0*pwC*2.0*1.65)/pwC7a; /* needs 1.65 times more     */
	rf7 = (int) (rf7 + 0.5);		 /* power than a square pulse */

    /* 90 degree one-lobe sinc pulse on CO, null at Ca 118ppm away */
        rf5 = (compC*4095.0*pwC*1.69)/pwC5;     /* needs 1.69 times more     */
        rf5 = (int) (rf5 + 0.5);                /* power than a square pulse */

    /* the pwC7 pulse at the middle of t1  */
        if ((nli2 > 0.0) && (nli == 1.0)) nli = 0.0;
        if (pwC7a > 2.0*pwN) pwZ = pwC7a; else pwZ = 2.0*pwN;
        if ((pwC7==0.0) && (pwC7a>2.0*pwN)) pwZ1=pwC7a-2.0*pwN; else pwZ1=0.0;
	if ( nli > 1 )     pwC7 = pwC7a;
	if ( pwC7 > 0 )   phshift7 = 320.0;
	else              phshift7 = 0.0;
	
    /* selective H20 one-lobe sinc pulse */
    tpwrs = tpwr - 20.0*log10(pwHs/(compH*pw*1.69)); /* needs 1.69 times more */
    tpwrs = (int) (tpwrs);                       /* power than a square pulse */

    /* power level and pulse time for WALTZ 1H decoupling */
	pwHd = 1/(4.0 * waltzB1) ;                          
	tpwrd = tpwr - 20.0*log10(pwHd/(compH*pw));
	tpwrd = (int) (tpwrd + 0.5);
 


/* CHECK VALIDITY OF PARAMETER RANGES */


    if ( 0.5*nli2*1/(sw2) > timeTN - WFG3_START_DELAY)
       { printf(" nli2 is too big. Make nli2 equal to %d or less.\n", 
  	 ((int)((timeTN - WFG3_START_DELAY)*2.0*sw2))); psg_abort(1);}

    if ( dm[A] == 'y' || dm[B] == 'y' || dm[C] == 'y' )
       { printf("incorrect dec1 decoupler flags! Should be 'nnn' "); psg_abort(1);}

    if ( dm2[A] == 'y' || dm2[B] == 'y' )
       { printf("incorrect dec2 decoupler flags! Should be 'nny' "); psg_abort(1);}

    if ( dm3[A] == 'y' || dm3[C] == 'y' )
       { printf("incorrect dec3 decoupler flags! Should be 'nyn' or 'nnn' ");
							             psg_abort(1);}	
    if ( dpwr2 > 46 )
       { printf("dpwr2 too large! recheck value  "); psg_abort(1);}

    if ( pw > 20.0e-6 )
       { printf(" pw too long ! recheck value "); psg_abort(1);} 
  
    if ( pwN > 100.0e-6 )
       { printf(" pwN too long! recheck value "); psg_abort(1);} 
 
    if ( TROSY[A]=='y' && dm2[C] == 'y')
       { text_error("Choose either TROSY='n' or dm2='n' ! "); psg_abort(1);}



/* PHASES AND INCREMENTED TIMES */

/*  Phase incrementation for hypercomplex 2D data, States-Haberkorn element */

    if (phase1 == 2)   { tsadd(t3,1,4); tsadd(t2,1,4);} 
    if (TROSY[A]=='y')
	 {  if (phase2 == 2)   				      icosel = +1;
            else 	    {tsadd(t4,2,4);  tsadd(t10,2,4);  icosel = -1;}
	 }
    else {  if (phase2 == 2)  {tsadd(t10,2,4); icosel = +1;}
            else 			       icosel = -1;    
	 }


/*  Set up f1180  */
   
    if( ix == 1) d2_init = d2;
    tau1 = d2_init + (t1_counter) / sw1;
    if((f1180[A] == 'y') && (nli > 1.0)) 
	{ tau1 += ( 1.0 / (2.0*sw1) ); if(tau1 < 0.2e-6) tau1 = 0.0; }
    tau1 = tau1/2.0;


/*  Set up f2180  */

    if( ix == 1) d3_init = d3;
    tau2 = d3_init + (t2_counter) / sw2;
    if((f2180[A] == 'y') && (nli2 > 1.0)) 
	{ tau2 += ( 1.0 / (2.0*sw2) ); if(tau2 < 0.2e-6) tau2 = 0.0; }
    tau2 = tau2/2.0;



/* Calculate modifications to phases for States-TPPI acquisition          */

   if(t1_counter % 2) 
	{ tsadd(t3,2,4); tsadd(t12,2,4); }

   if(t2_counter % 2) 
	{ tsadd(t8,2,4); tsadd(t12,2,4); }



/* BEGIN PULSE SEQUENCE */

status(A);
delay(d1);
if (dm3[B] == 'y') lk_hold();

rcvroff();
obspower(tpwr);
decpower(pwClvl);
dec2power(pwNlvl);
decpwrf(rf0);
obsoffset(tof);
txphase(zero);
decphase(zero);
dcplrphase(zero);
delay(1.0e-5);

dec2rgpulse(pwN, zero, 0.0, 0.0);  /*destroy N15 and C13 magnetization*/
decrgpulse(pwC, zero, 0.0, 0.0);
zgradpulse(gzlvl0, 0.5e-3);
delay(1.0e-4);
dec2rgpulse(pwN, one, 0.0, 0.0);
decrgpulse(pwC, zero, 0.0, 0.0);
zgradpulse(0.7*gzlvl0, 0.5e-3);
delay(5.0e-4);

rgpulse(pw,zero,0.0,0.0);                      /* 1H pulse excitation */

dec2phase(zero);
zgradpulse(gzlvl0, gt0);
delay(lambda - gt0);

sim3pulse(2.0*pw, 0.0, 2.0*pwN, zero, zero, zero, 0.0, 0.0);

txphase(one);
zgradpulse(gzlvl0, gt0);
delay(lambda - gt0);

rgpulse(pw, one, 0.0, 0.0);

obspower(tpwrs);
if (TROSY[A]=='y') {
  txphase(two);
  shaped_pulse("H2Osinc", pwHs, two, 5.0e-4, 0.0);
  obspower(tpwr);
  zgradpulse(gzlvl3, gt3);
  delay(2.0e-4);
  dec2rgpulse(pwN, zero, 0.0, 0.0);

  delay(0.5*kappa - 2.0*pw);

  rgpulse(2.0*pw, two, 0.0, 0.0);

  obspower(tpwrd);	  				       /* POWER_DELAY */
  decphase(zero);
  dec2phase(zero);
  decpwrf(rf7);
  delay(timeTN - 0.5*kappa - POWER_DELAY -WFG_START_DELAY);
}
else {
  txphase(zero);
  shaped_pulse("H2Osinc", pwHs, zero, 5.0e-4, 0.0);
  obspower(tpwrd);
  zgradpulse(gzlvl3, gt3);
  delay(2.0e-4);
  dec2rgpulse(pwN, zero, 0.0, 0.0);

  txphase(one);
  delay(kappa - pwHd - 2.0e-6 - PRG_START_DELAY);

  rgpulse(pwHd,one,0.0,0.0);
  txphase(zero);
  delay(2.0e-6);
  obsprgon("waltz16", pwHd, 90.0);	          /* PRG_START_DELAY */
  xmtron();
  decphase(zero);
  dec2phase(zero);
  decpwrf(rf7);
  delay(timeTN - kappa -WFG_START_DELAY);
}

sim3shaped_pulse("","offC7","",0.0, pwC7, 2.0*pwN, zero, zero, zero, 0.0, 0.0);

decphase(t3);
decpwrf(rf5);
delay(timeTN -WFG_STOP_DELAY -pwHd);

dec2rgpulse(pwN, zero, 0.0, 0.0);

if (TROSY[A]=='n') {
  xmtroff();
  obsprgoff();
  rgpulse(pwHd,three,2.0e-6,0.0);
}

delay(2.0e-6);
zgradpulse(gzlvl3, gt3);
delay(2.0e-4);

decpwrf(rf5); 
decshaped_pulse("offC5", pwC5, zero, 0.0, 0.0);
delay(2.0e-6);

zgradpulse(-gzlvl7, gt7);
decpwrf(rf0);
decphase(zero);
delay(zeta - gt7 - 0.5*10.933*pwC-2.0e-6);

  decrgpulse(pwC*158.0/90.0, zero, 0.0, 0.0);
  decrgpulse(pwC*171.2/90.0, two, 0.0, 0.0);
  decrgpulse(pwC*342.8/90.0, zero, 0.0, 0.0);      /* Shaka 6 composite */
  decrgpulse(pwC*145.5/90.0, two, 0.0, 0.0);
  decrgpulse(pwC*81.2/90.0, zero, 0.0, 0.0);
  decrgpulse(pwC*85.3/90.0, two, 0.0, 0.0);

delay(2.0e-6);
zgradpulse(-gzlvl7, gt7);
decpwrf(rf5);
decphase(one);
txphase(one);
delay(zeta - gt7 - 0.5*10.933*pwC - WFG_START_DELAY-2.0e-6);
                                                           /* WFG_START_DELAY */
decshaped_pulse("offC5", pwC5, one, 0.0, 0.0);

delay(2.0e-6);
zgradpulse(1.33*gzlvl3,gt3);
delay(200.0e-6);

if(dm3[B] == 'y'){                        /*optional 2H decoupling on */
  dec3unblank();
  dec3rgpulse(1/dmf3, one, 0.0, 0.0);
  dec3unblank();
  setstatus(DEC3ch, TRUE, 'w', FALSE, dmf3);
}

decpwrf(rf1);
decphase(t2);
txphase(one);

if (h1dec[A]=='y') {
  rgpulse(pwHd,one,0.0,0.0);
  txphase(zero);
  delay(2.0e-6);
  obsprgon("waltz16", pwHd, 90.0);                   /* PRG_START_DELAY */
  xmtron();
}

decrgpulse(pwC1, t3, 0.0, 0.0);
decphase(zero);

decpwrf(rf2);
delay(tauCC -gt5 -202.0e-6 -POWER_DELAY- pwHd -PRG_STOP_DELAY -1/dmf3
                                            -2.0e-6 - WFG_STOP_DELAY);

if(dm3[B] == 'y') {                     /*optional 2H decoupling off */
  dec3rgpulse(1/dmf3, three, 0.0, 0.0);
  dec3blank();
  setstatus(DEC3ch, FALSE, 'w', FALSE, dmf3);
  dec3blank();
}
else delay(1/dmf3 +WFG_STOP_DELAY);
 
if(h1dec[A]=='y') {
  xmtroff();
  obsprgoff();                                        /* PRG_STOP_DELAY */
  rgpulse(pwHd,three,2.0e-6,0.0);
}
else delay(pwHd +2.0e-6 +PRG_STOP_DELAY);
  
delay(2.0e-6);
zgradpulse(-gzlvl5, gt5);
delay(200.0e-6);

decrgpulse(pwC2,zero,0.0,0.0);

delay(2.0e-6);
zgradpulse(-gzlvl5, gt5);
delay(200.0e-6);
decpwrf(rf1);

if(h1dec[A]=='y'){
  rgpulse(pwHd,one,0.0,0.0);
  txphase(zero);
  delay(2.0e-6);
  obsprgon("waltz16", pwHd, 90.0);                /* PRG_START_DELAY */
  xmtron();
}
else delay(pwHd+2.0e-6+PRG_START_DELAY);

if(dm3[B] == 'y'){                        /*optional 2H decoupling on */
  dec3unblank();
  dec3rgpulse(1/dmf3, one, 0.0, 0.0);
  dec3unblank();
  setstatus(DEC3ch, TRUE, 'w', FALSE, dmf3);
}
else delay(1/dmf3+WFG_START_DELAY);

delay(tauCC -gt5 -202.0e-6 -POWER_DELAY -1/dmf3 -WFG_START_DELAY
		-POWER_DELAY -pwHd -2.0e-6 -PRG_START_DELAY
		-pwHd-2.0e-6-PRG_STOP_DELAY);

if((h1dec[A]=='y') && (h1dec[B]=='n')) {
  xmtroff();
  obsprgoff();                                    /* PRG_STOP_DELAY */
  rgpulse(pwHd,one,2.0e-6,0.0);
  decrgpulse(pwC1,t2,0.0,0.0);
}
else {
  delay(pwHd+2.0e-6+PRG_STOP_DELAY-POWER_DELAY);
  if ((h1dec[A]=='y')&&(h1dec[B]=='y')) {
    delay(POWER_DELAY);
    decrgpulse(pwC1,t2,0.0,0.0);
  }
  if ((h1dec[A]=='n')&&(h1dec[B]=='n')) {
    obspower(tpwr);
    simpulse(2.0*pw,pwC1,two,t2,0.0,0.0);  /* Assuming 2.0*pw < pwC1 */
  }
}
/* It could be h1dec='ny' ??? */	

/*   xxxxxxxxxxxxxxxxxxxxxx       13Cb EVOLUTION       xxxxxxxxxxxxxxxxxx    */

if (CT_c[0]=='n') {
  if ((nli>1.0) && (tau1>0.0)) {     /* total 13C evolution equals d2 exactly */
            /* 2.0*pwC1/PI compensates for evolution at 64% rate during pwC1 */
    decpwrf(rf7);
    if(tau1 - 2.0*pwC1/PI - WFG3_START_DELAY - 0.5*pwZ > 0.0) {
      delay(tau1 - 2.0*pwC1/PI - WFG3_START_DELAY - 0.5*pwZ);
							  /* WFG3_START_DELAY */
      sim3shaped_pulse("", "offC7", "", 0.0, pwC7a, 2.0*pwN, zero, zero, zero,
								      0.0, 0.0);
      initval(phshift7, v7);
      decstepsize(1.0);
      dcplrphase(v7);  				        /* SAPS_DELAY */
      delay(tau1 - 2.0*pwC1/PI  - SAPS_DELAY - 0.5*pwZ - 2.0e-6);
    }
    else {
      initval(180.0, v7);
      decstepsize(1.0);
      dcplrphase(v7);  				        /* SAPS_DELAY */
      delay(2.0*tau1 - 4.0*pwC1/PI - SAPS_DELAY - 2.0e-6);
    }
  }

  else if (nli==1.0) {    /* special 1D check of pwC7 phase enabled when nli=1 */
 	 decpwrf(rf7);
	 delay(10.0e-6 + SAPS_DELAY + 0.5*pwZ1 + WFG_START_DELAY);
							  /* WFG3_START_DELAY */
	 sim3shaped_pulse("", "offC7", "", 0.0, pwC7, 2.0*pwN, zero, zero, zero,
							          2.0e-6, 0.0);
	 initval(phshift7, v7);
	 decstepsize(1.0);
	 dcplrphase(v7);  					/* SAPS_DELAY */
	 delay(10.0e-6 + WFG3_START_DELAY + 0.5*pwZ1);
      }

      else{		       /* 13Ca evolution refocused for 1st increment  */
	decpwrf(rf2);
	decrgpulse(pwC2, zero, 2.0e-6, 0.0);
      }
}  /* H1 dec. and H2 dec. status are not changed through nonCT evolution*/

else {		/* 13C CONSTANT TIME EVOLUTION */
  decpwrf(rf0);
  decpower(pwCgCO_lvl);
  if(h1dec[B]=='y') {
    if(tau1 - 2.0*pwC1/PI -WFG_START_DELAY -2*POWER_DELAY> 0.0) 
      delay(tau1 - 2.0*pwC1/PI -WFG_START_DELAY - 2*POWER_DELAY);
    decshaped_pulse("CgCO1",pwCgCO,zero,0.0,0.0);
    delay(tauC -gt8 -202.0e-6 -pwHd -2.0e-6 -PRG_STOP_DELAY
			-pwCgCO -pwC2 -WFG_STOP_DELAY-1/dmf3);

    if(dm3[B] == 'y') {                     /*optional 2H decoupling off */
      dec3rgpulse(1/dmf3, three, 0.0, 0.0);
      dec3blank();
      setstatus(DEC3ch, FALSE, 'w', FALSE, dmf3);
      dec3blank();
    }
    else delay(1/dmf3+WFG_STOP_DELAY); 
    xmtroff();
    obsprgoff();                                        /* PRG_STOP_DELAY */
    rgpulse(pwHd,three,2.0e-6,0.0);
  }
  if ((h1dec[B]=='n')&&(dm3[B]=='n')) {
    obspower(tpwr);
    if(tau1 - 2.0*pwC1/PI -WFG_START_DELAY -3*POWER_DELAY> 0.0) {
      delay(tau1 - 2.0*pwC1/PI -WFG3_START_DELAY - 3*POWER_DELAY);
      simshaped_pulse("","CgCO1",2.0*pw,pwCgCO,two,zero,0.0,0.0);
    }
    else simshaped_pulse("","CgCO1",2.0*pw,pwCgCO,two,zero,0.0,0.0);
    obspower(tpwrd);
    delay(tauC -gt8 -202.0e-6 -pwCgCO -pwC2 -POWER_DELAY);
  }
  if ((h1dec[B]=='n')&&(dm3[B]=='y')) {
    obspower(tpwr);
    if(tau1 - 2.0*pwC1/PI - WFG_START_DELAY -3*POWER_DELAY> 0.0) {
      delay(tau1 - 2.0*pwC1/PI - WFG3_START_DELAY - 3*POWER_DELAY);
      decshaped_pulse("CgCO1",pwCgCO,zero,0.0,0.0);
    }
    else decshaped_pulse("CgCO1",pwCgCO,zero,0.0,0.0);
    delay(taud-0.5*pwC2-WFG_START_DELAY-WFG_STOP_DELAY-pwCgCO);
    rgpulse(2.0*pw,two,0.0,0.0);
    obspower(tpwrd);
    delay(tauC -taud -gt8 -202e-6 -2.0*pw -POWER_DELAY -1/dmf3
	-pwCgCO -pwC2 -WFG_STOP_DELAY);
    dec3rgpulse(1/dmf3, three, 0.0, 0.0);
    dec3blank();
    setstatus(DEC3ch, FALSE, 'w', FALSE, dmf3);
    dec3blank();
  }

  delay(2.0e-6);
  zgradpulse(gzlvl8,gt8);
  delay(200.0e-6-2*POWER_DELAY);
  decpower(pwClvl);decpwrf(rf2);

  decrgpulse(pwC2,zero,0.0,0.0);

  delay(2.0e-6);
  zgradpulse(gzlvl8,gt8);        
  delay(200.0e-6-2*POWER_DELAY);

  decpower(pwCgCO_lvl);decpwrf(rf0);

  if(h1dec[A]=='y'){
    rgpulse(pwHd,one,0.0,0.0);
    txphase(zero);
    delay(2.0e-6);
    obsprgon("waltz16", pwHd, 90.0);                /* PRG_START_DELAY */
    xmtron();
  }
  else delay(pwHd+ 2.0e-6 +PRG_START_DELAY);

  if(dm3[B] == 'y'){                        /*optional 2H decoupling on */
    dec3unblank();
    dec3rgpulse(1/dmf3, one, 0.0, 0.0);
    dec3unblank();
    setstatus(DEC3ch, TRUE, 'w', FALSE, dmf3);
  }
  else delay(1/dmf3+WFG_START_DELAY);

  delay(tauC -tau1 -202.0e-6 -gt8 -pwCgCO -WFG_START_DELAY
	-WFG_STOP_DELAY -POWER_DELAY -1/dmf3 -WFG_START_DELAY
	-pwHd -2.0e-6 -PRG_START_DELAY);
  decshaped_pulse("CgCO2",pwCgCO,zero,0.0,0.0);
}		/* END of C13 CONSTANT TIME EVOLUTION */

decphase(one);
decpower(pwClvl); 
decpwrf(rf1);

decrgpulse(pwC1, one, 2.0e-6, 0.0);
delay(tauCC - gt5 -202.0e-6 -2.0e-6 -pwHd -PRG_STOP_DELAY
				-1/dmf3 -WFG_STOP_DELAY);

if(dm3[B] == 'y') {                     /*optional 2H decoupling off */
  dec3rgpulse(1/dmf3, three, 0.0, 0.0);
  dec3blank();
  setstatus(DEC3ch, FALSE, 'w', FALSE, dmf3);
  dec3blank();
}
else delay(1/dmf3+WFG_STOP_DELAY);

if(h1dec[B]=='y') {
  xmtroff();
  obsprgoff();                                      /* PRG_STOP_DELAY */
  rgpulse(pwHd,three,2.0e-6,0.0);
}
else delay(2.0e-6+pwHd+PRG_STOP_DELAY);

delay(2.0e-6);
zgradpulse(gzlvl5*1.33, gt5);
delay(200.0e-6-2.0*POWER_DELAY);
decpwrf(rf2);
decphase(zero);

decrgpulse(pwC2, zero, 0.0, 0.0);

delay(2.0e-6);
zgradpulse(gzlvl5*1.33,gt5);
delay(200.0e-6-2.0*POWER_DELAY);
decpwrf(rf1);
decphase(t5);

if(h1dec[A]=='y'){
  rgpulse(pwHd,one,0.0,0.0);
  txphase(zero);
  delay(2.0e-6);
  obsprgon("waltz16", pwHd, 90.0);                /* PRG_START_DELAY */
  xmtron();
}
else delay(pwHd+ 2.0e-6 +PRG_START_DELAY);

if(dm3[B] == 'y'){                        /*optional 2H decoupling on */
  dec3unblank();
  dec3rgpulse(1/dmf3, one, 0.0, 0.0);
  dec3unblank();
  setstatus(DEC3ch, TRUE, 'w', FALSE, dmf3);
}
else delay(1/dmf3+WFG_START_DELAY);


delay(tauCC - gt5 -202.0e-6 -1/dmf3 -WFG_START_DELAY -2.0e-6 -pwHd 
						-PRG_START_DELAY);

/*decrgpulse(pwC1, t5, 0.0, 0.0); */
decrgpulse(pwC1, zero, 0.0, 0.0); 

decpwrf(rf5);
decshaped_pulse("offC5", pwC5, one, 0.0, 0.0);

delay(zeta - gt7 -202.0e-6 - pwHd -2.0e-6 -PRG_STOP_DELAY
      -1/dmf3 -WFG_STOP_DELAY -0.5*10.933*pwC-2.0e-6);

if(dm3[B] == 'y') {                     /*optional 2H decoupling off */
  dec3rgpulse(1/dmf3, three, 0.0, 0.0);
  dec3blank();
  setstatus(DEC3ch, FALSE, 'w', FALSE, dmf3);
  dec3blank();
}
else delay(1/dmf3+WFG_STOP_DELAY);

if(h1dec[A]=='y') {
  xmtroff();
  obsprgoff();                                      /* PRG_STOP_DELAY */
  rgpulse(pwHd,three,2.0e-6,0.0);
}
else delay(2.0e-6+pwHd+PRG_STOP_DELAY);

delay(2.0e-6);
zgradpulse(-gzlvl7, gt7);
decpwrf(rf0);
decphase(zero);
delay(200.0e-6-2.0*POWER_DELAY);

  decrgpulse(pwC*158.0/90.0, zero, 0.0, 0.0);
  decrgpulse(pwC*171.2/90.0, two, 0.0, 0.0);
  decrgpulse(pwC*342.8/90.0, zero, 0.0, 0.0);      /* Shaka 6 composite */
  decrgpulse(pwC*145.5/90.0, two, 0.0, 0.0);
  decrgpulse(pwC*81.2/90.0, zero, 0.0, 0.0);
  decrgpulse(pwC*85.3/90.0, two, 0.0, 0.0);

delay(2.0e-6);
zgradpulse(-gzlvl7, gt7);
delay(200.0e-6);
decpwrf(rf5);
decphase(one);
txphase(one);

if(h1dec[A]=='y'){
  rgpulse(pwHd,one,0.0,0.0);
  txphase(zero);
  delay(2.0e-6);
  obsprgon("waltz16", pwHd, 90.0);                /* PRG_START_DELAY */
  xmtron();
}
else delay(pwHd+ 2.0e-6 +PRG_START_DELAY);

if(dm3[B] == 'y'){                        /*optional 2H decoupling on */
  dec3unblank();
  dec3rgpulse(1/dmf3, one, 0.0, 0.0);
  dec3unblank();
  setstatus(DEC3ch, TRUE, 'w', FALSE, dmf3);
}
else delay(1/dmf3+WFG_START_DELAY);

delay(zeta - gt7 - 0.5*10.933*pwC - WFG_START_DELAY-2.0e-6
	-1/dmf3 -WFG_START_DELAY -pwHd -2.0e-6 -PRG_START_DELAY);
                                                           /* WFG_START_DELAY */
decshaped_pulse("offC5", pwC5, t5, 0.0, 0.0);


/*  xxxxxxxxxxxxxxxxxx    OPTIONS FOR N15 EVOLUTION    xxxxxxxxxxxxxxxxxxxxx  */

dec2phase(t8);
txphase(one);
dcplrphase(zero);
obspower(tpwrd);

if(dm3[B] == 'y')  {                     /*optional 2H decoupling off */
  dec3rgpulse(1/dmf3, three, 0.0, 0.0);
  dec3blank();
  setstatus(DEC3ch, FALSE, 'w', FALSE, dmf3);
  dec3blank();
}

if(h1dec[A]=='y') { 
  xmtroff();
  obsprgoff();                                      /* PRG_STOP_DELAY */
  rgpulse(pwHd,three,2.0e-6,0.0);
}

zgradpulse(gzlvl4, gt4);
delay(2.0e-4);

if (TROSY[A]=='n') {
  rgpulse(pwHd,one,0.0,0.0);
  txphase(zero);
  delay(2.0e-6);
  obsprgon("waltz16", pwHd, 90.0);
  xmtron();
}

dec2rgpulse(pwN, t8, 0.0, 0.0);

decphase(zero);
dec2phase(t9);
decpwrf(rf7);
delay(timeTN - tau2);

sim3shaped_pulse("","offC7","",0.0, pwC7, 2.0*pwN, zero, zero, t9, 0.0, 0.0);

dec2phase(t10);
decpwrf(rf5);

if (TROSY[A]=='y')
{    if (tau2 > gt1 + 2.0*GRADIENT_DELAY + 1.5e-4 + pwHs)
	{
	  txphase(three);
          delay(timeTN - pwC2) ;         /* WFG_START_DELAY */
          decrgpulse(pwC2, zero, 0.0, 0.0);
          delay(tau2 - gt1 - 2.0*GRADIENT_DELAY - 1.5e-4 - pwHs);
          if (mag_flg[A]=='y')  magradpulse(icosel*gzcal*gzlvl1, gt1);
          else  zgradpulse(icosel*gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwrs);				       /* POWER_DELAY */
	  delay(1.0e-4 - POWER_DELAY);
   	  shaped_pulse("H2Osinc", pwHs, three, 0.0, 0.0);
	  txphase(t4);
	  obspower(tpwr);				       /* POWER_DELAY */
	  delay(0.5e-4 - POWER_DELAY);
	}

    else if (tau2 > pwHs + 0.5e-4)
	{
	  txphase(three);
          delay(timeTN-pwC2-gt1-2.0*GRADIENT_DELAY-1.0e-4);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else  zgradpulse(icosel*gzlvl1, gt1);	   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwrs);				       /* POWER_DELAY */
	  delay(1.0e-4 - POWER_DELAY);                     /* WFG_START_DELAY */
          decrgpulse(pwC2, zero, 0.0, 0.0);
          delay(tau2 - pwHs - 0.5e-4);
   	  shaped_pulse("H2Osinc", pwHs, three, 0.0, 0.0);
	  txphase(t4);
	  obspower(tpwr);				       /* POWER_DELAY */
	  delay(0.5e-4 - POWER_DELAY);
	}
    else
	{
	  txphase(three);
          delay(timeTN - pwC2 - gt1 - 2.0*GRADIENT_DELAY
							    - 1.5e-4 - pwHs);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else  zgradpulse(icosel*gzlvl1, gt1);	   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwrs);				       /* POWER_DELAY */
	  delay(1.0e-4 - POWER_DELAY);                     /* WFG_START_DELAY */
   	  shaped_pulse("H2Osinc", pwHs, three, 0.0, 0.0);
	  txphase(t4);
	  obspower(tpwr);				       /* POWER_DELAY */
	  delay(0.5e-4 - POWER_DELAY);
          decrgpulse(pwC2, zero, 0.0, 0.0);
          delay(tau2);
	}
}
else
{
    if (tau2 > kappa)
	{
          delay(timeTN - pwC2);     	   /* WFG_START_DELAY */
          decrgpulse(pwC2, zero, 0.0, 0.0);
          delay(tau2 - kappa - PRG_STOP_DELAY - pwHd - 2.0e-6);
          xmtroff();
          obsprgoff();					    /* PRG_STOP_DELAY */
	  rgpulse(pwHd,three,2.0e-6,0.0);
	  txphase(t4);
          delay(kappa - gt1 - 2.0*GRADIENT_DELAY - 1.0e-4);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else    zgradpulse(icosel*gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwr);				       /* POWER_DELAY */
	  delay(1.0e-4 - POWER_DELAY);
	}
    else if (tau2 > (kappa - pwC2))
	{
          delay(timeTN + tau2 - kappa - PRG_STOP_DELAY - pwHd - 2.0e-6);
          xmtroff();
          obsprgoff();					    /* PRG_STOP_DELAY */
	  rgpulse(pwHd,three,2.0e-6,0.0);
	  txphase(t4);                                     /* WFG_START_DELAY */
          decrgpulse(pwC2, zero, 0.0, 0.0);
          delay(kappa -pwC2 -gt1 -2.0*GRADIENT_DELAY -1.0e-4);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else    zgradpulse(icosel*gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwr);				       /* POWER_DELAY */
	  delay(1.0e-4 - POWER_DELAY);
	}
    else if (tau2 > gt1 + 2.0*GRADIENT_DELAY + 1.0e-4)
	{
          delay(timeTN + tau2 - kappa - PRG_STOP_DELAY - pwHd - 2.0e-6);
          xmtroff();
          obsprgoff();					    /* PRG_STOP_DELAY */
	  rgpulse(pwHd,three,2.0e-6,0.0);
	  txphase(t4);
          delay(kappa - tau2 - pwC2 );   /* WFG_START_DELAY */
          decrgpulse(pwC2, zero, 0.0, 0.0);
          delay(tau2 - gt1 - 2.0*GRADIENT_DELAY - 1.0e-4);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else    zgradpulse(icosel*gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwr);				       /* POWER_DELAY */
	  delay(1.0e-4 - POWER_DELAY);
	}
    else
	{
          delay(timeTN + tau2 - kappa - PRG_STOP_DELAY - pwHd - 2.0e-6);
          xmtroff();
	  obsprgoff();					    /* PRG_STOP_DELAY */
	  rgpulse(pwHd,three,2.0e-6,0.0);
	  txphase(t4);
    	  delay(kappa-tau2-pwC2-gt1-2.0*GRADIENT_DELAY-1.0e-4);
          if (mag_flg[A]=='y')    magradpulse(icosel*gzcal*gzlvl1, gt1);
          else    zgradpulse(icosel*gzlvl1, gt1);   	/* 2.0*GRADIENT_DELAY */
	  obspower(tpwr);				       /* POWER_DELAY */
	  delay(1.0e-4 - POWER_DELAY);                    /* WFG_START_DELAY */
          decrgpulse(pwC2, zero, 0.0, 0.0);
          delay(tau2);
	}
}
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
	zgradpulse(gzlvl6, gt5);
	delay(lambda - 1.3*pwN - gt5);

	sim3pulse(2.0*pw, 0.0, 2.0*pwN, zero, zero, zero, 0.0, 0.0);

	dec2phase(t10);
	zgradpulse(gzlvl6, gt5);
	if (TROSY[A]=='y')   delay(lambda - 1.6*pwN - gt5);
	else   delay(lambda - 0.65*pwN - gt5);

	if (TROSY[A]=='y')   dec2rgpulse(pwN, t10, 0.0, 0.0); 
	else    	     rgpulse(pw, zero, 0.0, 0.0); 

	delay((gt1/10.0) + gstab - 0.5*pw + 2.0*GRADIENT_DELAY + POWER_DELAY);

	rgpulse(2.0*pw, zero, 0.0, rof1);
	dec2power(dpwr2);				       /* POWER_DELAY */
        if (mag_flg[A] == 'y')    magradpulse(gzcal*gzlvl2, gt1/10.0);
        else   zgradpulse(gzlvl2, gt1/10.0);            /* 2.0*GRADIENT_DELAY */

statusdelay(C,gstab- rof1);
   if (dm3[B]=='y') lk_sample();

	setreceiver(t12);
}		 