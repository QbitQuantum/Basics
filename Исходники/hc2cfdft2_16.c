static void hc2cfdft2_16(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DK(KP414213562, +0.414213562373095048801688724209698078569671875);
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     {
	  INT m;
	  for (m = mb, W = W + ((mb - 1) * 8); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 8, MAKE_VOLATILE_STRIDE(64, rs)) {
	       E T4p, T4o, T4n, T4s;
	       {
		    E T1, T2, Tw, Ty, Th, T3, Tx, TE, Ti, TK, Tj, T4, T5;
		    T1 = W[0];
		    T2 = W[2];
		    Tw = W[6];
		    Ty = W[7];
		    Th = W[4];
		    T3 = T1 * T2;
		    Tx = T1 * Tw;
		    TE = T1 * Ty;
		    Ti = T1 * Th;
		    TK = T2 * Th;
		    Tj = W[5];
		    T4 = W[1];
		    T5 = W[3];
		    {
			 E T1v, T2q, T1s, T2s, T38, T3T, T1Y, T3P, T17, T1h, T2x, T2v, T33, T3Q, T3S;
			 E T1N, Tv, T3A, T2E, T3B, T3L, T2c, T3I, T2S, TW, T3E, T3J, T2n, T3D, T2J;
			 E T3M, T2X;
			 {
			      E TF, Tk, Tz, TL, T6, TR, Tq, Tc, T2h, T25, T2k, T29, T1G, T1M, T2P;
			      E T2R;
			      {
				   E T18, TY, T1d, T13, T1H, T1A, T1K, T1E, T37, T1R, T35, T1X;
				   {
					E T1j, T1o, T1W, T1p, T1m, T1Q, T1U, T1q;
					{
					     E T1k, T1l, T1S, T1T;
					     {
						  E T1t, T28, T24, T1D, T1z, T1u, TQ, Tp, Tb;
						  T1t = Ip[0];
						  TQ = T2 * Tj;
						  Tp = T1 * Tj;
						  TF = FNMS(T4, Tw, TE);
						  T1j = FMA(T4, Tj, Ti);
						  Tk = FNMS(T4, Tj, Ti);
						  Tz = FMA(T4, Ty, Tx);
						  T18 = FNMS(T5, Tj, TK);
						  TL = FMA(T5, Tj, TK);
						  TY = FNMS(T4, T5, T3);
						  T6 = FMA(T4, T5, T3);
						  Tb = T1 * T5;
						  TR = FNMS(T5, Th, TQ);
						  T1d = FMA(T5, Th, TQ);
						  Tq = FMA(T4, Th, Tp);
						  T1o = FNMS(T4, Th, Tp);
						  T28 = T6 * Tj;
						  T24 = T6 * Th;
						  T1D = TY * Tj;
						  T1z = TY * Th;
						  Tc = FNMS(T4, T2, Tb);
						  T13 = FMA(T4, T2, Tb);
						  T1u = Im[0];
						  T1k = Ip[WS(rs, 4)];
						  T2h = FMA(Tc, Tj, T24);
						  T25 = FNMS(Tc, Tj, T24);
						  T2k = FNMS(Tc, Th, T28);
						  T29 = FMA(Tc, Th, T28);
						  T1H = FNMS(T13, Tj, T1z);
						  T1A = FMA(T13, Tj, T1z);
						  T1K = FMA(T13, Th, T1D);
						  T1E = FNMS(T13, Th, T1D);
						  T1W = T1t + T1u;
						  T1v = T1t - T1u;
						  T1l = Im[WS(rs, 4)];
					     }
					     T1S = Rm[0];
					     T1T = Rp[0];
					     T1p = Rp[WS(rs, 4)];
					     T1m = T1k - T1l;
					     T1Q = T1k + T1l;
					     T2q = T1T + T1S;
					     T1U = T1S - T1T;
					     T1q = Rm[WS(rs, 4)];
					}
					{
					     E T36, T1V, T1O, T1r, T1n, T1P, T34, T2r;
					     T36 = T4 * T1U;
					     T1V = T1 * T1U;
					     T1O = T1q - T1p;
					     T1r = T1p + T1q;
					     T1n = T1j * T1m;
					     T37 = FMA(T1, T1W, T36);
					     T2r = T1j * T1r;
					     T1P = Th * T1O;
					     T34 = Tj * T1O;
					     T1s = FNMS(T1o, T1r, T1n);
					     T2s = FMA(T1o, T1m, T2r);
					     T1R = FNMS(Tj, T1Q, T1P);
					     T35 = FMA(Th, T1Q, T34);
					     T1X = FNMS(T4, T1W, T1V);
					}
				   }
				   {
					E T1F, T11, T1e, T16, T1L, T1b, T1f, T1C, T2Z;
					{
					     E T14, T15, TZ, T10, T19, T1a, T1B;
					     TZ = Ip[WS(rs, 2)];
					     T10 = Im[WS(rs, 2)];
					     T38 = T35 + T37;
					     T3T = T37 - T35;
					     T1Y = T1R + T1X;
					     T3P = T1X - T1R;
					     T1F = TZ + T10;
					     T11 = TZ - T10;
					     T14 = Rp[WS(rs, 2)];
					     T15 = Rm[WS(rs, 2)];
					     T19 = Ip[WS(rs, 6)];
					     T1a = Im[WS(rs, 6)];
					     T1e = Rp[WS(rs, 6)];
					     T16 = T14 + T15;
					     T1B = T15 - T14;
					     T1L = T19 + T1a;
					     T1b = T19 - T1a;
					     T1f = Rm[WS(rs, 6)];
					     T1C = T1A * T1B;
					     T2Z = T1E * T1B;
					}
					{
					     E T1J, T31, T2u, T30, T32;
					     {
						  E T12, T1g, T1I, T1c, T2w;
						  T12 = TY * T11;
						  T1g = T1e + T1f;
						  T1I = T1f - T1e;
						  T1c = T18 * T1b;
						  T17 = FNMS(T13, T16, T12);
						  T2w = T18 * T1g;
						  T1J = T1H * T1I;
						  T31 = T1K * T1I;
						  T1h = FNMS(T1d, T1g, T1c);
						  T2x = FMA(T1d, T1b, T2w);
					     }
					     T2u = TY * T16;
					     T30 = FMA(T1A, T1F, T2Z);
					     T32 = FMA(T1H, T1L, T31);
					     T1G = FNMS(T1E, T1F, T1C);
					     T2v = FMA(T13, T11, T2u);
					     T1M = FNMS(T1K, T1L, T1J);
					     T33 = T30 + T32;
					     T3Q = T30 - T32;
					}
				   }
			      }
			      {
				   E Tl, T22, T9, T20, Tf, T2O, Ta, T21, T2A, Tm, Tr, Ts;
				   {
					E T7, T8, Td, Te;
					T7 = Ip[WS(rs, 1)];
					T3S = T1G - T1M;
					T1N = T1G + T1M;
					T8 = Im[WS(rs, 1)];
					Td = Rp[WS(rs, 1)];
					Te = Rm[WS(rs, 1)];
					Tl = Ip[WS(rs, 5)];
					T22 = T7 + T8;
					T9 = T7 - T8;
					T20 = Td - Te;
					Tf = Td + Te;
					T2O = T2 * T22;
					Ta = T6 * T9;
					T21 = T2 * T20;
					T2A = T6 * Tf;
					Tm = Im[WS(rs, 5)];
					Tr = Rp[WS(rs, 5)];
					Ts = Rm[WS(rs, 5)];
				   }
				   {
					E Tg, T2a, Tn, T26, T2Q, T27, T2C, T2B, Tu, Tt, To, T23, T2D, T2b;
					Tg = FNMS(Tc, Tf, Ta);
					T2a = Tl + Tm;
					Tn = Tl - Tm;
					T26 = Tr - Ts;
					Tt = Tr + Ts;
					T2Q = T25 * T2a;
					To = Tk * Tn;
					T27 = T25 * T26;
					T2C = Tk * Tt;
					T2B = FMA(Tc, T9, T2A);
					Tu = FNMS(Tq, Tt, To);
					T23 = FMA(T5, T22, T21);
					T2D = FMA(Tq, Tn, T2C);
					T2b = FMA(T29, T2a, T27);
					Tv = Tg + Tu;
					T3A = Tg - Tu;
					T2P = FNMS(T5, T20, T2O);
					T2E = T2B + T2D;
					T3B = T2B - T2D;
					T3L = T2b - T23;
					T2c = T23 + T2b;
					T2R = FNMS(T29, T26, T2Q);
				   }
			      }
			      {
				   E T2f, TC, T2T, TD, T2d, TI, TS, T2e, T2F, T2l, TO, TT;
				   {
					E TG, TH, TA, TB, TM, TN;
					TA = Ip[WS(rs, 7)];
					TB = Im[WS(rs, 7)];
					TG = Rp[WS(rs, 7)];
					T3I = T2R - T2P;
					T2S = T2P + T2R;
					T2f = TA + TB;
					TC = TA - TB;
					TH = Rm[WS(rs, 7)];
					TM = Ip[WS(rs, 3)];
					T2T = Tw * T2f;
					TD = Tz * TC;
					T2d = TG - TH;
					TI = TG + TH;
					TN = Im[WS(rs, 3)];
					TS = Rp[WS(rs, 3)];
					T2e = Tw * T2d;
					T2F = Tz * TI;
					T2l = TM + TN;
					TO = TM - TN;
					TT = Rm[WS(rs, 3)];
				   }
				   {
					E TJ, T2V, TP, T2i, TU, T2G;
					TJ = FNMS(TF, TI, TD);
					T2V = T2h * T2l;
					TP = TL * TO;
					T2i = TS - TT;
					TU = TS + TT;
					T2G = FMA(TF, TC, T2F);
					{
					     E T2g, T2j, TV, T2H;
					     T2g = FMA(Ty, T2f, T2e);
					     T2j = T2h * T2i;
					     TV = FNMS(TR, TU, TP);
					     T2H = TL * TU;
					     {
						  E T2U, T2m, T2I, T2W;
						  T2U = FNMS(Ty, T2d, T2T);
						  T2m = FMA(T2k, T2l, T2j);
						  TW = TJ + TV;
						  T3E = TJ - TV;
						  T2I = FMA(TR, TO, T2H);
						  T2W = FNMS(T2k, T2i, T2V);
						  T3J = T2m - T2g;
						  T2n = T2g + T2m;
						  T3D = T2G - T2I;
						  T2J = T2G + T2I;
						  T3M = T2U - T2W;
						  T2X = T2U + T2W;
					     }
					}
				   }
			      }
			 }
			 {
			      E T3Y, T3x, T3X, T3y, T3r, T3q, T3p, T3u;
			      {
				   E T2Y, T3o, TX, T3s, T3i, T39, T3t, T3l, T3e, T1x, T2M, T2p, T3d, T2K, T2t;
				   E T2y;
				   {
					E T2o, T1Z, T3j, T3k, T1i, T1w, T3g, T3h;
					T2Y = T2S + T2X;
					T3g = T2X - T2S;
					T3h = T2c - T2n;
					T2o = T2c + T2n;
					T1Z = T1N + T1Y;
					T3j = T1Y - T1N;
					T3o = Tv - TW;
					TX = Tv + TW;
					T3s = T3g - T3h;
					T3i = T3g + T3h;
					T3k = T38 - T33;
					T39 = T33 + T38;
					T3Y = T17 - T1h;
					T1i = T17 + T1h;
					T1w = T1s + T1v;
					T3x = T1v - T1s;
					T3t = T3j + T3k;
					T3l = T3j - T3k;
					T3e = T1w - T1i;
					T1x = T1i + T1w;
					T2M = T2o + T1Z;
					T2p = T1Z - T2o;
					T3d = T2J - T2E;
					T2K = T2E + T2J;
					T3X = T2q - T2s;
					T2t = T2q + T2s;
					T2y = T2v + T2x;
					T3y = T2v - T2x;
				   }
				   {
					E T2N, T3c, T3a, T3n, T3b, T2L, T2z, T1y;
					T2N = T1x - TX;
					T1y = TX + T1x;
					T3c = T2Y + T39;
					T3a = T2Y - T39;
					T3n = T2t - T2y;
					T2z = T2t + T2y;
					Ip[0] = KP500000000 * (T1y + T2p);
					Im[WS(rs, 7)] = KP500000000 * (T2p - T1y);
					T3b = T2z + T2K;
					T2L = T2z - T2K;
					{
					     E T3f, T3m, T3v, T3w;
					     T3r = T3e - T3d;
					     T3f = T3d + T3e;
					     Im[WS(rs, 3)] = KP500000000 * (T3a - T2N);
					     Ip[WS(rs, 4)] = KP500000000 * (T2N + T3a);
					     Rp[WS(rs, 4)] = KP500000000 * (T2L + T2M);
					     Rm[WS(rs, 3)] = KP500000000 * (T2L - T2M);
					     Rp[0] = KP500000000 * (T3b + T3c);
					     Rm[WS(rs, 7)] = KP500000000 * (T3b - T3c);
					     T3m = T3i + T3l;
					     T3q = T3l - T3i;
					     T3p = T3n - T3o;
					     T3v = T3n + T3o;
					     T3w = T3s + T3t;
					     T3u = T3s - T3t;
					     Im[WS(rs, 5)] = -(KP500000000 * (FNMS(KP707106781, T3m, T3f)));
					     Ip[WS(rs, 2)] = KP500000000 * (FMA(KP707106781, T3m, T3f));
					     Rp[WS(rs, 2)] = KP500000000 * (FMA(KP707106781, T3w, T3v));
					     Rm[WS(rs, 5)] = KP500000000 * (FNMS(KP707106781, T3w, T3v));
					}
				   }
			      }
			      {
				   E T3R, T4b, T3z, T4q, T4g, T3U, T40, T41, T4r, T4j, T4m, T3G, T46, T3O, T4l;
				   E T3Z, T4c;
				   {
					E T3K, T3N, T4h, T4i, T3C, T3F, T4e, T4f;
					Rp[WS(rs, 6)] = KP500000000 * (FMA(KP707106781, T3q, T3p));
					Rm[WS(rs, 1)] = KP500000000 * (FNMS(KP707106781, T3q, T3p));
					Im[WS(rs, 1)] = -(KP500000000 * (FNMS(KP707106781, T3u, T3r)));
					Ip[WS(rs, 6)] = KP500000000 * (FMA(KP707106781, T3u, T3r));
					T3K = T3I + T3J;
					T4e = T3I - T3J;
					T4f = T3M - T3L;
					T3N = T3L + T3M;
					T3R = T3P - T3Q;
					T4h = T3Q + T3P;
					T4b = T3y + T3x;
					T3z = T3x - T3y;
					T4q = FNMS(KP414213562, T4e, T4f);
					T4g = FMA(KP414213562, T4f, T4e);
					T4i = T3T - T3S;
					T3U = T3S + T3T;
					T40 = T3B + T3A;
					T3C = T3A - T3B;
					T3F = T3D + T3E;
					T41 = T3D - T3E;
					T4r = FNMS(KP414213562, T4h, T4i);
					T4j = FMA(KP414213562, T4i, T4h);
					T4m = T3C - T3F;
					T3G = T3C + T3F;
					T46 = FNMS(KP414213562, T3K, T3N);
					T3O = FMA(KP414213562, T3N, T3K);
					T4l = T3X - T3Y;
					T3Z = T3X + T3Y;
				   }
				   {
					E T45, T3H, T42, T47, T3V;
					T45 = FNMS(KP707106781, T3G, T3z);
					T3H = FMA(KP707106781, T3G, T3z);
					T4c = T41 - T40;
					T42 = T40 + T41;
					T47 = FMA(KP414213562, T3R, T3U);
					T3V = FNMS(KP414213562, T3U, T3R);
					{
					     E T49, T43, T48, T4a, T44, T3W;
					     T49 = FMA(KP707106781, T42, T3Z);
					     T43 = FNMS(KP707106781, T42, T3Z);
					     T48 = T46 - T47;
					     T4a = T46 + T47;
					     T44 = T3V - T3O;
					     T3W = T3O + T3V;
					     Rp[WS(rs, 1)] = KP500000000 * (FMA(KP923879532, T4a, T49));
					     Rm[WS(rs, 6)] = KP500000000 * (FNMS(KP923879532, T4a, T49));
					     Rp[WS(rs, 5)] = KP500000000 * (FMA(KP923879532, T44, T43));
					     Rm[WS(rs, 2)] = KP500000000 * (FNMS(KP923879532, T44, T43));
					     Im[WS(rs, 6)] = -(KP500000000 * (FNMS(KP923879532, T3W, T3H)));
					     Ip[WS(rs, 1)] = KP500000000 * (FMA(KP923879532, T3W, T3H));
					     Ip[WS(rs, 5)] = KP500000000 * (FMA(KP923879532, T48, T45));
					     Im[WS(rs, 2)] = -(KP500000000 * (FNMS(KP923879532, T48, T45)));
					}
				   }
				   {
					E T4d, T4k, T4t, T4u;
					T4p = FMA(KP707106781, T4c, T4b);
					T4d = FNMS(KP707106781, T4c, T4b);
					T4k = T4g - T4j;
					T4o = T4g + T4j;
					T4n = FMA(KP707106781, T4m, T4l);
					T4t = FNMS(KP707106781, T4m, T4l);
					T4u = T4q + T4r;
					T4s = T4q - T4r;
					Im[0] = -(KP500000000 * (FNMS(KP923879532, T4k, T4d)));
					Ip[WS(rs, 7)] = KP500000000 * (FMA(KP923879532, T4k, T4d));
					Rm[0] = KP500000000 * (FMA(KP923879532, T4u, T4t));
					Rp[WS(rs, 7)] = KP500000000 * (FNMS(KP923879532, T4u, T4t));
				   }
			      }
			 }
		    }
	       }
	       Rp[WS(rs, 3)] = KP500000000 * (FMA(KP923879532, T4o, T4n));
	       Rm[WS(rs, 4)] = KP500000000 * (FNMS(KP923879532, T4o, T4n));
	       Im[WS(rs, 4)] = -(KP500000000 * (FNMS(KP923879532, T4s, T4p)));
	       Ip[WS(rs, 3)] = KP500000000 * (FMA(KP923879532, T4s, T4p));
	  }
     }
}