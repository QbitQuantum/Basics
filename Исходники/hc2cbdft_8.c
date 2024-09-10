static void hc2cbdft_8(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     INT m;
     for (m = mb, W = W + ((mb - 1) * 14); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 14, MAKE_VOLATILE_STRIDE(rs)) {
	  E T1m, T1r, T1i, T1u, T1o, T1v, T1n, T1w, T1s;
	  {
	       E T1k, Tl, T1p, TE, TP, T1g, TM, T1b, T1f, T1a, TU, Tf, T1l, TH, Tw;
	       E T1q;
	       {
		    E TA, T3, TN, Tk, Th, T6, TO, TD, Tb, Tm, Ta, TK, Tp, Tc, Ts;
		    E Tt;
		    {
			 E T4, T5, TB, TC;
			 {
			      E T1, T2, Ti, Tj;
			      T1 = Rp[0];
			      T2 = Rm[WS(rs, 3)];
			      Ti = Ip[0];
			      Tj = Im[WS(rs, 3)];
			      T4 = Rp[WS(rs, 2)];
			      TA = T1 - T2;
			      T3 = T1 + T2;
			      TN = Ti - Tj;
			      Tk = Ti + Tj;
			      T5 = Rm[WS(rs, 1)];
			      TB = Ip[WS(rs, 2)];
			      TC = Im[WS(rs, 1)];
			 }
			 {
			      E T8, T9, Tn, To;
			      T8 = Rp[WS(rs, 1)];
			      Th = T4 - T5;
			      T6 = T4 + T5;
			      TO = TB - TC;
			      TD = TB + TC;
			      T9 = Rm[WS(rs, 2)];
			      Tn = Ip[WS(rs, 1)];
			      To = Im[WS(rs, 2)];
			      Tb = Rm[0];
			      Tm = T8 - T9;
			      Ta = T8 + T9;
			      TK = Tn - To;
			      Tp = Tn + To;
			      Tc = Rp[WS(rs, 3)];
			      Ts = Im[0];
			      Tt = Ip[WS(rs, 3)];
			 }
		    }
		    {
			 E Tr, Td, Tu, TL, Te, T7;
			 T1k = Tk - Th;
			 Tl = Th + Tk;
			 Tr = Tb - Tc;
			 Td = Tb + Tc;
			 TL = Tt - Ts;
			 Tu = Ts + Tt;
			 T1p = TA + TD;
			 TE = TA - TD;
			 TP = TN + TO;
			 T1g = TN - TO;
			 TM = TK + TL;
			 T1b = TL - TK;
			 T1f = Ta - Td;
			 Te = Ta + Td;
			 T1a = T3 - T6;
			 T7 = T3 + T6;
			 {
			      E Tq, TF, TG, Tv;
			      Tq = Tm + Tp;
			      TF = Tm - Tp;
			      TG = Tr - Tu;
			      Tv = Tr + Tu;
			      TU = T7 - Te;
			      Tf = T7 + Te;
			      T1l = TF - TG;
			      TH = TF + TG;
			      Tw = Tq - Tv;
			      T1q = Tq + Tv;
			 }
		    }
	       }
	       {
		    E TX, T10, T1c, T13, T1h, T1E, T1H, T1C, T1K, T1G, T1L, T1F;
		    {
			 E TQ, Tx, T1y, TI, Tg, Tz;
			 TX = TP - TM;
			 TQ = TM + TP;
			 Tx = FMA(KP707106781, Tw, Tl);
			 T10 = FNMS(KP707106781, Tw, Tl);
			 T1c = T1a + T1b;
			 T1y = T1a - T1b;
			 T13 = FNMS(KP707106781, TH, TE);
			 TI = FMA(KP707106781, TH, TE);
			 Tg = W[0];
			 Tz = W[1];
			 {
			      E T1B, T1A, T1x, T1J, T1z, T1D;
			      {
				   E TR, Ty, TS, TJ;
				   T1B = T1g - T1f;
				   T1h = T1f + T1g;
				   T1A = W[11];
				   TR = Tg * TI;
				   Ty = Tg * Tx;
				   T1x = W[10];
				   T1J = T1A * T1y;
				   TS = FNMS(Tz, Tx, TR);
				   TJ = FMA(Tz, TI, Ty);
				   T1z = T1x * T1y;
				   T1m = FMA(KP707106781, T1l, T1k);
				   T1E = FNMS(KP707106781, T1l, T1k);
				   Im[0] = TS - TQ;
				   Ip[0] = TQ + TS;
				   Rm[0] = Tf + TJ;
				   Rp[0] = Tf - TJ;
				   T1H = FMA(KP707106781, T1q, T1p);
				   T1r = FNMS(KP707106781, T1q, T1p);
				   T1D = W[12];
			      }
			      T1C = FNMS(T1A, T1B, T1z);
			      T1K = FMA(T1x, T1B, T1J);
			      T1G = W[13];
			      T1L = T1D * T1H;
			      T1F = T1D * T1E;
			 }
		    }
		    {
			 E TY, T16, T12, T17, T11;
			 {
			      E TW, TT, T15, TV, TZ, T1M, T1I;
			      TW = W[7];
			      T1M = FNMS(T1G, T1E, T1L);
			      T1I = FMA(T1G, T1H, T1F);
			      TT = W[6];
			      T15 = TW * TU;
			      Im[WS(rs, 3)] = T1M - T1K;
			      Ip[WS(rs, 3)] = T1K + T1M;
			      Rm[WS(rs, 3)] = T1C + T1I;
			      Rp[WS(rs, 3)] = T1C - T1I;
			      TV = TT * TU;
			      TZ = W[8];
			      TY = FNMS(TW, TX, TV);
			      T16 = FMA(TT, TX, T15);
			      T12 = W[9];
			      T17 = TZ * T13;
			      T11 = TZ * T10;
			 }
			 {
			      E T1e, T19, T1t, T1d, T1j, T18, T14;
			      T1e = W[3];
			      T18 = FNMS(T12, T10, T17);
			      T14 = FMA(T12, T13, T11);
			      T19 = W[2];
			      T1t = T1e * T1c;
			      Im[WS(rs, 2)] = T18 - T16;
			      Ip[WS(rs, 2)] = T16 + T18;
			      Rm[WS(rs, 2)] = TY + T14;
			      Rp[WS(rs, 2)] = TY - T14;
			      T1d = T19 * T1c;
			      T1j = W[4];
			      T1i = FNMS(T1e, T1h, T1d);
			      T1u = FMA(T19, T1h, T1t);
			      T1o = W[5];
			      T1v = T1j * T1r;
			      T1n = T1j * T1m;
			 }
		    }
	       }
	  }
	  T1w = FNMS(T1o, T1m, T1v);
	  T1s = FMA(T1o, T1r, T1n);
	  Im[WS(rs, 1)] = T1w - T1u;
	  Ip[WS(rs, 1)] = T1u + T1w;
	  Rm[WS(rs, 1)] = T1i + T1s;
	  Rp[WS(rs, 1)] = T1i - T1s;
     }
}