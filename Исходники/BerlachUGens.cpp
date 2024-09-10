static inline void calc_coeffs4 (double *bcoeff, double *acoeff, double w0, double Dw, double gain)
{
  double G = exp10f(gain/20.f);
  // bandwidth gain is set to half gain
  double GB = exp10f(gain/40.f);
  double c0 = cosf(w0);
  double WB = tanf(Dw/2);
  double e = sqrtf((G*G-GB*GB)/(GB*GB-1.f));
  double g = powf(G, 0.25f);
  double a = powf(e, 0.25f);
#define  si1  0.382683432365089781779f;
#define  si2  0.923879532511286738483f;
  //Ba(1+i,:) = [g^2*WB^2*v, 2*g*b*si*WB, b^2*v]
  //Aa(1+i,:) = [WB^2*v, 2*a*si*WB, a^2*v]
  double Aa0 = WB*WB;
  double Aatmp = 2*a*WB;
  double Aa10 = Aatmp * si1;
  double Aa11 = Aatmp * si2;
  double as = a*a;
  double Ba0 = Aa0 * g*g;
  double Batmp = 2*g * a * WB;
  double Ba10 = Batmp * si1;
  double Ba11 = Batmp * si2;
  //  fprintf(stdout, "%f %f %f %f %f %f %f\n", Aa0, Aa10, Aa11, Ba0, Ba10, Ba11, as);
  //  double Bhat0 = Ba0/Aa0;
  //  D = A0(i)+A1(i)+A2(i)
  double D1 = Aa0+Aa11+as;
  double D0 = Aa0+Aa10+as;
  //Bhat(i,1) = (B0(i)+B1(i)+B2(i))./D
  //(B0(i)+B1(i)+B2(i))./D
  double tmp = Ba0+as;
  double x;
  double Bhat00 = (Ba10+tmp)/D0;
  double Bhat01 = (Ba11+tmp)/D1;
  x=2.f*(Ba0-as);
  double Bhat10 = x/D0;
  double Bhat11 = x/D1;
  double Bhat20 = (tmp-Ba10)/D0;
  double Bhat21 = (tmp-Ba11)/D1;
  //Ahat(i,1) = 1
  //Ahat(i,2) = 2*(A0(i)-A2(i))./D
  //Ahat(i,3) = (A0(i)-A1(i)+A2(i))./D
  x = 2.f*(Aa0-as);
  double Ahat10 = x/D0;
  double Ahat11 = x/D1;
  double Ahat20 = (Aa0-Aa10+as)/D0;
  double Ahat21 = (Aa0-Aa11+as)/D1;

  //  fprintf(stdout, "%f %f %f %f %f\n %f %f %f %f\n\n",Bhat00, Bhat01, Bhat10, Bhat11, Bhat21, Ahat11, Ahat10, Ahat20, Ahat21);


  // B(i,2) = c0*(Bhat(i,2)-2*Bhat(i,1))
  bcoeff[0] = Bhat00;
  bcoeff[5] = Bhat01;
  bcoeff[1] = c0*(Bhat10-2.f*Bhat00);
  bcoeff[6] = c0*(Bhat11-2.f*Bhat01);
  bcoeff[2] = (Bhat00-Bhat10+Bhat20)*c0*c0- Bhat10;
  bcoeff[7] = (Bhat01-Bhat11+Bhat21)*c0*c0 - Bhat11;
  bcoeff[3] = c0*(Bhat10-2.f*Bhat20);
  bcoeff[8] = c0*(Bhat11-2.f*Bhat21);
  bcoeff[4] = Bhat20;
  bcoeff[9] = Bhat21;

  //  fprintf(stdout, "%f %f %f %f %f\n %f %f %f %f %f\n", Bres00, Bres10, Bres20, Bres30, Bres40, Bres01, Bres11, Bres21, Bres31, Bres41);

  acoeff[0]= c0*(Ahat10-2.f);
  acoeff[4]= c0*(Ahat11-2.f);
  acoeff[1]= (1.f-Ahat10+Ahat20)*c0*c0 - Ahat10;
  acoeff[5]= (1.f-Ahat11+Ahat21)*c0*c0- Ahat11;
  acoeff[2]= c0*(Ahat10-2.f*Ahat20);
  acoeff[6]= c0*(Ahat11-2.f*Ahat21);
  acoeff[3]= Ahat20;
  acoeff[7]= Ahat21;

  //  fprintf(stdout, "%f %f %f %f %f\n %f %f %f %f %f\n", Ares00, Ares10, Ares20, Ares30, Ares40, Ares01, Ares11, Ares21, Ares31, Ares41);
}