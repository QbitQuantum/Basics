// // //
double analysisClass::deltaPzeta( unsigned int iMuR, unsigned int iTauR ){
  TVector3 muT; TVector3 tauT; TVector3 unitmuT; TVector3 unittauT; TVector3 unitbisecT; TVector3 MET;
  muT.SetPtEtaPhi(  muPtcorr(iMuR),    0, MuonPhi->at(iMuR)    );
  tauT.SetPtEtaPhi( tauPtcorr(iTauR), 0, HPSTauPhi->at(iTauR) );
  unitmuT=muT*(1./muT.Mag());  unittauT=tauT*(1./tauT.Mag());
  unitbisecT=(unitmuT+unittauT)*(1./((unitmuT+unittauT).Mag()));
  MET.SetPtEtaPhi( METcorr("Pt"), 0, METcorr("Phi")  );
  double pZeta;  double pZetaVis;
  pZeta    = unitbisecT.Dot( (muT+tauT+MET) );
  pZetaVis = unitbisecT.Dot( (muT+tauT)     );
  /*std::cout<<" TauMag, MuMag: "<<unitmuT.Mag()<<" "<<unittauT.Mag()<<std::endl;
  std::cout<<"  Mu-bisec: "<<muT.DeltaPhi(unitbisecT)<<std::endl;
  std::cout<<" Tau-bisec: "<<tauT.DeltaPhi(unitbisecT)<<std::endl;
  std::cout<<"    Tau-Mu: "<<tauT.DeltaPhi(muT)<<std::endl;
  std::cout<<"(pZeta-1.5*pZetaVis): "<<(pZeta-1.5*pZetaVis)<<std::endl;
  std::cout<<std::endl;*/
  return (pZeta-1.5*pZetaVis);
}