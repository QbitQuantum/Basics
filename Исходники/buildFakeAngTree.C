void findEangHang(const TVector3& antnorm,
                  const TVector3& sourcedir,
                  Float_t& eang,
                  Float_t& hang) {
   // both should already be unit vectors
   
   // E angle projects onto the plane
   const TVector3 w = (antnorm.Dot(sourcedir)) * antnorm;
   const TVector3 v = sourcedir - w;
   eang = TMath::Abs( TMath::Pi() - v.Theta() );
   
   // H angle projects out of the plane
   hang = TMath::Abs( TMath::Pi() - w.Theta() );

#ifdef DEBUG
   Printf("w:");
   w.Print();
   Printf("v:");
   v.Print();
#endif

}