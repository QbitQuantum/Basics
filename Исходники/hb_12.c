static void hb_12(R *cr, R *ci, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     {
	  INT m;
	  for (m = mb, W = W + ((mb - 1) * 22); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 22, MAKE_VOLATILE_STRIDE(24, rs)) {
	       E T5, TH, T12, T1M, T1i, T1U, Tg, Tt, T19, T1X, T1p, T1P, Ta, TM, T15;
	       E T1N, T1l, T1V, Tl, Ty, T1c, T1Y, T1s, T1Q;
	       {
		    E T1, TD, T4, T1g, TG, T11, T10, T1h;
		    T1 = cr[0];
		    TD = ci[WS(rs, 11)];
		    {
			 E T2, T3, TE, TF;
			 T2 = cr[WS(rs, 4)];
			 T3 = ci[WS(rs, 3)];
			 T4 = T2 + T3;
			 T1g = KP866025403 * (T2 - T3);
			 TE = ci[WS(rs, 7)];
			 TF = cr[WS(rs, 8)];
			 TG = TE - TF;
			 T11 = KP866025403 * (TE + TF);
		    }
		    T5 = T1 + T4;
		    TH = TD + TG;
		    T10 = FNMS(KP500000000, T4, T1);
		    T12 = T10 - T11;
		    T1M = T10 + T11;
		    T1h = FNMS(KP500000000, TG, TD);
		    T1i = T1g + T1h;
		    T1U = T1h - T1g;
	       }
	       {
		    E Tc, Tp, Tf, T17, Ts, T1o, T18, T1n;
		    Tc = cr[WS(rs, 3)];
		    Tp = ci[WS(rs, 8)];
		    {
			 E Td, Te, Tq, Tr;
			 Td = ci[WS(rs, 4)];
			 Te = ci[0];
			 Tf = Td + Te;
			 T17 = KP866025403 * (Td - Te);
			 Tq = cr[WS(rs, 7)];
			 Tr = cr[WS(rs, 11)];
			 Ts = Tq + Tr;
			 T1o = KP866025403 * (Tq - Tr);
		    }
		    Tg = Tc + Tf;
		    Tt = Tp - Ts;
		    T18 = FMA(KP500000000, Ts, Tp);
		    T19 = T17 + T18;
		    T1X = T18 - T17;
		    T1n = FNMS(KP500000000, Tf, Tc);
		    T1p = T1n + T1o;
		    T1P = T1n - T1o;
	       }
	       {
		    E T6, TL, T9, T1j, TK, T14, T13, T1k;
		    T6 = ci[WS(rs, 5)];
		    TL = cr[WS(rs, 6)];
		    {
			 E T7, T8, TI, TJ;
			 T7 = ci[WS(rs, 1)];
			 T8 = cr[WS(rs, 2)];
			 T9 = T7 + T8;
			 T1j = KP866025403 * (T7 - T8);
			 TI = ci[WS(rs, 9)];
			 TJ = cr[WS(rs, 10)];
			 TK = TI - TJ;
			 T14 = KP866025403 * (TI + TJ);
		    }
		    Ta = T6 + T9;
		    TM = TK - TL;
		    T13 = FNMS(KP500000000, T9, T6);
		    T15 = T13 + T14;
		    T1N = T13 - T14;
		    T1k = FMA(KP500000000, TK, TL);
		    T1l = T1j - T1k;
		    T1V = T1j + T1k;
	       }
	       {
		    E Th, Tx, Tk, T1a, Tw, T1r, T1b, T1q;
		    Th = ci[WS(rs, 2)];
		    Tx = cr[WS(rs, 9)];
		    {
			 E Ti, Tj, Tu, Tv;
			 Ti = cr[WS(rs, 1)];
			 Tj = cr[WS(rs, 5)];
			 Tk = Ti + Tj;
			 T1a = KP866025403 * (Ti - Tj);
			 Tu = ci[WS(rs, 10)];
			 Tv = ci[WS(rs, 6)];
			 Tw = Tu + Tv;
			 T1r = KP866025403 * (Tv - Tu);
		    }
		    Tl = Th + Tk;
		    Ty = Tw - Tx;
		    T1b = FMA(KP500000000, Tw, Tx);
		    T1c = T1a - T1b;
		    T1Y = T1a + T1b;
		    T1q = FNMS(KP500000000, Tk, Th);
		    T1s = T1q + T1r;
		    T1Q = T1q - T1r;
	       }
	       {
		    E Tb, Tm, TU, TW, TX, TY, TT, TV;
		    Tb = T5 + Ta;
		    Tm = Tg + Tl;
		    TU = Tb - Tm;
		    TW = TH + TM;
		    TX = Tt + Ty;
		    TY = TW - TX;
		    cr[0] = Tb + Tm;
		    ci[0] = TW + TX;
		    TT = W[10];
		    TV = W[11];
		    cr[WS(rs, 6)] = FNMS(TV, TY, TT * TU);
		    ci[WS(rs, 6)] = FMA(TV, TU, TT * TY);
	       }
	       {
		    E TA, TQ, TO, TS;
		    {
			 E To, Tz, TC, TN;
			 To = T5 - Ta;
			 Tz = Tt - Ty;
			 TA = To - Tz;
			 TQ = To + Tz;
			 TC = Tg - Tl;
			 TN = TH - TM;
			 TO = TC + TN;
			 TS = TN - TC;
		    }
		    {
			 E Tn, TB, TP, TR;
			 Tn = W[16];
			 TB = W[17];
			 cr[WS(rs, 9)] = FNMS(TB, TO, Tn * TA);
			 ci[WS(rs, 9)] = FMA(Tn, TO, TB * TA);
			 TP = W[4];
			 TR = W[5];
			 cr[WS(rs, 3)] = FNMS(TR, TS, TP * TQ);
			 ci[WS(rs, 3)] = FMA(TP, TS, TR * TQ);
		    }
	       }
	       {
		    E T28, T2e, T2c, T2g;
		    {
			 E T26, T27, T2a, T2b;
			 T26 = T1M - T1N;
			 T27 = T1X + T1Y;
			 T28 = T26 - T27;
			 T2e = T26 + T27;
			 T2a = T1U + T1V;
			 T2b = T1P - T1Q;
			 T2c = T2a + T2b;
			 T2g = T2a - T2b;
		    }
		    {
			 E T25, T29, T2d, T2f;
			 T25 = W[8];
			 T29 = W[9];
			 cr[WS(rs, 5)] = FNMS(T29, T2c, T25 * T28);
			 ci[WS(rs, 5)] = FMA(T25, T2c, T29 * T28);
			 T2d = W[20];
			 T2f = W[21];
			 cr[WS(rs, 11)] = FNMS(T2f, T2g, T2d * T2e);
			 ci[WS(rs, 11)] = FMA(T2d, T2g, T2f * T2e);
		    }
	       }
	       {
		    E T1S, T22, T20, T24;
		    {
			 E T1O, T1R, T1W, T1Z;
			 T1O = T1M + T1N;
			 T1R = T1P + T1Q;
			 T1S = T1O - T1R;
			 T22 = T1O + T1R;
			 T1W = T1U - T1V;
			 T1Z = T1X - T1Y;
			 T20 = T1W - T1Z;
			 T24 = T1W + T1Z;
		    }
		    {
			 E T1L, T1T, T21, T23;
			 T1L = W[2];
			 T1T = W[3];
			 cr[WS(rs, 2)] = FNMS(T1T, T20, T1L * T1S);
			 ci[WS(rs, 2)] = FMA(T1T, T1S, T1L * T20);
			 T21 = W[14];
			 T23 = W[15];
			 cr[WS(rs, 8)] = FNMS(T23, T24, T21 * T22);
			 ci[WS(rs, 8)] = FMA(T23, T22, T21 * T24);
		    }
	       }
	       {
		    E T1C, T1I, T1G, T1K;
		    {
			 E T1A, T1B, T1E, T1F;
			 T1A = T12 + T15;
			 T1B = T1p + T1s;
			 T1C = T1A - T1B;
			 T1I = T1A + T1B;
			 T1E = T1i + T1l;
			 T1F = T19 + T1c;
			 T1G = T1E - T1F;
			 T1K = T1E + T1F;
		    }
		    {
			 E T1z, T1D, T1H, T1J;
			 T1z = W[18];
			 T1D = W[19];
			 cr[WS(rs, 10)] = FNMS(T1D, T1G, T1z * T1C);
			 ci[WS(rs, 10)] = FMA(T1D, T1C, T1z * T1G);
			 T1H = W[6];
			 T1J = W[7];
			 cr[WS(rs, 4)] = FNMS(T1J, T1K, T1H * T1I);
			 ci[WS(rs, 4)] = FMA(T1J, T1I, T1H * T1K);
		    }
	       }
	       {
		    E T1e, T1w, T1u, T1y;
		    {
			 E T16, T1d, T1m, T1t;
			 T16 = T12 - T15;
			 T1d = T19 - T1c;
			 T1e = T16 - T1d;
			 T1w = T16 + T1d;
			 T1m = T1i - T1l;
			 T1t = T1p - T1s;
			 T1u = T1m + T1t;
			 T1y = T1m - T1t;
		    }
		    {
			 E TZ, T1f, T1v, T1x;
			 TZ = W[0];
			 T1f = W[1];
			 cr[WS(rs, 1)] = FNMS(T1f, T1u, TZ * T1e);
			 ci[WS(rs, 1)] = FMA(TZ, T1u, T1f * T1e);
			 T1v = W[12];
			 T1x = W[13];
			 cr[WS(rs, 7)] = FNMS(T1x, T1y, T1v * T1w);
			 ci[WS(rs, 7)] = FMA(T1v, T1y, T1x * T1w);
		    }
	       }
	  }
     }
}