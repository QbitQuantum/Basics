pulsesequence()
{

/* DECLARE AND LOAD VARIABLES */

char        f1180[MAXSTR],   		      /* Flag to start t1 @ halfdwell */
            f2180[MAXSTR],    		      /* Flag to start t2 @ halfdwell */
            mag_flg[MAXSTR];      /* magic-angle coherence transfer gradients */
 
int         icosel,          			  /* used to get n and p type */
            t1_counter,  		        /* used for states tppi in t1 */
            t2_counter,  	 	        /* used for states tppi in t2 */
	    ni2 = getval("ni2");

double      tau1,         				         /*  t1 delay */
            tau2,        				         /*  t2 delay */
            timeTN = getval("timeTN"),     /* constant time for 15N evolution */
	    kappa = 5.4e-3,
	    lambda = 2.4e-3,
            
	pwClvl = getval("pwClvl"), 	        /* coarse power for C13 pulse */
        pwC = getval("pwC"),          /* C13 90 degree pulse length at pwClvl */
	rf0,            	  /* maximum fine power when using pwC pulses */

/* the following pulse lengths for SLP pulses are automatically calculated    */
/* by the macro "biocal".  SLP pulse shapes, "offC3" etc are called       */
/* directly from your shapelib.                    			      */
   pwC3 = getval("pwC3"),  /*180 degree pulse at Ca(56ppm) null at CO(174ppm) */
   pwC3a,                      /* pwC3a=pwC3, but not set to zero when pwC3=0 */
   phshift3,             /* phase shift induced on CO by pwC3 ("offC3") pulse */
   pwZ,					   /* the largest of pwC3 and 2.0*pwN */
   pwC6,                      /* 90 degree selective sinc pulse on CO(174ppm) */
   pwC8,                     /* 180 degree selective sinc pulse on CO(174ppm) */
   rf3,	                           /* fine power for the pwC3 ("offC3") pulse */
   rf6,	                           /* fine power for the pwC6 ("offC6") pulse */
   rf8,	                           /* fine power for the pwC8 ("offC8") pulse */
   bw, ofs, ppm,  /* bandwidth, offset, ppm - temporary Pbox parameters */

   compH = getval("compH"),       /* adjustment for C13 amplifier compression */
   compC = getval("compC"),       /* adjustment for C13 amplifier compression */

   	pwHs = getval("pwHs"),	        /* H1 90 degree pulse length at tpwrs */
   	tpwrsf = getval("tpwrsf"),      /* fine power for pwHs pulse          */
   	tpwrs,	  	              /* power for the pwHs ("H2Osinc") pulse */

   	pwHd,	    		        /* H1 90 degree pulse length at tpwrd */
   	tpwrd,	  	                   /* rf for WALTZ decoupling */

        waltzB1 = getval("waltzB1"),  /* waltz16 field strength (in Hz)     */
	pwNlvl = getval("pwNlvl"),	              /* power for N15 pulses */
        pwN = getval("pwN"),          /* N15 90 degree pulse length at pwNlvl */

	sw1 = getval("sw1"),
	sw2 = getval("sw2"),

	gt1 = getval("gt1"),  		       /* coherence pathway gradients */
        gzcal  = getval("gzcal"),            /* g/cm to DAC conversion factor */
	gzlvl1 = getval("gzlvl1"),
	gzlvl2 = getval("gzlvl2"),

	gt0 = getval("gt0"),				   /* other gradients */
	gt3 = getval("gt3"),
	gt4 = getval("gt4"),
	gt5 = getval("gt5"),
	gzlvl0 = getval("gzlvl0"),
	gzlvl3 = getval("gzlvl3"),
	gzlvl4 = getval("gzlvl4"),
	gzlvl5 = getval("gzlvl5"),
	gzlvl6 = getval("gzlvl6");

    getstr("f1180",f1180);
    getstr("f2180",f2180);
    getstr("mag_flg",mag_flg);



/*   LOAD PHASE TABLE    */

	settable(t3,2,phi3);
	settable(t4,1,phx);
	settable(t5,4,phi5);
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


      setautocal();                      /* activate auto-calibration */   

      if (autocal[0] == 'n') 
      {
    /* offC3 - 180 degree pulse on Ca, null at CO 118ppm away */
          pwC3a = getval("pwC3a");    
          rf3 = (compC*4095.0*pwC*2.0)/pwC3a;
	  rf3 = (int) (rf3 + 0.5);  
	
    /* 90 degree one-lobe sinc pulse on CO, null at Ca 118ppm away */	
          pwC6 = getval("pwC6");    
	  rf6 = (compC*4095.0*pwC*1.69)/pwC6;	/* needs 1.69 times more     */
	  rf6 = (int) (rf6 + 0.5);		/* power than a square pulse */

    /* 180 degree one-lobe sinc pulse on CO, null at Ca 118ppm away */
          pwC8 = getval("pwC8");
	  rf8 = (compC*4095.0*pwC*2.0*1.65)/pwC8;  /* needs 1.65 times more     */
	  rf8 = (int) (rf8 + 0.5);		   /* power than a square pulse */

    /* selective H20 one-lobe sinc pulse */
          tpwrs = tpwr - 20.0*log10(pwHs/(compH*pw*1.69)); /* needs 1.69 times more */
          tpwrs = (int) (tpwrs);                       /* power than a square pulse */

    /* power level and pulse time for WALTZ 1H decoupling */
	  pwHd = 1/(4.0 * waltzB1) ;                              /* 7.5 kHz rf   */
	  tpwrd = tpwr - 20.0*log10(pwHd/(compH*pw));
	  tpwrd = (int) (tpwrd + 0.5);
      }
      else      /* if autocal = 'y'(yes), 'q'(quiet), 'r'(read) or 's'(semi) */
      {
        if(FIRST_FID)                                         /* make shapes */
        {
          ppm = getval("dfrq"); 
          bw = 118.0*ppm; ofs = -bw; 
          offC3 = pbox_make("offC3", "square180n", bw, ofs, compC*pwC, pwClvl);
          offC6 = pbox_make("offC6", "sinc90n", bw, 0.0, compC*pwC, pwClvl);
          offC8 = pbox_make("offC8", "sinc180n", bw, 0.0, compC*pwC, pwClvl);
          H2Osinc = pbox_Rsh("H2Osinc", "sinc90", pwHs, 0.0, compH*pw, tpwr);
          bw = 2.8*7500.0;
          wz16 = pbox_Dcal("WALTZ16", 2.8*waltzB1, 0.0, compH*pw, tpwr);

          ofs_check(H1ofs, C13ofs, N15ofs, H2ofs);
        }
        pwC3a = offC3.pw; rf3 = offC3.pwrf;             /* set up parameters */
        pwC6 = offC6.pw; rf6 = offC6.pwrf; 
        pwC8 = offC8.pw; rf8 = offC8.pwrf;
        pwHs = H2Osinc.pw; tpwrs = H2Osinc.pwr-1.0;  /* 1dB correction applied */
        tpwrd = wz16.pwr; pwHd = 1.0/wz16.dmf;  
      }

      if (tpwrsf < 4095.0) tpwrs = tpwrs + 6.0;

    /* the pwC3 pulse at the middle of t1  */
       if (pwC3a > 2.0*pwN) pwZ = pwC3a; else pwZ = 2.0*pwN;
       phshift3=0.0;
       if(pwC3 > 0) phshift3 = 48.0;

/* CHECK VALIDITY OF PARAMETER RANGES */

    if ( 0.5*ni2*1/(sw2) > timeTN - pwC3a - WFG3_START_DELAY)
       { printf(" ni2 is too big. Make ni2 equal to %d or less.\n", 
  	 ((int)((timeTN - WFG3_START_DELAY)*2.0*sw2))); psg_abort(1);}

    if ( dm[A] == 'y' || dm[B] == 'y' || dm[C] == 'y' )
       { printf("incorrect dec1 decoupler flags! Should be 'nnn' "); psg_abort(1);}

    if ( dm2[A] == 'y' || dm2[B] == 'y' )
       { printf("incorrect dec2 decoupler flags! Should be 'nny' "); psg_abort(1);}

    if ( dpwr2 > 50 )
       { printf("dpwr2 too large! recheck value  "); psg_abort(1);}

    if ( pw > 50.0e-6 )
       { printf(" pw too long ! recheck value "); psg_abort(1);} 
  
    if ( (pwN > 100.0e-6) && (ni>1 || ni2>1))
       { printf(" pwN too long! recheck value "); psg_abort(1);} 
 

/* PHASES AND INCREMENTED TIMES */

/*  Phase incrementation for hypercomplex 2D data, States-Haberkorn element */

    if (phase1 == 2)   tsadd(t3,1,4);  
    {  
       if (phase2 == 2)  {tsadd(t10,2,4); icosel = +1;}
       else 			       icosel = -1;    
    }


/*  Set up f1180  */
   
    tau1 = d2;
    if(f1180[A] == 'y') 
	{ tau1 += ( 1.0 / (2.0*sw1) ); if(tau1 < 0.2e-6) tau1 = 0.0; }
    tau1 = tau1/2.0;


/*  Set up f2180  */

    tau2 = d3;
    if(f2180[A] == 'y') 
	{ tau2 += ( 1.0 / (2.0*sw2) ); if(tau2 < 0.2e-6) tau2 = 0.0; }
    tau2 = tau2/2.0;


/* Calculate modifications to phases for States-TPPI acquisition          */

   if( ix == 1) d2_init = d2;
   t1_counter = (int) ( (d2-d2_init)*sw1 + 0.5 );
   if(t1_counter % 2) 
	{ tsadd(t3,2,4); tsadd(t12,2,4); }

   if( ix == 1) d3_init = d3;
   t2_counter = (int) ( (d3-d3_init)*sw2 + 0.5 );
   if(t2_counter % 2) 
	{ tsadd(t8,2,4); tsadd(t12,2,4); }



/* BEGIN PULSE SEQUENCE */

status(A);
    delay(d1);
    rcvroff();
    obspower(tpwr);
    decpower(pwClvl);
 	dec2power(pwNlvl);
	decpwrf(rf0);
	obsoffset(tof);
	txphase(zero);
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

    if (tpwrsf < 4095.0) obspwrf(tpwrsf);
    obspower(tpwrs);
    txphase(two);
    shaped_pulse("H2Osinc", pwHs, two, 2.0e-6, 0.0);
    obspower(tpwrd);
    if (tpwrsf < 4095.0) obspwrf(4095.0);
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
    decpwrf(rf8);
    delay(timeTN - kappa - WFG3_START_DELAY);
   
							  /* WFG3_START_DELAY */
	sim3shaped_pulse("", "offC8", "", 0.0, pwC8, 2.0*pwN, zero, zero, zero, 
								     0.0, 0.0);
	decphase(t3);
	decpwrf(rf6);
	delay(timeTN);

	dec2rgpulse(pwN, zero, 0.0, 0.0);
   xmtroff();
   obsprgoff();
   rgpulse(pwHd,three,2.0e-6,0.0);
   zgradpulse(gzlvl3, gt3);
   delay(2.0e-4);
    rgpulse(pwHd,one,0.0,0.0);
    txphase(zero);
    delay(2.0e-6);
    obsprgon("waltz16", pwHd, 90.0);	          /* PRG_START_DELAY */
    xmtron();
/*   xxxxxxxxxxxxxxxxxxxxxx       13CO EVOLUTION        xxxxxxxxxxxxxxxxxx    */

   decshaped_pulse("offC6", pwC6, t3, 1.0e-6, 0.0);
   decphase(zero);


   if((tau1 - 2.0*pwC6/3.14 - WFG3_START_DELAY - 0.5*pwZ - POWER_DELAY) > SAPS_DELAY)
   {
      decpwrf(rf3);
      delay(tau1 - 2.0*pwC6/3.14 - WFG3_START_DELAY - 0.5*pwZ - POWER_DELAY);
      sim3shaped_pulse("", "offC3", "", 0.0, pwC3a, 2.0*pwN, zero, zero, zero,0.0,0.0);
      initval(phshift3, v3);
      decstepsize(1.0);
      dcplrphase(v3);  				        /* SAPS_DELAY */
      decpwrf(rf6);
      decphase(t5);
      delay(tau1 - 2.0*pwC6/3.14 - SAPS_DELAY - 0.5*pwZ- WFG3_START_DELAY - POWER_DELAY);
   }
   else
   {
       decpwrf(rf8);
       decshaped_pulse("offC8", pwC8, zero, 2.0e-6, 0.0);
       decpwrf(rf6);
       decphase(t5);
       delay(2.0e-6);
   }

   decshaped_pulse("offC6", pwC6, t5, 0.5e-6, 1.0e-6);
   xmtroff();
   obsprgoff();
   rgpulse(pwHd,three,2.0e-6,0.0);

/*  xxxxxxxxxxxxxxxxxx    N15 EVOLUTION    xxxxxxxxxxxxxxxxxxxxx  */

   dec2phase(t8);
   zgradpulse(gzlvl4, gt4);
   dcplrphase(zero);
   obspower(tpwr);
   delay(2.0e-4);

   dec2rgpulse(pwN, t8, 0.0, 0.0);
   decpwrf(rf3);
   decphase(zero);
   delay((timeTN - tau2 - pwC3a)/2.0);
   decshaped_pulse("offC3", pwC3a, zero, 0.0, 0.0);

   dec2phase(t9);
   decpwrf(rf8);
   delay((timeTN - tau2 - pwC3a)/2.0);
							 /* WFG3_START_DELAY  */
/*
   sim3shaped_pulse("", "offC8", "", 2.0*pw, pwC8, 2.0*pwN, zero, zero, t9, 
								   0.0, 0.0);
*/
   sim3shaped_pulse("", "offC8", "",0.0,pwC8,2.0*pwN,zero,zero,t9,0.0,0.0);
   dec2phase(t10);
   decpwrf(rf3);

   delay((timeTN + tau2 - pwC3a)/2.0);
   decshaped_pulse("offC3", pwC3a, zero, 0.0, 0.0);
   delay((timeTN + tau2 - pwC3a)/2.0 - 2.75e-3 - 2.0*pw);
   rgpulse(2.0*pw,zero, 0.0, 0.0);
   if (mag_flg[A]=='y')   
   {
        magradpulse(gzcal*gzlvl1, gt1);
   }
   else
   {
        zgradpulse(gzlvl1, gt1);  
        delay(4.0*GRADIENT_DELAY);
   }
   txphase(t4);
   delay(2.75e-3 - gt1 - 6.0*GRADIENT_DELAY);     

/*  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx  */
   sim3pulse(pw, 0.0, pwN, t4, zero, t10, 0.0, 0.0);

   txphase(zero);
   dec2phase(zero);
   zgradpulse(gzlvl5, gt5);
   delay(lambda - 1.3*pwN - gt5);

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

   zgradpulse(gzlvl6, gt5);
   delay(lambda - 0.65*pwN - gt5);

   rgpulse(pw, zero, 0.0, 0.0); 

   delay((gt1/10.0) + 1.0e-4 - 0.5*pw + 2.0*GRADIENT_DELAY + POWER_DELAY);

   rgpulse(2.0*pw, zero, 0.0,0.0);
   dec2power(dpwr2);				       /* POWER_DELAY */
   if (mag_flg[A] == 'y')    magradpulse(icosel*gzcal*gzlvl2, gt1/10.0);
   else   zgradpulse(icosel*gzlvl2, gt1/10.0);            /* 2.0*GRADIENT_DELAY */
   rcvron();
statusdelay(C,1.0e-4);

	setreceiver(t12);
}		 