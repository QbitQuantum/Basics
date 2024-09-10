/* calculation of dqbardSig_f */
void MRSSNLHardT::dqbardSig_f(const dSymMatrixT& Sig, const dArrayT& qn, dMatrixT& dqbardSig)
{
   dSymMatrixT dhchi_dSig(3),dhc_dSig(3),dhtanphi_dSig(3),dhtanpsi_dSig(3),
               Sig_Dev(3),dQdS(3),II_S(3),SxS_S(3),tmp1(3),tmp2(3);
   dMatrixT SxS(6,6),II(6,6);
   
   II.Identity();
               
   double fchi = qn[0];
   double fc = qn[1];
   double ftan_phi = qn[2];
   double ftan_psi = qn[3]; 
   double A1 = -falpha_chi*(fchi - fchi_r);
   double A2 = -falpha_c*(fc - fc_r);
   double A3 = -falpha_phi*(ftan_phi - tan(fphi_r));
   double A4 = -falpha_psi*ftan_psi;
   double Sig_p = Sig.Trace()/3.0;
   double SN = signof(Sig_p);
   double B1 = (Sig_p+fabs(Sig_p))/2./fGf_I;
   double dB1dP = (SN +fabs(SN))/2./fGf_I;
   double dQdP = ftan_psi;
   
   Sig_Dev.Deviatoric(Sig);
   double temp  = (Sig_Dev.ScalarProduct())/2.0;
   double temp2 = fc - ftan_psi*fchi;
   double temp3 = temp2 * temp2;
   temp += temp3;
   double deno1 = 2.0*sqrt(temp);
   double deno2 = 4.0*pow(temp, ratio32);
   dQdS.SetToScaled(1.0/deno1, Sig_Dev);
   
   II.Multx(Sig_Dev,II_S);
   II_S /= deno1/2.;
   SxS.Outer(Sig_Dev,Sig_Dev);
   //SxS.Multx(Sig_Dev,SxS_S);
   Contract4To2(SxS,Sig_Dev,SxS_S);
   SxS_S /= deno2;
   
   tmp1 = II_S;
   tmp1 -= SxS_S;
   tmp2 = tmp1;
   tmp1 /= fGf_I;
   tmp2 /= fGf_II;
   
   dhchi_dSig = 0.0;
   dhchi_dSig = tmp1;
   for (int i=0; i<3; i++)
       dhchi_dSig[i] += dQdP*dB1dP/3.;
   dhchi_dSig *= A1; 
   dhc_dSig = tmp2;
   dhc_dSig *= A2;
   dhtanphi_dSig = tmp2;
   dhtanphi_dSig *= A3;
   dhtanpsi_dSig = tmp2;
   dhtanpsi_dSig *= A4;
  
   dqbardSig=0.0;
   dqbardSig(0,0) = dhchi_dSig(0,0);
   dqbardSig(0,1) = dhchi_dSig(1,1);
   dqbardSig(0,2) = dhchi_dSig(2,2);
   dqbardSig(0,3) = dhchi_dSig(1,2);
   dqbardSig(0,4) = dhchi_dSig(0,2);
   dqbardSig(0,5) = dhchi_dSig(0,1);
   dqbardSig(1,0) = dhc_dSig(0,0);
   dqbardSig(1,1) = dhc_dSig(1,1);
   dqbardSig(1,2) = dhc_dSig(2,2);
   dqbardSig(1,3) = dhc_dSig(1,2);
   dqbardSig(1,4) = dhc_dSig(0,2);
   dqbardSig(1,5) = dhc_dSig(0,1);
   dqbardSig(2,0) = dhtanphi_dSig(0,0);
   dqbardSig(2,1) = dhtanphi_dSig(1,1);
   dqbardSig(2,2) = dhtanphi_dSig(2,2);
   dqbardSig(2,3) = dhtanphi_dSig(1,2);
   dqbardSig(2,4) = dhtanphi_dSig(0,2);
   dqbardSig(2,5) = dhtanphi_dSig(0,1);
   dqbardSig(3,0) = dhtanpsi_dSig(0,0);
   dqbardSig(3,1) = dhtanpsi_dSig(1,1);
   dqbardSig(3,2) = dhtanpsi_dSig(2,2);
   dqbardSig(3,3) = dhtanpsi_dSig(1,2);
   dqbardSig(3,4) = dhtanpsi_dSig(0,2);
   dqbardSig(3,5) = dhtanpsi_dSig(0,1);
}