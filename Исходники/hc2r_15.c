static void hc2r_15(const R *ri, const R *ii, R *O, stride ris, stride iis, stride os, INT v, INT ivs, INT ovs)
{
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DK(KP1_902113032, +1.902113032590307144232878666758764286811397268);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     DK(KP1_118033988, +1.118033988749894848204586834365638117720309180);
     DK(KP618033988, +0.618033988749894848204586834365638117720309180);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP1_732050807, +1.732050807568877293527446341505872366942805254);
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     INT i;
     for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, O = O + ovs, MAKE_VOLATILE_STRIDE(ris), MAKE_VOLATILE_STRIDE(iis), MAKE_VOLATILE_STRIDE(os)) {
	  E TL, Tz, TM, TK;
	  {
	       E T3, Th, Tt, TD, TI, TH, TY, TC, TZ, Tu, Tm, Tv, Tr, Te, TW;
	       E Tg, T1, T2, T12, T10, TV;
	       Tg = ii[WS(iis, 5)];
	       T1 = ri[0];
	       T2 = ri[WS(ris, 5)];
	       {
		    E T4, TA, T9, TF, T7, Tj, Tc, Tk, TG, Tq, Tf, Tl, TB;
		    T4 = ri[WS(ris, 3)];
		    TA = ii[WS(iis, 3)];
		    T9 = ri[WS(ris, 6)];
		    Tf = T1 - T2;
		    T3 = FMA(KP2_000000000, T2, T1);
		    TF = ii[WS(iis, 6)];
		    {
			 E Ta, Tb, T5, T6, To, Tp;
			 T5 = ri[WS(ris, 7)];
			 T6 = ri[WS(ris, 2)];
			 Th = FMA(KP1_732050807, Tg, Tf);
			 Tt = FNMS(KP1_732050807, Tg, Tf);
			 Ta = ri[WS(ris, 4)];
			 TD = T5 - T6;
			 T7 = T5 + T6;
			 Tb = ri[WS(ris, 1)];
			 To = ii[WS(iis, 4)];
			 Tp = ii[WS(iis, 1)];
			 Tj = ii[WS(iis, 7)];
			 Tc = Ta + Tb;
			 TI = Ta - Tb;
			 Tk = ii[WS(iis, 2)];
			 TG = Tp - To;
			 Tq = To + Tp;
		    }
		    Tl = Tj - Tk;
		    TB = Tj + Tk;
		    TH = FNMS(KP500000000, TG, TF);
		    TY = TG + TF;
		    TC = FMA(KP500000000, TB, TA);
		    TZ = TA - TB;
		    {
			 E Ti, T8, Td, Tn;
			 Ti = FNMS(KP2_000000000, T4, T7);
			 T8 = T4 + T7;
			 Td = T9 + Tc;
			 Tn = FNMS(KP2_000000000, T9, Tc);
			 Tu = FNMS(KP1_732050807, Tl, Ti);
			 Tm = FMA(KP1_732050807, Tl, Ti);
			 Tv = FNMS(KP1_732050807, Tq, Tn);
			 Tr = FMA(KP1_732050807, Tq, Tn);
			 Te = T8 + Td;
			 TW = T8 - Td;
		    }
	       }
	       T12 = FMA(KP618033988, TY, TZ);
	       T10 = FNMS(KP618033988, TZ, TY);
	       TV = FNMS(KP500000000, Te, T3);
	       O[0] = FMA(KP2_000000000, Te, T3);
	       {
		    E TJ, TE, TT, TP, TU, TS, Ty, Tw, Tx;
		    {
			 E TO, Ts, TQ, TN, TR, T11, TX;
			 TO = Tr - Tm;
			 Ts = Tm + Tr;
			 T11 = FMA(KP1_118033988, TW, TV);
			 TX = FNMS(KP1_118033988, TW, TV);
			 TQ = FNMS(KP866025403, TI, TH);
			 TJ = FMA(KP866025403, TI, TH);
			 TN = FMA(KP250000000, Ts, Th);
			 O[WS(os, 6)] = FNMS(KP1_902113032, T12, T11);
			 O[WS(os, 9)] = FMA(KP1_902113032, T12, T11);
			 O[WS(os, 12)] = FMA(KP1_902113032, T10, TX);
			 O[WS(os, 3)] = FNMS(KP1_902113032, T10, TX);
			 TR = FNMS(KP866025403, TD, TC);
			 TE = FMA(KP866025403, TD, TC);
			 O[WS(os, 5)] = Th - Ts;
			 TT = FMA(KP559016994, TO, TN);
			 TP = FNMS(KP559016994, TO, TN);
			 TU = FMA(KP618033988, TQ, TR);
			 TS = FNMS(KP618033988, TR, TQ);
		    }
		    Ty = Tv - Tu;
		    Tw = Tu + Tv;
		    O[WS(os, 14)] = FMA(KP1_902113032, TU, TT);
		    O[WS(os, 11)] = FNMS(KP1_902113032, TU, TT);
		    O[WS(os, 2)] = FMA(KP1_902113032, TS, TP);
		    O[WS(os, 8)] = FNMS(KP1_902113032, TS, TP);
		    Tx = FMA(KP250000000, Tw, Tt);
		    O[WS(os, 10)] = Tt - Tw;
		    TL = FNMS(KP559016994, Ty, Tx);
		    Tz = FMA(KP559016994, Ty, Tx);
		    TM = FNMS(KP618033988, TE, TJ);
		    TK = FMA(KP618033988, TJ, TE);
	       }
	  }
	  O[WS(os, 7)] = FMA(KP1_902113032, TM, TL);
	  O[WS(os, 13)] = FNMS(KP1_902113032, TM, TL);
	  O[WS(os, 4)] = FMA(KP1_902113032, TK, Tz);
	  O[WS(os, 1)] = FNMS(KP1_902113032, TK, Tz);
     }
}