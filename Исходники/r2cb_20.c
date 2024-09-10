static void r2cb_20(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP1_902113032, +1.902113032590307144232878666758764286811397268);
     DK(KP1_118033988, +1.118033988749894848204586834365638117720309180);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP618033988, +0.618033988749894848204586834365638117720309180);
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     INT i;
     for (i = v; i > 0; i = i - 1, R0 = R0 + ovs, R1 = R1 + ovs, Cr = Cr + ivs, Ci = Ci + ivs, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(csr), MAKE_VOLATILE_STRIDE(csi)) {
	  E TY, T1o, T1m, T14, T12, TX, T1n, T1j, TZ, T13;
	  {
	       E Tr, TD, Tl, T5, T1a, T1l, T1d, T1k, TT, T10, TO, T11, TE, TF, Tk;
	       E TI, TC, T1i, To, TG, T16;
	       {
		    E T4, Tq, T1, T2;
		    T4 = Cr[WS(csr, 5)];
		    Tq = Ci[WS(csi, 5)];
		    T1 = Cr[0];
		    T2 = Cr[WS(csr, 10)];
		    {
			 E Ts, T8, T19, TR, T18, Tb, TS, Tv, Tx, Tf, Ty, T1c, TM, T1b, Ti;
			 E Tz, Tt, Tu, TN, TA;
			 {
			      E TP, TQ, T9, Ta;
			      {
				   E T6, T7, Tp, T3;
				   T6 = Cr[WS(csr, 4)];
				   T7 = Cr[WS(csr, 6)];
				   TP = Ci[WS(csi, 4)];
				   Tp = T1 - T2;
				   T3 = T1 + T2;
				   Ts = T6 - T7;
				   T8 = T6 + T7;
				   Tr = FMA(KP2_000000000, Tq, Tp);
				   TD = FNMS(KP2_000000000, Tq, Tp);
				   Tl = FMA(KP2_000000000, T4, T3);
				   T5 = FNMS(KP2_000000000, T4, T3);
				   TQ = Ci[WS(csi, 6)];
			      }
			      T9 = Cr[WS(csr, 9)];
			      Ta = Cr[WS(csr, 1)];
			      Tt = Ci[WS(csi, 9)];
			      T19 = TP + TQ;
			      TR = TP - TQ;
			      T18 = T9 - Ta;
			      Tb = T9 + Ta;
			      Tu = Ci[WS(csi, 1)];
			 }
			 {
			      E TK, TL, Td, Te, Tg, Th;
			      Td = Cr[WS(csr, 8)];
			      Te = Cr[WS(csr, 2)];
			      TK = Ci[WS(csi, 8)];
			      TS = Tt - Tu;
			      Tv = Tt + Tu;
			      Tx = Td - Te;
			      Tf = Td + Te;
			      TL = Ci[WS(csi, 2)];
			      Tg = Cr[WS(csr, 7)];
			      Th = Cr[WS(csr, 3)];
			      Ty = Ci[WS(csi, 7)];
			      T1c = TK + TL;
			      TM = TK - TL;
			      T1b = Tg - Th;
			      Ti = Tg + Th;
			      Tz = Ci[WS(csi, 3)];
			 }
			 T1a = T18 + T19;
			 T1l = T19 - T18;
			 T1d = T1b + T1c;
			 T1k = T1c - T1b;
			 TT = TR - TS;
			 T10 = TS + TR;
			 TN = Tz - Ty;
			 TA = Ty + Tz;
			 TO = TM - TN;
			 T11 = TN + TM;
			 {
			      E Tm, Tc, Tj, Tn, Tw, TB;
			      Tm = T8 + Tb;
			      Tc = T8 - Tb;
			      Tj = Tf - Ti;
			      Tn = Tf + Ti;
			      TE = Ts - Tv;
			      Tw = Ts + Tv;
			      TB = Tx - TA;
			      TF = Tx + TA;
			      Tk = Tc + Tj;
			      TI = Tc - Tj;
			      TC = Tw + TB;
			      T1i = Tw - TB;
			      TY = Tm - Tn;
			      To = Tm + Tn;
			 }
		    }
	       }
	       R0[WS(rs, 5)] = FMA(KP2_000000000, Tk, T5);
	       R1[WS(rs, 7)] = FMA(KP2_000000000, TC, Tr);
	       TG = TE + TF;
	       T16 = TE - TF;
	       R0[0] = FMA(KP2_000000000, To, Tl);
	       {
		    E TU, TW, T1g, T1e, T15, TV, TJ, TH, T1h, T1f, T17;
		    TU = FNMS(KP618033988, TT, TO);
		    TW = FMA(KP618033988, TO, TT);
		    R1[WS(rs, 2)] = FMA(KP2_000000000, TG, TD);
		    TH = FNMS(KP500000000, Tk, T5);
		    T1g = FNMS(KP618033988, T1a, T1d);
		    T1e = FMA(KP618033988, T1d, T1a);
		    T15 = FNMS(KP500000000, TG, TD);
		    TV = FMA(KP1_118033988, TI, TH);
		    TJ = FNMS(KP1_118033988, TI, TH);
		    T1o = FMA(KP618033988, T1k, T1l);
		    T1m = FNMS(KP618033988, T1l, T1k);
		    R0[WS(rs, 3)] = FNMS(KP1_902113032, TW, TV);
		    R0[WS(rs, 7)] = FMA(KP1_902113032, TW, TV);
		    R0[WS(rs, 1)] = FMA(KP1_902113032, TU, TJ);
		    R0[WS(rs, 9)] = FNMS(KP1_902113032, TU, TJ);
		    T1f = FNMS(KP1_118033988, T16, T15);
		    T17 = FMA(KP1_118033988, T16, T15);
		    T1h = FNMS(KP500000000, TC, Tr);
		    R1[WS(rs, 6)] = FNMS(KP1_902113032, T1g, T1f);
		    R1[WS(rs, 8)] = FMA(KP1_902113032, T1g, T1f);
		    R1[WS(rs, 4)] = FMA(KP1_902113032, T1e, T17);
		    R1[0] = FNMS(KP1_902113032, T1e, T17);
		    T14 = FNMS(KP618033988, T10, T11);
		    T12 = FMA(KP618033988, T11, T10);
		    TX = FNMS(KP500000000, To, Tl);
		    T1n = FMA(KP1_118033988, T1i, T1h);
		    T1j = FNMS(KP1_118033988, T1i, T1h);
	       }
	  }
	  R1[WS(rs, 5)] = FNMS(KP1_902113032, T1o, T1n);
	  R1[WS(rs, 9)] = FMA(KP1_902113032, T1o, T1n);
	  R1[WS(rs, 3)] = FMA(KP1_902113032, T1m, T1j);
	  R1[WS(rs, 1)] = FNMS(KP1_902113032, T1m, T1j);
	  TZ = FMA(KP1_118033988, TY, TX);
	  T13 = FNMS(KP1_118033988, TY, TX);
	  R0[WS(rs, 4)] = FNMS(KP1_902113032, T14, T13);
	  R0[WS(rs, 6)] = FMA(KP1_902113032, T14, T13);
	  R0[WS(rs, 2)] = FMA(KP1_902113032, T12, TZ);
	  R0[WS(rs, 8)] = FNMS(KP1_902113032, T12, TZ);
     }
}