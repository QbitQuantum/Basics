double HWWKinematics::CalcUnboostedMTR(TLorentzVector P, TLorentzVector Q, TVector3 M){
    // first calculate pt-corrected MR
 float mymrnew = CalcMRNEW(L1,L2,MET);

    //Next, calculate the transverse Lorentz transformation
 TVector3 B = P.Vect()+Q.Vect()+MET;
 B.SetZ(0.0);
 B = (-1./(sqrt(4.*mymrnew*mymrnew+B.Dot(B))))*B;

 P.Boost(B);
 Q.Boost(B);

    //Now, re-calculate MTR in the new reference frame:
 float mymtrnew = CalcMTRNEW(P, Q);

    //R is now just the ratio of mymrnew and mymtrnew;

 return mymtrnew;
}