static void t1_8(float *ri, float *ii, const float *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT m;
     for (m = mb, W = W + (mb * 14); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 14, MAKE_VOLATILE_STRIDE(rs)) {
	  E T1g, T1f, T1e, Tm, T1q, T1o, T1p, TN, T1h, T1i;
	  {
	       E T1, T1m, T1l, T7, TS, Tk, TQ, Te, To, Tr, T17, TM, T12, Tu, TW;
	       E Tp, Tx, Tt, Tq, Tw;
	       {
		    E T3, T6, T2, T5;
		    T1 = ri[0];
		    T1m = ii[0];
		    T3 = ri[WS(rs, 4)];
		    T6 = ii[WS(rs, 4)];
		    T2 = W[6];
		    T5 = W[7];
		    {
			 E Ta, Td, T9, Tc;
			 {
			      E Tg, Tj, Ti, TR, Th, T1k, T4, Tf;
			      Tg = ri[WS(rs, 6)];
			      Tj = ii[WS(rs, 6)];
			      T1k = T2 * T6;
			      T4 = T2 * T3;
			      Tf = W[10];
			      Ti = W[11];
			      T1l = FNMS(T5, T3, T1k);
			      T7 = FMA(T5, T6, T4);
			      TR = Tf * Tj;
			      Th = Tf * Tg;
			      Ta = ri[WS(rs, 2)];
			      Td = ii[WS(rs, 2)];
			      TS = FNMS(Ti, Tg, TR);
			      Tk = FMA(Ti, Tj, Th);
			      T9 = W[2];
			      Tc = W[3];
			 }
			 {
			      E TB, TE, TH, T13, TC, TK, TG, TD, TJ, TP, Tb, TA, Tn;
			      TB = ri[WS(rs, 7)];
			      TE = ii[WS(rs, 7)];
			      TP = T9 * Td;
			      Tb = T9 * Ta;
			      TA = W[12];
			      TH = ri[WS(rs, 3)];
			      TQ = FNMS(Tc, Ta, TP);
			      Te = FMA(Tc, Td, Tb);
			      T13 = TA * TE;
			      TC = TA * TB;
			      TK = ii[WS(rs, 3)];
			      TG = W[4];
			      TD = W[13];
			      TJ = W[5];
			      {
				   E T14, TF, T16, TL, T15, TI;
				   To = ri[WS(rs, 1)];
				   T15 = TG * TK;
				   TI = TG * TH;
				   T14 = FNMS(TD, TB, T13);
				   TF = FMA(TD, TE, TC);
				   T16 = FNMS(TJ, TH, T15);
				   TL = FMA(TJ, TK, TI);
				   Tr = ii[WS(rs, 1)];
				   Tn = W[0];
				   T17 = T14 - T16;
				   T1g = T14 + T16;
				   TM = TF + TL;
				   T12 = TF - TL;
			      }
			      Tu = ri[WS(rs, 5)];
			      TW = Tn * Tr;
			      Tp = Tn * To;
			      Tx = ii[WS(rs, 5)];
			      Tt = W[8];
			      Tq = W[1];
			      Tw = W[9];
			 }
		    }
	       }
	       {
		    E T8, T1j, T1n, Tz, T1a, TU, Tl, T1b, T1c, T1v, T1t, T1w, T19, T1u, T1d;
		    {
			 E T1r, T10, TV, T1s, T11, T18;
			 {
			      E TO, TX, Ts, TZ, Ty, TT, TY, Tv;
			      T8 = T1 + T7;
			      TO = T1 - T7;
			      TY = Tt * Tx;
			      Tv = Tt * Tu;
			      TX = FNMS(Tq, To, TW);
			      Ts = FMA(Tq, Tr, Tp);
			      TZ = FNMS(Tw, Tu, TY);
			      Ty = FMA(Tw, Tx, Tv);
			      TT = TQ - TS;
			      T1j = TQ + TS;
			      T1n = T1l + T1m;
			      T1r = T1m - T1l;
			      T10 = TX - TZ;
			      T1f = TX + TZ;
			      Tz = Ts + Ty;
			      TV = Ts - Ty;
			      T1a = TO - TT;
			      TU = TO + TT;
			      T1s = Te - Tk;
			      Tl = Te + Tk;
			 }
			 T1b = T10 - TV;
			 T11 = TV + T10;
			 T18 = T12 - T17;
			 T1c = T12 + T17;
			 T1v = T1s + T1r;
			 T1t = T1r - T1s;
			 T1w = T18 - T11;
			 T19 = T11 + T18;
		    }
		    ii[WS(rs, 3)] = FMA(KP707106781, T1w, T1v);
		    ii[WS(rs, 7)] = FNMS(KP707106781, T1w, T1v);
		    ri[WS(rs, 1)] = FMA(KP707106781, T19, TU);
		    ri[WS(rs, 5)] = FNMS(KP707106781, T19, TU);
		    T1u = T1b + T1c;
		    T1d = T1b - T1c;
		    ii[WS(rs, 1)] = FMA(KP707106781, T1u, T1t);
		    ii[WS(rs, 5)] = FNMS(KP707106781, T1u, T1t);
		    ri[WS(rs, 3)] = FMA(KP707106781, T1d, T1a);
		    ri[WS(rs, 7)] = FNMS(KP707106781, T1d, T1a);
		    T1e = T8 - Tl;
		    Tm = T8 + Tl;
		    T1q = T1n - T1j;
		    T1o = T1j + T1n;
		    T1p = TM - Tz;
		    TN = Tz + TM;
	       }
	  }
	  ii[WS(rs, 2)] = T1p + T1q;
	  ii[WS(rs, 6)] = T1q - T1p;
	  ri[0] = Tm + TN;
	  ri[WS(rs, 4)] = Tm - TN;
	  T1h = T1f - T1g;
	  T1i = T1f + T1g;
	  ii[0] = T1i + T1o;
	  ii[WS(rs, 4)] = T1o - T1i;
	  ri[WS(rs, 2)] = T1e + T1h;
	  ri[WS(rs, 6)] = T1e - T1h;
     }
}