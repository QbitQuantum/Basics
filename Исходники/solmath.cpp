/* ************************************************************************** */
solreal BoysFunction(const int m,solreal x)
{
   static const solreal srpo2=0.88622692545275801365e0; //$\sqrt{\pi}/2$
   solreal srx=sqrt(x);
   solreal F0=srpo2*erf(srx)/srx;
   if (m==0) {return F0;}
   solreal emx=exp(-x);
   solreal oo2x=0.5e0/x;
   if (m==1) {return ((F0-emx)*oo2x);}
   solreal oo2x2=oo2x*oo2x;
   if (m==2) {return (3.0e0*F0*oo2x2-emx*(oo2x+3.0e0*oo2x2));}
   solreal oo2x3=oo2x*oo2x2;
   if (m==3) {return (15.0e0*F0*oo2x3-emx*(oo2x+5.0e0*oo2x2+15.0e0*oo2x3));}
   solreal oo2x4=oo2x2*oo2x2;
   //std::cout << "oo2x4: " << oo2x4 << std::endl;
   if (m==4) {return (105.0e0*F0*oo2x4-emx*(oo2x+7.0e0*oo2x2+35.0e0*oo2x3+105.0e0*oo2x4));}
   solreal oo2x5=oo2x3*oo2x2;
   //std::cout << "oo2x5: " << oo2x5 << std::endl;
   if (m==5) {
      return (945.0e0*F0*oo2x5-emx*(oo2x+9.0e0*oo2x2+63.0e0*oo2x3+315.0e0*oo2x4+945.0e0*oo2x5));
   }
   solreal oo2x6=oo2x3*oo2x3;
   //std::cout << "oo2x6: " << oo2x6 << std::endl;
   if (m==6) {
      return (10395.0e0*F0*oo2x6-emx*(oo2x+11.0e0*oo2x2+99.0e0*oo2x3+693.0e0*oo2x4
                                       +3465.0e0*oo2x5+10395.0e0*oo2x6));
   }
#if DEBUG
   std::cout << "This value of m (" << m << ") is not implemented yet..." << std::endl;
#endif
   return 0.0e0;
}