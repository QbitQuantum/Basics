static void r2cbIII_32(R *R0, R *R1, R *Cr, R *Ci, stride rs, stride csr, stride csi, INT v, INT ivs, INT ovs)
{
     DK(KP1_913880671, +1.913880671464417729871595773960539938965698411);
     DK(KP580569354, +0.580569354508924735272384751634790549382952557);
     DK(KP942793473, +0.942793473651995297112775251810508755314920638);
     DK(KP1_763842528, +1.763842528696710059425513727320776699016885241);
     DK(KP1_546020906, +1.546020906725473921621813219516939601942082586);
     DK(KP1_268786568, +1.268786568327290996430343226450986741351374190);
     DK(KP196034280, +0.196034280659121203988391127777283691722273346);
     DK(KP1_990369453, +1.990369453344393772489673906218959843150949737);
     DK(KP765366864, +0.765366864730179543456919968060797733522689125);
     DK(KP1_847759065, +1.847759065022573512256366378793576573644833252);
     DK(KP1_961570560, +1.961570560806460898252364472268478073947867462);
     DK(KP390180644, +0.390180644032256535696569736954044481855383236);
     DK(KP1_111140466, +1.111140466039204449485661627897065748749874382);
     DK(KP1_662939224, +1.662939224605090474157576755235811513477121624);
     DK(KP1_414213562, +1.414213562373095048801688724209698078569671875);
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     DK(KP382683432, +0.382683432365089771728459984030398866761344562);
     DK(KP923879532, +0.923879532511286756128183189396788286822416626);
     DK(KP707106781, +0.707106781186547524400844362104849039284835938);
     {
	  INT i;
	  for (i = v; i > 0; i = i - 1, R0 = R0 + ovs, R1 = R1 + ovs, Cr = Cr + ivs, Ci = Ci + ivs, MAKE_VOLATILE_STRIDE(128, rs), MAKE_VOLATILE_STRIDE(128, csr), MAKE_VOLATILE_STRIDE(128, csi)) {
	       E T7, T2i, T2F, Tz, T1k, T1I, T1Z, T1x, Te, T22, T2E, T2j, T1f, T1y, TK;
	       E T1J, Tm, T2B, TW, T1a, T1C, T1L, T28, T2l, Tt, T2A, T17, T1b, T1F, T1M;
	       E T2d, T2m;
	       {
		    E T3, Tv, T1j, T2h, T6, T1g, Ty, T2g;
		    {
			 E T1, T2, T1h, T1i;
			 T1 = Cr[0];
			 T2 = Cr[WS(csr, 15)];
			 T3 = T1 + T2;
			 Tv = T1 - T2;
			 T1h = Ci[0];
			 T1i = Ci[WS(csi, 15)];
			 T1j = T1h + T1i;
			 T2h = T1i - T1h;
		    }
		    {
			 E T4, T5, Tw, Tx;
			 T4 = Cr[WS(csr, 8)];
			 T5 = Cr[WS(csr, 7)];
			 T6 = T4 + T5;
			 T1g = T4 - T5;
			 Tw = Ci[WS(csi, 8)];
			 Tx = Ci[WS(csi, 7)];
			 Ty = Tw + Tx;
			 T2g = Tw - Tx;
		    }
		    T7 = T3 + T6;
		    T2i = T2g + T2h;
		    T2F = T2h - T2g;
		    Tz = Tv - Ty;
		    T1k = T1g + T1j;
		    T1I = T1g - T1j;
		    T1Z = T3 - T6;
		    T1x = Tv + Ty;
	       }
	       {
		    E Ta, TA, TD, T21, Td, TF, TI, T20;
		    {
			 E T8, T9, TB, TC;
			 T8 = Cr[WS(csr, 4)];
			 T9 = Cr[WS(csr, 11)];
			 Ta = T8 + T9;
			 TA = T8 - T9;
			 TB = Ci[WS(csi, 4)];
			 TC = Ci[WS(csi, 11)];
			 TD = TB + TC;
			 T21 = TB - TC;
		    }
		    {
			 E Tb, Tc, TG, TH;
			 Tb = Cr[WS(csr, 3)];
			 Tc = Cr[WS(csr, 12)];
			 Td = Tb + Tc;
			 TF = Tb - Tc;
			 TG = Ci[WS(csi, 3)];
			 TH = Ci[WS(csi, 12)];
			 TI = TG + TH;
			 T20 = TH - TG;
		    }
		    Te = Ta + Td;
		    T22 = T20 - T21;
		    T2E = T21 + T20;
		    T2j = Ta - Td;
		    {
			 E T1d, T1e, TE, TJ;
			 T1d = TA + TD;
			 T1e = TF + TI;
			 T1f = KP707106781 * (T1d - T1e);
			 T1y = KP707106781 * (T1d + T1e);
			 TE = TA - TD;
			 TJ = TF - TI;
			 TK = KP707106781 * (TE + TJ);
			 T1J = KP707106781 * (TE - TJ);
		    }
	       }
	       {
		    E Ti, TM, TU, T25, Tl, TR, TP, T26, TQ, TV;
		    {
			 E Tg, Th, TS, TT;
			 Tg = Cr[WS(csr, 2)];
			 Th = Cr[WS(csr, 13)];
			 Ti = Tg + Th;
			 TM = Tg - Th;
			 TS = Ci[WS(csi, 2)];
			 TT = Ci[WS(csi, 13)];
			 TU = TS + TT;
			 T25 = TS - TT;
		    }
		    {
			 E Tj, Tk, TN, TO;
			 Tj = Cr[WS(csr, 10)];
			 Tk = Cr[WS(csr, 5)];
			 Tl = Tj + Tk;
			 TR = Tj - Tk;
			 TN = Ci[WS(csi, 10)];
			 TO = Ci[WS(csi, 5)];
			 TP = TN + TO;
			 T26 = TN - TO;
		    }
		    Tm = Ti + Tl;
		    T2B = T26 + T25;
		    TQ = TM - TP;
		    TV = TR + TU;
		    TW = FNMS(KP382683432, TV, KP923879532 * TQ);
		    T1a = FMA(KP382683432, TQ, KP923879532 * TV);
		    {
			 E T1A, T1B, T24, T27;
			 T1A = TM + TP;
			 T1B = TU - TR;
			 T1C = FNMS(KP923879532, T1B, KP382683432 * T1A);
			 T1L = FMA(KP923879532, T1A, KP382683432 * T1B);
			 T24 = Ti - Tl;
			 T27 = T25 - T26;
			 T28 = T24 - T27;
			 T2l = T24 + T27;
		    }
	       }
	       {
		    E Tp, TX, T15, T2a, Ts, T12, T10, T2b, T11, T16;
		    {
			 E Tn, To, T13, T14;
			 Tn = Cr[WS(csr, 1)];
			 To = Cr[WS(csr, 14)];
			 Tp = Tn + To;
			 TX = Tn - To;
			 T13 = Ci[WS(csi, 1)];
			 T14 = Ci[WS(csi, 14)];
			 T15 = T13 + T14;
			 T2a = T14 - T13;
		    }
		    {
			 E Tq, Tr, TY, TZ;
			 Tq = Cr[WS(csr, 6)];
			 Tr = Cr[WS(csr, 9)];
			 Ts = Tq + Tr;
			 T12 = Tq - Tr;
			 TY = Ci[WS(csi, 6)];
			 TZ = Ci[WS(csi, 9)];
			 T10 = TY + TZ;
			 T2b = TY - TZ;
		    }
		    Tt = Tp + Ts;
		    T2A = T2b + T2a;
		    T11 = TX - T10;
		    T16 = T12 - T15;
		    T17 = FMA(KP923879532, T11, KP382683432 * T16);
		    T1b = FNMS(KP382683432, T11, KP923879532 * T16);
		    {
			 E T1D, T1E, T29, T2c;
			 T1D = TX + T10;
			 T1E = T12 + T15;
			 T1F = FNMS(KP923879532, T1E, KP382683432 * T1D);
			 T1M = FMA(KP923879532, T1D, KP382683432 * T1E);
			 T29 = Tp - Ts;
			 T2c = T2a - T2b;
			 T2d = T29 + T2c;
			 T2m = T2c - T29;
		    }
	       }
	       {
		    E Tf, Tu, T2L, T2M, T2N, T2O;
		    Tf = T7 + Te;
		    Tu = Tm + Tt;
		    T2L = Tf - Tu;
		    T2M = T2B + T2A;
		    T2N = T2F - T2E;
		    T2O = T2M + T2N;
		    R0[0] = KP2_000000000 * (Tf + Tu);
		    R0[WS(rs, 8)] = KP2_000000000 * (T2N - T2M);
		    R0[WS(rs, 4)] = KP1_414213562 * (T2L + T2O);
		    R0[WS(rs, 12)] = KP1_414213562 * (T2O - T2L);
	       }
	       {
		    E T2t, T2x, T2w, T2y;
		    {
			 E T2r, T2s, T2u, T2v;
			 T2r = T1Z - T22;
			 T2s = KP707106781 * (T2m - T2l);
			 T2t = T2r + T2s;
			 T2x = T2r - T2s;
			 T2u = T2j + T2i;
			 T2v = KP707106781 * (T28 - T2d);
			 T2w = T2u - T2v;
			 T2y = T2v + T2u;
		    }
		    R0[WS(rs, 3)] = FMA(KP1_662939224, T2t, KP1_111140466 * T2w);
		    R0[WS(rs, 15)] = FNMS(KP1_961570560, T2x, KP390180644 * T2y);
		    R0[WS(rs, 11)] = FNMS(KP1_111140466, T2t, KP1_662939224 * T2w);
		    R0[WS(rs, 7)] = FMA(KP390180644, T2x, KP1_961570560 * T2y);
	       }
	       {
		    E T2D, T2J, T2I, T2K;
		    {
			 E T2z, T2C, T2G, T2H;
			 T2z = T7 - Te;
			 T2C = T2A - T2B;
			 T2D = T2z + T2C;
			 T2J = T2z - T2C;
			 T2G = T2E + T2F;
			 T2H = Tm - Tt;
			 T2I = T2G - T2H;
			 T2K = T2H + T2G;
		    }
		    R0[WS(rs, 2)] = FMA(KP1_847759065, T2D, KP765366864 * T2I);
		    R0[WS(rs, 14)] = FNMS(KP1_847759065, T2J, KP765366864 * T2K);
		    R0[WS(rs, 10)] = FNMS(KP765366864, T2D, KP1_847759065 * T2I);
		    R0[WS(rs, 6)] = FMA(KP765366864, T2J, KP1_847759065 * T2K);
	       }
	       {
		    E T19, T1n, T1m, T1o;
		    {
			 E TL, T18, T1c, T1l;
			 TL = Tz + TK;
			 T18 = TW + T17;
			 T19 = TL + T18;
			 T1n = TL - T18;
			 T1c = T1a + T1b;
			 T1l = T1f + T1k;
			 T1m = T1c + T1l;
			 T1o = T1c - T1l;
		    }
		    R1[0] = FNMS(KP196034280, T1m, KP1_990369453 * T19);
		    R1[WS(rs, 12)] = FNMS(KP1_546020906, T1n, KP1_268786568 * T1o);
		    R1[WS(rs, 8)] = -(FMA(KP196034280, T19, KP1_990369453 * T1m));
		    R1[WS(rs, 4)] = FMA(KP1_268786568, T1n, KP1_546020906 * T1o);
	       }
	       {
		    E T1r, T1v, T1u, T1w;
		    {
			 E T1p, T1q, T1s, T1t;
			 T1p = Tz - TK;
			 T1q = T1b - T1a;
			 T1r = T1p + T1q;
			 T1v = T1p - T1q;
			 T1s = T1f - T1k;
			 T1t = TW - T17;
			 T1u = T1s - T1t;
			 T1w = T1t + T1s;
		    }
		    R1[WS(rs, 2)] = FMA(KP1_763842528, T1r, KP942793473 * T1u);
		    R1[WS(rs, 14)] = FNMS(KP1_913880671, T1v, KP580569354 * T1w);
		    R1[WS(rs, 10)] = FNMS(KP942793473, T1r, KP1_763842528 * T1u);
		    R1[WS(rs, 6)] = FMA(KP580569354, T1v, KP1_913880671 * T1w);
	       }
	       {
		    E T1T, T1X, T1W, T1Y;
		    {
			 E T1R, T1S, T1U, T1V;
			 T1R = T1x + T1y;
			 T1S = T1L + T1M;
			 T1T = T1R - T1S;
			 T1X = T1R + T1S;
			 T1U = T1J + T1I;
			 T1V = T1C - T1F;
			 T1W = T1U - T1V;
			 T1Y = T1V + T1U;
		    }
		    R1[WS(rs, 3)] = FMA(KP1_546020906, T1T, KP1_268786568 * T1W);
		    R1[WS(rs, 15)] = FNMS(KP1_990369453, T1X, KP196034280 * T1Y);
		    R1[WS(rs, 11)] = FNMS(KP1_268786568, T1T, KP1_546020906 * T1W);
		    R1[WS(rs, 7)] = FMA(KP196034280, T1X, KP1_990369453 * T1Y);
	       }
	       {
		    E T2f, T2p, T2o, T2q;
		    {
			 E T23, T2e, T2k, T2n;
			 T23 = T1Z + T22;
			 T2e = KP707106781 * (T28 + T2d);
			 T2f = T23 + T2e;
			 T2p = T23 - T2e;
			 T2k = T2i - T2j;
			 T2n = KP707106781 * (T2l + T2m);
			 T2o = T2k - T2n;
			 T2q = T2n + T2k;
		    }
		    R0[WS(rs, 1)] = FMA(KP1_961570560, T2f, KP390180644 * T2o);
		    R0[WS(rs, 13)] = FNMS(KP1_662939224, T2p, KP1_111140466 * T2q);
		    R0[WS(rs, 9)] = FNMS(KP390180644, T2f, KP1_961570560 * T2o);
		    R0[WS(rs, 5)] = FMA(KP1_111140466, T2p, KP1_662939224 * T2q);
	       }
	       {
		    E T1H, T1P, T1O, T1Q;
		    {
			 E T1z, T1G, T1K, T1N;
			 T1z = T1x - T1y;
			 T1G = T1C + T1F;
			 T1H = T1z + T1G;
			 T1P = T1z - T1G;
			 T1K = T1I - T1J;
			 T1N = T1L - T1M;
			 T1O = T1K - T1N;
			 T1Q = T1N + T1K;
		    }
		    R1[WS(rs, 1)] = FMA(KP1_913880671, T1H, KP580569354 * T1O);
		    R1[WS(rs, 13)] = FNMS(KP1_763842528, T1P, KP942793473 * T1Q);
		    R1[WS(rs, 9)] = FNMS(KP580569354, T1H, KP1_913880671 * T1O);
		    R1[WS(rs, 5)] = FMA(KP942793473, T1P, KP1_763842528 * T1Q);
	       }
	  }
     }
}