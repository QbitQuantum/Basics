static void q1_3(float *rio, float *iio, const float *W, stride rs, stride vs, INT mb, INT me, INT ms)
{
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     INT m;
     for (m = mb, W = W + (mb * 4); m < me; m = m + 1, rio = rio + ms, iio = iio + ms, W = W + 4, MAKE_VOLATILE_STRIDE(rs), MAKE_VOLATILE_STRIDE(vs)) {
	  E T1, T4, T6, Tc, Td, Te, T9, Tf, Tl, To, Tq, Tw, Tx, Ty, Tt;
	  E Tz, TR, TS, TN, TT, TF, TI, TK, TQ;
	  {
	       E T2, T3, Tr, Ts;
	       T1 = rio[0];
	       T2 = rio[WS(rs, 1)];
	       T3 = rio[WS(rs, 2)];
	       T4 = T2 + T3;
	       T6 = FNMS(KP500000000, T4, T1);
	       Tc = KP866025403 * (T3 - T2);
	       {
		    E T7, T8, Tm, Tn;
		    Td = iio[0];
		    T7 = iio[WS(rs, 1)];
		    T8 = iio[WS(rs, 2)];
		    Te = T7 + T8;
		    T9 = KP866025403 * (T7 - T8);
		    Tf = FNMS(KP500000000, Te, Td);
		    Tl = rio[WS(vs, 1)];
		    Tm = rio[WS(vs, 1) + WS(rs, 1)];
		    Tn = rio[WS(vs, 1) + WS(rs, 2)];
		    To = Tm + Tn;
		    Tq = FNMS(KP500000000, To, Tl);
		    Tw = KP866025403 * (Tn - Tm);
	       }
	       Tx = iio[WS(vs, 1)];
	       Tr = iio[WS(vs, 1) + WS(rs, 1)];
	       Ts = iio[WS(vs, 1) + WS(rs, 2)];
	       Ty = Tr + Ts;
	       Tt = KP866025403 * (Tr - Ts);
	       Tz = FNMS(KP500000000, Ty, Tx);
	       {
		    E TL, TM, TG, TH;
		    TR = iio[WS(vs, 2)];
		    TL = iio[WS(vs, 2) + WS(rs, 1)];
		    TM = iio[WS(vs, 2) + WS(rs, 2)];
		    TS = TL + TM;
		    TN = KP866025403 * (TL - TM);
		    TT = FNMS(KP500000000, TS, TR);
		    TF = rio[WS(vs, 2)];
		    TG = rio[WS(vs, 2) + WS(rs, 1)];
		    TH = rio[WS(vs, 2) + WS(rs, 2)];
		    TI = TG + TH;
		    TK = FNMS(KP500000000, TI, TF);
		    TQ = KP866025403 * (TH - TG);
	       }
	  }
	  rio[0] = T1 + T4;
	  iio[0] = Td + Te;
	  rio[WS(rs, 1)] = Tl + To;
	  iio[WS(rs, 1)] = Tx + Ty;
	  iio[WS(rs, 2)] = TR + TS;
	  rio[WS(rs, 2)] = TF + TI;
	  {
	       E Ta, Tg, T5, Tb;
	       Ta = T6 + T9;
	       Tg = Tc + Tf;
	       T5 = W[0];
	       Tb = W[1];
	       rio[WS(vs, 1)] = FMA(T5, Ta, Tb * Tg);
	       iio[WS(vs, 1)] = FNMS(Tb, Ta, T5 * Tg);
	  }
	  {
	       E TW, TY, TV, TX;
	       TW = TK - TN;
	       TY = TT - TQ;
	       TV = W[2];
	       TX = W[3];
	       rio[WS(vs, 2) + WS(rs, 2)] = FMA(TV, TW, TX * TY);
	       iio[WS(vs, 2) + WS(rs, 2)] = FNMS(TX, TW, TV * TY);
	  }
	  {
	       E TC, TE, TB, TD;
	       TC = Tq - Tt;
	       TE = Tz - Tw;
	       TB = W[2];
	       TD = W[3];
	       rio[WS(vs, 2) + WS(rs, 1)] = FMA(TB, TC, TD * TE);
	       iio[WS(vs, 2) + WS(rs, 1)] = FNMS(TD, TC, TB * TE);
	  }
	  {
	       E Tu, TA, Tp, Tv;
	       Tu = Tq + Tt;
	       TA = Tw + Tz;
	       Tp = W[0];
	       Tv = W[1];
	       rio[WS(vs, 1) + WS(rs, 1)] = FMA(Tp, Tu, Tv * TA);
	       iio[WS(vs, 1) + WS(rs, 1)] = FNMS(Tv, Tu, Tp * TA);
	  }
	  {
	       E TO, TU, TJ, TP;
	       TO = TK + TN;
	       TU = TQ + TT;
	       TJ = W[0];
	       TP = W[1];
	       rio[WS(vs, 1) + WS(rs, 2)] = FMA(TJ, TO, TP * TU);
	       iio[WS(vs, 1) + WS(rs, 2)] = FNMS(TP, TO, TJ * TU);
	  }
	  {
	       E Ti, Tk, Th, Tj;
	       Ti = T6 - T9;
	       Tk = Tf - Tc;
	       Th = W[2];
	       Tj = W[3];
	       rio[WS(vs, 2)] = FMA(Th, Ti, Tj * Tk);
	       iio[WS(vs, 2)] = FNMS(Tj, Ti, Th * Tk);
	  }
     }
}