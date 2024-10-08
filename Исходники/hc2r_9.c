static void hc2r_9(const R *ri, const R *ii, R *O, stride ris, stride iis, stride os, int v, int ivs, int ovs)
{
     DK(KP984807753, +0.984807753012208059366743024589523013670643252);
     DK(KP173648177, +0.173648177666930348851716626769314796000375677);
     DK(KP300767466, +0.300767466360870593278543795225003852144476517);
     DK(KP1_705737063, +1.705737063904886419256501927880148143872040591);
     DK(KP642787609, +0.642787609686539326322643409907263432907559884);
     DK(KP766044443, +0.766044443118978035202392650555416673935832457);
     DK(KP1_326827896, +1.326827896337876792410842639271782594433726619);
     DK(KP1_113340798, +1.113340798452838732905825904094046265936583811);
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     DK(KP866025403, +0.866025403784438646763723170752936183471402627);
     DK(KP2_000000000, +2.000000000000000000000000000000000000000000000);
     DK(KP1_732050807, +1.732050807568877293527446341505872366942805254);
     int i;
     for (i = v; i > 0; i = i - 1, ri = ri + ivs, ii = ii + ivs, O = O + ovs) {
	  E T3, Tq, Tc, Tk, Tj, T8, Tm, Ts, Th, Tr, Tw, Tx;
	  {
	       E Tb, T1, T2, T9, Ta;
	       Ta = ii[WS(iis, 3)];
	       Tb = KP1_732050807 * Ta;
	       T1 = ri[0];
	       T2 = ri[WS(ris, 3)];
	       T9 = T1 - T2;
	       T3 = FMA(KP2_000000000, T2, T1);
	       Tq = T9 + Tb;
	       Tc = T9 - Tb;
	  }
	  {
	       E T4, T7, Ti, Tg, Tl, Td;
	       T4 = ri[WS(ris, 1)];
	       Tk = ii[WS(iis, 1)];
	       {
		    E T5, T6, Te, Tf;
		    T5 = ri[WS(ris, 4)];
		    T6 = ri[WS(ris, 2)];
		    T7 = T5 + T6;
		    Ti = KP866025403 * (T5 - T6);
		    Te = ii[WS(iis, 4)];
		    Tf = ii[WS(iis, 2)];
		    Tg = KP866025403 * (Te + Tf);
		    Tj = Tf - Te;
	       }
	       T8 = T4 + T7;
	       Tl = FMA(KP500000000, Tj, Tk);
	       Tm = Ti + Tl;
	       Ts = Tl - Ti;
	       Td = FNMS(KP500000000, T7, T4);
	       Th = Td - Tg;
	       Tr = Td + Tg;
	  }
	  O[0] = FMA(KP2_000000000, T8, T3);
	  Tw = T3 - T8;
	  Tx = KP1_732050807 * (Tk - Tj);
	  O[WS(os, 3)] = Tw - Tx;
	  O[WS(os, 6)] = Tw + Tx;
	  {
	       E Tp, Tn, To, Tv, Tt, Tu;
	       Tp = FMA(KP1_113340798, Th, KP1_326827896 * Tm);
	       Tn = FNMS(KP642787609, Tm, KP766044443 * Th);
	       To = Tc - Tn;
	       O[WS(os, 1)] = FMA(KP2_000000000, Tn, Tc);
	       O[WS(os, 7)] = To + Tp;
	       O[WS(os, 4)] = To - Tp;
	       Tv = FMA(KP1_705737063, Tr, KP300767466 * Ts);
	       Tt = FNMS(KP984807753, Ts, KP173648177 * Tr);
	       Tu = Tq - Tt;
	       O[WS(os, 2)] = FMA(KP2_000000000, Tt, Tq);
	       O[WS(os, 8)] = Tu + Tv;
	       O[WS(os, 5)] = Tu - Tv;
	  }
     }
}