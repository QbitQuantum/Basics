static void hb2_16(R *cr, R *ci, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     DK(KP414213562, +0.414213562373095048801688724209698078569671875);
     {
	  INT m;
	  for (m = mb, W = W + ((mb - 1) * 8); m < me; m = m + 1, cr = cr + ms, ci = ci - ms, W = W + 8, MAKE_VOLATILE_STRIDE(32, rs)) {
	       E Tv, Tw, T2z, T2C, TB, TF, Ty, Tz, T1V, TA, T2G, T3Q, T3C, T3g, T3L;
	       E T30, T3m, T3z, T3w, T3s, T1X, T1Y, T2u, T2c, T2p, TE, TG, T1G, T1o, T1D;
	       {
		    E T3f, T3l, T2F, T3r, T2Z, T3v, TD, Tx;
		    Tv = W[0];
		    Tw = W[2];
		    Tx = Tv * Tw;
		    T2z = W[6];
		    T3f = Tv * T2z;
		    T2C = W[7];
		    T3l = Tv * T2C;
		    TB = W[4];
		    T2F = Tv * TB;
		    T3r = Tw * TB;
		    TF = W[5];
		    T2Z = Tv * TF;
		    T3v = Tw * TF;
		    Ty = W[1];
		    Tz = W[3];
		    TD = Tv * Tz;
		    T1V = FMA(Ty, Tz, Tx);
		    TA = FNMS(Ty, Tz, Tx);
		    T2G = FNMS(Ty, TF, T2F);
		    T3Q = FMA(Tz, TB, T3v);
		    T3C = FNMS(Ty, TB, T2Z);
		    T3g = FMA(Ty, T2C, T3f);
		    T3L = FNMS(Tz, TF, T3r);
		    T30 = FMA(Ty, TB, T2Z);
		    T3m = FNMS(Ty, T2z, T3l);
		    T3z = FMA(Ty, TF, T2F);
		    T3w = FNMS(Tz, TB, T3v);
		    T3s = FMA(Tz, TF, T3r);
		    {
			 E T1W, T2b, TC, T1n;
			 T1W = T1V * TB;
			 T2b = T1V * TF;
			 T1X = FNMS(Ty, Tw, TD);
			 T1Y = FNMS(T1X, TF, T1W);
			 T2u = FNMS(T1X, TB, T2b);
			 T2c = FMA(T1X, TB, T2b);
			 T2p = FMA(T1X, TF, T1W);
			 TC = TA * TB;
			 T1n = TA * TF;
			 TE = FMA(Ty, Tw, TD);
			 TG = FNMS(TE, TF, TC);
			 T1G = FNMS(TE, TB, T1n);
			 T1o = FMA(TE, TB, T1n);
			 T1D = FMA(TE, TF, TC);
		    }
	       }
	       {
		    E TL, T1Z, T2d, T1t, T31, T34, T3n, T3D, T3E, T3R, T1w, T20, Tf, T3M, T2L;
		    E T3h, TW, T2e, T3G, T3H, T3N, T2Q, T36, T2V, T37, Tu, T3S, T18, T1z, T24;
		    E T2g, T27, T2h, T1j, T1y;
		    {
			 E T3, TH, TU, T2I, T1s, T32, T6, T1p, Ta, TM, TK, T33, TP, T2J, Td;
			 E TR;
			 {
			      E T1, T2, TS, TT;
			      T1 = cr[0];
			      T2 = ci[WS(rs, 7)];
			      T3 = T1 + T2;
			      TH = T1 - T2;
			      TS = ci[WS(rs, 9)];
			      TT = cr[WS(rs, 14)];
			      TU = TS + TT;
			      T2I = TS - TT;
			 }
			 {
			      E T1q, T1r, T4, T5;
			      T1q = ci[WS(rs, 15)];
			      T1r = cr[WS(rs, 8)];
			      T1s = T1q + T1r;
			      T32 = T1q - T1r;
			      T4 = cr[WS(rs, 4)];
			      T5 = ci[WS(rs, 3)];
			      T6 = T4 + T5;
			      T1p = T4 - T5;
			 }
			 {
			      E T8, T9, TI, TJ;
			      T8 = cr[WS(rs, 2)];
			      T9 = ci[WS(rs, 5)];
			      Ta = T8 + T9;
			      TM = T8 - T9;
			      TI = ci[WS(rs, 11)];
			      TJ = cr[WS(rs, 12)];
			      TK = TI + TJ;
			      T33 = TI - TJ;
			 }
			 {
			      E TN, TO, Tb, Tc;
			      TN = ci[WS(rs, 13)];
			      TO = cr[WS(rs, 10)];
			      TP = TN + TO;
			      T2J = TN - TO;
			      Tb = ci[WS(rs, 1)];
			      Tc = cr[WS(rs, 6)];
			      Td = Tb + Tc;
			      TR = Tb - Tc;
			 }
			 TL = TH - TK;
			 T1Z = TH + TK;
			 T2d = T1s - T1p;
			 T1t = T1p + T1s;
			 T31 = Ta - Td;
			 T34 = T32 - T33;
			 T3n = T34 - T31;
			 {
			      E T1u, T1v, T7, Te;
			      T3D = T32 + T33;
			      T3E = T2J + T2I;
			      T3R = T3D - T3E;
			      T1u = TM + TP;
			      T1v = TR + TU;
			      T1w = T1u - T1v;
			      T20 = T1u + T1v;
			      T7 = T3 + T6;
			      Te = Ta + Td;
			      Tf = T7 + Te;
			      T3M = T7 - Te;
			      {
				   E T2H, T2K, TQ, TV;
				   T2H = T3 - T6;
				   T2K = T2I - T2J;
				   T2L = T2H + T2K;
				   T3h = T2H - T2K;
				   TQ = TM - TP;
				   TV = TR - TU;
				   TW = TQ + TV;
				   T2e = TQ - TV;
			      }
			 }
		    }
		    {
			 E Ti, T1e, T1c, T2N, T1h, T2O, Tl, T19, Tp, T13, T11, T2S, T16, T2T, Ts;
			 E TY, T2M, T2P;
			 {
			      E Tg, Th, T1a, T1b;
			      Tg = cr[WS(rs, 1)];
			      Th = ci[WS(rs, 6)];
			      Ti = Tg + Th;
			      T1e = Tg - Th;
			      T1a = ci[WS(rs, 14)];
			      T1b = cr[WS(rs, 9)];
			      T1c = T1a + T1b;
			      T2N = T1a - T1b;
			 }
			 {
			      E T1f, T1g, Tj, Tk;
			      T1f = ci[WS(rs, 10)];
			      T1g = cr[WS(rs, 13)];
			      T1h = T1f + T1g;
			      T2O = T1f - T1g;
			      Tj = cr[WS(rs, 5)];
			      Tk = ci[WS(rs, 2)];
			      Tl = Tj + Tk;
			      T19 = Tj - Tk;
			 }
			 {
			      E Tn, To, TZ, T10;
			      Tn = ci[0];
			      To = cr[WS(rs, 7)];
			      Tp = Tn + To;
			      T13 = Tn - To;
			      TZ = ci[WS(rs, 8)];
			      T10 = cr[WS(rs, 15)];
			      T11 = TZ + T10;
			      T2S = TZ - T10;
			 }
			 {
			      E T14, T15, Tq, Tr;
			      T14 = ci[WS(rs, 12)];
			      T15 = cr[WS(rs, 11)];
			      T16 = T14 + T15;
			      T2T = T14 - T15;
			      Tq = cr[WS(rs, 3)];
			      Tr = ci[WS(rs, 4)];
			      Ts = Tq + Tr;
			      TY = Tq - Tr;
			 }
			 T3G = T2N + T2O;
			 T3H = T2S + T2T;
			 T3N = T3H - T3G;
			 T2M = Ti - Tl;
			 T2P = T2N - T2O;
			 T2Q = T2M - T2P;
			 T36 = T2M + T2P;
			 {
			      E T2R, T2U, Tm, Tt;
			      T2R = Tp - Ts;
			      T2U = T2S - T2T;
			      T2V = T2R + T2U;
			      T37 = T2U - T2R;
			      Tm = Ti + Tl;
			      Tt = Tp + Ts;
			      Tu = Tm + Tt;
			      T3S = Tm - Tt;
			 }
			 {
			      E T12, T17, T22, T23;
			      T12 = TY - T11;
			      T17 = T13 - T16;
			      T18 = FNMS(KP414213562, T17, T12);
			      T1z = FMA(KP414213562, T12, T17);
			      T22 = T1c - T19;
			      T23 = T1e + T1h;
			      T24 = FNMS(KP414213562, T23, T22);
			      T2g = FMA(KP414213562, T22, T23);
			 }
			 {
			      E T25, T26, T1d, T1i;
			      T25 = TY + T11;
			      T26 = T13 + T16;
			      T27 = FNMS(KP414213562, T26, T25);
			      T2h = FMA(KP414213562, T25, T26);
			      T1d = T19 + T1c;
			      T1i = T1e - T1h;
			      T1j = FMA(KP414213562, T1i, T1d);
			      T1y = FNMS(KP414213562, T1d, T1i);
			 }
		    }
		    cr[0] = Tf + Tu;
		    {
			 E T3B, T3K, T3F, T3I, T3J, T3A;
			 T3A = Tf - Tu;
			 T3B = T3z * T3A;
			 T3K = T3C * T3A;
			 T3F = T3D + T3E;
			 T3I = T3G + T3H;
			 T3J = T3F - T3I;
			 ci[0] = T3F + T3I;
			 ci[WS(rs, 8)] = FMA(T3z, T3J, T3K);
			 cr[WS(rs, 8)] = FNMS(T3C, T3J, T3B);
		    }
		    {
			 E T3O, T3P, T3T, T3U;
			 T3O = T3M - T3N;
			 T3P = T3L * T3O;
			 T3T = T3R - T3S;
			 T3U = T3L * T3T;
			 cr[WS(rs, 12)] = FNMS(T3Q, T3T, T3P);
			 ci[WS(rs, 12)] = FMA(T3Q, T3O, T3U);
		    }
		    {
			 E T3V, T3W, T3X, T3Y;
			 T3V = T3M + T3N;
			 T3W = TA * T3V;
			 T3X = T3S + T3R;
			 T3Y = TA * T3X;
			 cr[WS(rs, 4)] = FNMS(TE, T3X, T3W);
			 ci[WS(rs, 4)] = FMA(TE, T3V, T3Y);
		    }
		    {
			 E T3j, T3t, T3p, T3x, T3i, T3o;
			 T3i = T37 - T36;
			 T3j = FNMS(KP707106781, T3i, T3h);
			 T3t = FMA(KP707106781, T3i, T3h);
			 T3o = T2Q - T2V;
			 T3p = FNMS(KP707106781, T3o, T3n);
			 T3x = FMA(KP707106781, T3o, T3n);
			 {
			      E T3k, T3q, T3u, T3y;
			      T3k = T3g * T3j;
			      cr[WS(rs, 14)] = FNMS(T3m, T3p, T3k);
			      T3q = T3g * T3p;
			      ci[WS(rs, 14)] = FMA(T3m, T3j, T3q);
			      T3u = T3s * T3t;
			      cr[WS(rs, 6)] = FNMS(T3w, T3x, T3u);
			      T3y = T3s * T3x;
			      ci[WS(rs, 6)] = FMA(T3w, T3t, T3y);
			 }
		    }
		    {
			 E T2X, T3b, T39, T3d, T2W, T35, T38;
			 T2W = T2Q + T2V;
			 T2X = FNMS(KP707106781, T2W, T2L);
			 T3b = FMA(KP707106781, T2W, T2L);
			 T35 = T31 + T34;
			 T38 = T36 + T37;
			 T39 = FNMS(KP707106781, T38, T35);
			 T3d = FMA(KP707106781, T38, T35);
			 {
			      E T2Y, T3a, T3c, T3e;
			      T2Y = T2G * T2X;
			      cr[WS(rs, 10)] = FNMS(T30, T39, T2Y);
			      T3a = T30 * T2X;
			      ci[WS(rs, 10)] = FMA(T2G, T39, T3a);
			      T3c = T1V * T3b;
			      cr[WS(rs, 2)] = FNMS(T1X, T3d, T3c);
			      T3e = T1X * T3b;
			      ci[WS(rs, 2)] = FMA(T1V, T3d, T3e);
			 }
		    }
		    {
			 E T29, T2l, T2j, T2n;
			 {
			      E T21, T28, T2f, T2i;
			      T21 = FNMS(KP707106781, T20, T1Z);
			      T28 = T24 + T27;
			      T29 = FMA(KP923879532, T28, T21);
			      T2l = FNMS(KP923879532, T28, T21);
			      T2f = FMA(KP707106781, T2e, T2d);
			      T2i = T2g - T2h;
			      T2j = FNMS(KP923879532, T2i, T2f);
			      T2n = FMA(KP923879532, T2i, T2f);
			 }
			 {
			      E T2a, T2k, T2m, T2o;
			      T2a = T1Y * T29;
			      cr[WS(rs, 11)] = FNMS(T2c, T2j, T2a);
			      T2k = T2c * T29;
			      ci[WS(rs, 11)] = FMA(T1Y, T2j, T2k);
			      T2m = Tw * T2l;
			      cr[WS(rs, 3)] = FNMS(Tz, T2n, T2m);
			      T2o = Tz * T2l;
			      ci[WS(rs, 3)] = FMA(Tw, T2n, T2o);
			 }
		    }
		    {
			 E T1l, T1E, T1B, T1H;
			 {
			      E TX, T1k, T1x, T1A;
			      TX = FNMS(KP707106781, TW, TL);
			      T1k = T18 - T1j;
			      T1l = FNMS(KP923879532, T1k, TX);
			      T1E = FMA(KP923879532, T1k, TX);
			      T1x = FNMS(KP707106781, T1w, T1t);
			      T1A = T1y - T1z;
			      T1B = FNMS(KP923879532, T1A, T1x);
			      T1H = FMA(KP923879532, T1A, T1x);
			 }
			 {
			      E T1m, T1C, T1F, T1I;
			      T1m = TG * T1l;
			      cr[WS(rs, 13)] = FNMS(T1o, T1B, T1m);
			      T1C = T1o * T1l;
			      ci[WS(rs, 13)] = FMA(TG, T1B, T1C);
			      T1F = T1D * T1E;
			      cr[WS(rs, 5)] = FNMS(T1G, T1H, T1F);
			      T1I = T1G * T1E;
			      ci[WS(rs, 5)] = FMA(T1D, T1H, T1I);
			 }
		    }
		    {
			 E T2s, T2A, T2x, T2D;
			 {
			      E T2q, T2r, T2v, T2w;
			      T2q = FMA(KP707106781, T20, T1Z);
			      T2r = T2g + T2h;
			      T2s = FNMS(KP923879532, T2r, T2q);
			      T2A = FMA(KP923879532, T2r, T2q);
			      T2v = FNMS(KP707106781, T2e, T2d);
			      T2w = T27 - T24;
			      T2x = FMA(KP923879532, T2w, T2v);
			      T2D = FNMS(KP923879532, T2w, T2v);
			 }
			 {
			      E T2t, T2y, T2B, T2E;
			      T2t = T2p * T2s;
			      cr[WS(rs, 7)] = FNMS(T2u, T2x, T2t);
			      T2y = T2p * T2x;
			      ci[WS(rs, 7)] = FMA(T2u, T2s, T2y);
			      T2B = T2z * T2A;
			      cr[WS(rs, 15)] = FNMS(T2C, T2D, T2B);
			      T2E = T2z * T2D;
			      ci[WS(rs, 15)] = FMA(T2C, T2A, T2E);
			 }
		    }
		    {
			 E T1L, T1R, T1P, T1T;
			 {
			      E T1J, T1K, T1N, T1O;
			      T1J = FMA(KP707106781, TW, TL);
			      T1K = T1y + T1z;
			      T1L = FNMS(KP923879532, T1K, T1J);
			      T1R = FMA(KP923879532, T1K, T1J);
			      T1N = FMA(KP707106781, T1w, T1t);
			      T1O = T1j + T18;
			      T1P = FNMS(KP923879532, T1O, T1N);
			      T1T = FMA(KP923879532, T1O, T1N);
			 }
			 {
			      E T1M, T1Q, T1S, T1U;
			      T1M = TB * T1L;
			      cr[WS(rs, 9)] = FNMS(TF, T1P, T1M);
			      T1Q = TB * T1P;
			      ci[WS(rs, 9)] = FMA(TF, T1L, T1Q);
			      T1S = Tv * T1R;
			      cr[WS(rs, 1)] = FNMS(Ty, T1T, T1S);
			      T1U = Tv * T1T;
			      ci[WS(rs, 1)] = FMA(Ty, T1R, T1U);
			 }
		    }
	       }
	  }
     }
}