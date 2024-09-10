static void hb_5(R *cr, R *ci, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP618033988, +0.618033988749894848204586834365638117720309180);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 8); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 8, MAKE_VOLATILE_STRIDE(rs)) {
	  E TQ, TP, TT, TR, TS, TU;
	  {
	       E T1, Tn, TM, Tw, Tb, T8, To, Tf, Ta, Tg, Th;
	       {
		    E T2, T3, T5, T6, T4, Tu;
		    T1 = cr[0];
		    T2 = cr[WS(rs, 1)];
		    T3 = ci[0];
		    T5 = cr[WS(rs, 2)];
		    T6 = ci[WS(rs, 1)];
		    Tn = ci[WS(rs, 4)];
		    T4 = T2 + T3;
		    Tu = T2 - T3;
		    {
			 E T7, Tv, Td, Te;
			 T7 = T5 + T6;
			 Tv = T5 - T6;
			 Td = ci[WS(rs, 3)];
			 Te = cr[WS(rs, 4)];
			 TM = FNMS(KP618033988, Tu, Tv);
			 Tw = FMA(KP618033988, Tv, Tu);
			 Tb = T4 - T7;
			 T8 = T4 + T7;
			 To = Td - Te;
			 Tf = Td + Te;
			 Ta = FNMS(KP250000000, T8, T1);
			 Tg = ci[WS(rs, 2)];
			 Th = cr[WS(rs, 3)];
		    }
	       }
	       cr[0] = T1 + T8;
	       {
		    E TG, T9, Tm, Tz, TH, TC, TA, Tk, Tt, TL, Tc, Ti, Tp, TI;
		    TG = FNMS(KP559016994, Tb, Ta);
		    Tc = FMA(KP559016994, Tb, Ta);
		    T9 = W[0];
		    Ti = Tg + Th;
		    Tp = Tg - Th;
		    Tm = W[1];
		    {
			 E Ts, Tj, Tr, Tq;
			 Tz = W[6];
			 Ts = To - Tp;
			 Tq = To + Tp;
			 Tj = FMA(KP618033988, Ti, Tf);
			 TH = FNMS(KP618033988, Tf, Ti);
			 ci[0] = Tn + Tq;
			 Tr = FNMS(KP250000000, Tq, Tn);
			 TC = W[7];
			 TA = FMA(KP951056516, Tj, Tc);
			 Tk = FNMS(KP951056516, Tj, Tc);
			 Tt = FMA(KP559016994, Ts, Tr);
			 TL = FNMS(KP559016994, Ts, Tr);
		    }
		    {
			 E TE, TB, Ty, Tl, TD, Tx;
			 TE = TC * TA;
			 TB = Tz * TA;
			 Ty = Tm * Tk;
			 Tl = T9 * Tk;
			 TD = FNMS(KP951056516, Tw, Tt);
			 Tx = FMA(KP951056516, Tw, Tt);
			 TI = FMA(KP951056516, TH, TG);
			 TQ = FNMS(KP951056516, TH, TG);
			 ci[WS(rs, 4)] = FMA(Tz, TD, TE);
			 cr[WS(rs, 4)] = FNMS(TC, TD, TB);
			 ci[WS(rs, 1)] = FMA(T9, Tx, Ty);
			 cr[WS(rs, 1)] = FNMS(Tm, Tx, Tl);
		    }
		    {
			 E TF, TK, TN, TJ, TO;
			 TF = W[2];
			 TK = W[3];
			 TP = W[4];
			 TT = FMA(KP951056516, TM, TL);
			 TN = FNMS(KP951056516, TM, TL);
			 TJ = TF * TI;
			 TO = TK * TI;
			 TR = TP * TQ;
			 TS = W[5];
			 cr[WS(rs, 2)] = FNMS(TK, TN, TJ);
			 ci[WS(rs, 2)] = FMA(TF, TN, TO);
		    }
	       }
	  }
	  cr[WS(rs, 3)] = FNMS(TS, TT, TR);
	  TU = TS * TQ;
	  ci[WS(rs, 3)] = FMA(TP, TT, TU);
     }
}