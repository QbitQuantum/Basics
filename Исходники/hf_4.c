static const R *hf_4(R *rio, R *iio, const R *W, stride ios, INT m, INT dist)
{
     INT i;
     for (i = m - 2; i > 0; i = i - 2, rio = rio + dist, iio = iio - dist, W = W + 6, MAKE_VOLATILE_STRIDE(ios)) {
	  E Tq, Tk, Ty, Tw, T8, Tm, To, Te;
	  {
	       E T1, Tv, Ta, Td, Tu, T7, T9, Tc, Tn, Tb;
	       {
		    E Tg, Tj, Tf, Ti;
		    T1 = rio[0];
		    Tg = rio[WS(ios, 3)];
		    Tj = iio[0];
		    Tf = W[4];
		    Ti = W[5];
		    Tv = iio[-WS(ios, 3)];
		    {
			 E T3, T6, T5, Tt, T4, T2, Tp, Th;
			 T3 = rio[WS(ios, 2)];
			 Tp = Tf * Tj;
			 Th = Tf * Tg;
			 T6 = iio[-WS(ios, 1)];
			 T2 = W[2];
			 Tq = FNMS(Ti, Tg, Tp);
			 Tk = FMA(Ti, Tj, Th);
			 T5 = W[3];
			 Tt = T2 * T6;
			 T4 = T2 * T3;
			 Ta = rio[WS(ios, 1)];
			 Td = iio[-WS(ios, 2)];
			 Tu = FNMS(T5, T3, Tt);
			 T7 = FMA(T5, T6, T4);
			 T9 = W[0];
			 Tc = W[1];
		    }
	       }
	       Ty = Tv - Tu;
	       Tw = Tu + Tv;
	       T8 = T1 + T7;
	       Tm = T1 - T7;
	       Tn = T9 * Td;
	       Tb = T9 * Ta;
	       To = FNMS(Tc, Ta, Tn);
	       Te = FMA(Tc, Td, Tb);
	  }
	  {
	       E Ts, Tr, Tl, Tx;
	       Ts = To + Tq;
	       Tr = To - Tq;
	       Tl = Te + Tk;
	       Tx = Tk - Te;
	       rio[WS(ios, 1)] = Tm + Tr;
	       iio[-WS(ios, 3)] = Tm - Tr;
	       iio[0] = Ts + Tw;
	       rio[WS(ios, 2)] = Ts - Tw;
	       iio[-WS(ios, 1)] = Tx + Ty;
	       rio[WS(ios, 3)] = Tx - Ty;
	       rio[0] = T8 + Tl;
	       iio[-WS(ios, 2)] = T8 - Tl;
	  }
     }
     return W;
}