static void t1_10(R *ri, R *ii, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     INT m;
     for (m = mb, W = W + (mb * 18); m < me; m = m + 1, ri = ri + ms, ii = ii + ms, W = W + 18, MAKE_VOLATILE_STRIDE(rs)) {
	  E T7, T1O, TT, T1C, TF, TQ, TR, T1o, T1p, T1y, TX, TY, TZ, T1d, T1g;
	  E T1M, Ti, Tt, Tu, T1r, T1s, T1x, TU, TV, TW, T16, T19, T1L;
	  {
	       E T1, T1B, T6, T1A;
	       T1 = ri[0];
	       T1B = ii[0];
	       {
		    E T3, T5, T2, T4;
		    T3 = ri[WS(rs, 5)];
		    T5 = ii[WS(rs, 5)];
		    T2 = W[8];
		    T4 = W[9];
		    T6 = FMA(T2, T3, T4 * T5);
		    T1A = FNMS(T4, T3, T2 * T5);
	       }
	       T7 = T1 - T6;
	       T1O = T1B - T1A;
	       TT = T1 + T6;
	       T1C = T1A + T1B;
	  }
	  {
	       E Tz, T1b, TP, T1f, TE, T1c, TK, T1e;
	       {
		    E Tw, Ty, Tv, Tx;
		    Tw = ri[WS(rs, 4)];
		    Ty = ii[WS(rs, 4)];
		    Tv = W[6];
		    Tx = W[7];
		    Tz = FMA(Tv, Tw, Tx * Ty);
		    T1b = FNMS(Tx, Tw, Tv * Ty);
	       }
	       {
		    E TM, TO, TL, TN;
		    TM = ri[WS(rs, 1)];
		    TO = ii[WS(rs, 1)];
		    TL = W[0];
		    TN = W[1];
		    TP = FMA(TL, TM, TN * TO);
		    T1f = FNMS(TN, TM, TL * TO);
	       }
	       {
		    E TB, TD, TA, TC;
		    TB = ri[WS(rs, 9)];
		    TD = ii[WS(rs, 9)];
		    TA = W[16];
		    TC = W[17];
		    TE = FMA(TA, TB, TC * TD);
		    T1c = FNMS(TC, TB, TA * TD);
	       }
	       {
		    E TH, TJ, TG, TI;
		    TH = ri[WS(rs, 6)];
		    TJ = ii[WS(rs, 6)];
		    TG = W[10];
		    TI = W[11];
		    TK = FMA(TG, TH, TI * TJ);
		    T1e = FNMS(TI, TH, TG * TJ);
	       }
	       TF = Tz - TE;
	       TQ = TK - TP;
	       TR = TF + TQ;
	       T1o = T1b + T1c;
	       T1p = T1e + T1f;
	       T1y = T1o + T1p;
	       TX = Tz + TE;
	       TY = TK + TP;
	       TZ = TX + TY;
	       T1d = T1b - T1c;
	       T1g = T1e - T1f;
	       T1M = T1d + T1g;
	  }
	  {
	       E Tc, T14, Ts, T18, Th, T15, Tn, T17;
	       {
		    E T9, Tb, T8, Ta;
		    T9 = ri[WS(rs, 2)];
		    Tb = ii[WS(rs, 2)];
		    T8 = W[2];
		    Ta = W[3];
		    Tc = FMA(T8, T9, Ta * Tb);
		    T14 = FNMS(Ta, T9, T8 * Tb);
	       }
	       {
		    E Tp, Tr, To, Tq;
		    Tp = ri[WS(rs, 3)];
		    Tr = ii[WS(rs, 3)];
		    To = W[4];
		    Tq = W[5];
		    Ts = FMA(To, Tp, Tq * Tr);
		    T18 = FNMS(Tq, Tp, To * Tr);
	       }
	       {
		    E Te, Tg, Td, Tf;
		    Te = ri[WS(rs, 7)];
		    Tg = ii[WS(rs, 7)];
		    Td = W[12];
		    Tf = W[13];
		    Th = FMA(Td, Te, Tf * Tg);
		    T15 = FNMS(Tf, Te, Td * Tg);
	       }
	       {
		    E Tk, Tm, Tj, Tl;
		    Tk = ri[WS(rs, 8)];
		    Tm = ii[WS(rs, 8)];
		    Tj = W[14];
		    Tl = W[15];
		    Tn = FMA(Tj, Tk, Tl * Tm);
		    T17 = FNMS(Tl, Tk, Tj * Tm);
	       }
	       Ti = Tc - Th;
	       Tt = Tn - Ts;
	       Tu = Ti + Tt;
	       T1r = T14 + T15;
	       T1s = T17 + T18;
	       T1x = T1r + T1s;
	       TU = Tc + Th;
	       TV = Tn + Ts;
	       TW = TU + TV;
	       T16 = T14 - T15;
	       T19 = T17 - T18;
	       T1L = T16 + T19;
	  }
	  {
	       E T11, TS, T12, T1i, T1k, T1a, T1h, T1j, T13;
	       T11 = KP559016994 * (Tu - TR);
	       TS = Tu + TR;
	       T12 = FNMS(KP250000000, TS, T7);
	       T1a = T16 - T19;
	       T1h = T1d - T1g;
	       T1i = FMA(KP951056516, T1a, KP587785252 * T1h);
	       T1k = FNMS(KP587785252, T1a, KP951056516 * T1h);
	       ri[WS(rs, 5)] = T7 + TS;
	       T1j = T12 - T11;
	       ri[WS(rs, 7)] = T1j - T1k;
	       ri[WS(rs, 3)] = T1j + T1k;
	       T13 = T11 + T12;
	       ri[WS(rs, 9)] = T13 - T1i;
	       ri[WS(rs, 1)] = T13 + T1i;
	  }
	  {
	       E T1N, T1P, T1Q, T1U, T1W, T1S, T1T, T1V, T1R;
	       T1N = KP559016994 * (T1L - T1M);
	       T1P = T1L + T1M;
	       T1Q = FNMS(KP250000000, T1P, T1O);
	       T1S = Ti - Tt;
	       T1T = TF - TQ;
	       T1U = FMA(KP951056516, T1S, KP587785252 * T1T);
	       T1W = FNMS(KP587785252, T1S, KP951056516 * T1T);
	       ii[WS(rs, 5)] = T1P + T1O;
	       T1V = T1Q - T1N;
	       ii[WS(rs, 3)] = T1V - T1W;
	       ii[WS(rs, 7)] = T1W + T1V;
	       T1R = T1N + T1Q;
	       ii[WS(rs, 1)] = T1R - T1U;
	       ii[WS(rs, 9)] = T1U + T1R;
	  }
	  {
	       E T1m, T10, T1l, T1u, T1w, T1q, T1t, T1v, T1n;
	       T1m = KP559016994 * (TW - TZ);
	       T10 = TW + TZ;
	       T1l = FNMS(KP250000000, T10, TT);
	       T1q = T1o - T1p;
	       T1t = T1r - T1s;
	       T1u = FNMS(KP587785252, T1t, KP951056516 * T1q);
	       T1w = FMA(KP951056516, T1t, KP587785252 * T1q);
	       ri[0] = TT + T10;
	       T1v = T1m + T1l;
	       ri[WS(rs, 4)] = T1v - T1w;
	       ri[WS(rs, 6)] = T1v + T1w;
	       T1n = T1l - T1m;
	       ri[WS(rs, 2)] = T1n - T1u;
	       ri[WS(rs, 8)] = T1n + T1u;
	  }
	  {
	       E T1H, T1z, T1G, T1F, T1J, T1D, T1E, T1K, T1I;
	       T1H = KP559016994 * (T1x - T1y);
	       T1z = T1x + T1y;
	       T1G = FNMS(KP250000000, T1z, T1C);
	       T1D = TX - TY;
	       T1E = TU - TV;
	       T1F = FNMS(KP587785252, T1E, KP951056516 * T1D);
	       T1J = FMA(KP951056516, T1E, KP587785252 * T1D);
	       ii[0] = T1z + T1C;
	       T1K = T1H + T1G;
	       ii[WS(rs, 4)] = T1J + T1K;
	       ii[WS(rs, 6)] = T1K - T1J;
	       T1I = T1G - T1H;
	       ii[WS(rs, 2)] = T1F + T1I;
	       ii[WS(rs, 8)] = T1I - T1F;
	  }
     }
}