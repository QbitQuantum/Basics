static void hc2cfdft_4(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP500000000, +0.500000000000000000000000000000000000000000000);
     {
	  INT m;
	  for (m = mb, W = W + ((mb - 1) * 6); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 6, MAKE_VOLATILE_STRIDE(16, rs)) {
	       E Td, Tu, Tr, T4, Tm, To, T9, T5, TA, Tp, Tv, TD, T6, Tq;
	       {
		    E Tk, Tl, Tf, TC, Tj, T7, T8, T1, Tn, Tb, Tc;
		    Tb = Ip[0];
		    Tc = Im[0];
		    {
			 E Ti, Tg, Th, T2, T3;
			 Tg = Rm[0];
			 Th = Rp[0];
			 Tk = W[1];
			 Tl = Tb + Tc;
			 Td = Tb - Tc;
			 Tu = Th + Tg;
			 Ti = Tg - Th;
			 Tf = W[0];
			 T2 = Ip[WS(rs, 1)];
			 T3 = Im[WS(rs, 1)];
			 TC = Tk * Ti;
			 Tj = Tf * Ti;
			 T7 = Rp[WS(rs, 1)];
			 Tr = T2 + T3;
			 T4 = T2 - T3;
			 T8 = Rm[WS(rs, 1)];
			 T1 = W[2];
			 Tn = W[4];
		    }
		    Tm = FNMS(Tk, Tl, Tj);
		    To = T7 - T8;
		    T9 = T7 + T8;
		    T5 = T1 * T4;
		    TA = Tn * Tr;
		    Tp = Tn * To;
		    Tv = T1 * T9;
		    TD = FMA(Tf, Tl, TC);
		    T6 = W[3];
		    Tq = W[5];
	       }
	       {
		    E Tw, Ta, TB, Ts;
		    Tw = FMA(T6, T4, Tv);
		    Ta = FNMS(T6, T9, T5);
		    TB = FNMS(Tq, To, TA);
		    Ts = FMA(Tq, Tr, Tp);
		    {
			 E TF, Tx, Te, Tz;
			 TF = Tu + Tw;
			 Tx = Tu - Tw;
			 Te = Ta + Td;
			 Tz = Td - Ta;
			 {
			      E TG, TE, Tt, Ty;
			      TG = TB + TD;
			      TE = TB - TD;
			      Tt = Tm - Ts;
			      Ty = Ts + Tm;
			      Im[0] = KP500000000 * (TE - Tz);
			      Ip[WS(rs, 1)] = KP500000000 * (Tz + TE);
			      Rp[0] = KP500000000 * (TF + TG);
			      Rm[WS(rs, 1)] = KP500000000 * (TF - TG);
			      Rp[WS(rs, 1)] = KP500000000 * (Tx + Ty);
			      Rm[0] = KP500000000 * (Tx - Ty);
			      Im[WS(rs, 1)] = KP500000000 * (Tt - Te);
			      Ip[0] = KP500000000 * (Te + Tt);
			 }
		    }
	       }
	  }
     }
}