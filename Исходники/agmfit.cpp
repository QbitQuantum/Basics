// Compute the change in likelihood (Delta) if node UID joins community CID.
double TAGMFit::SeekJoin(const int& UID, const int& CID) {
  IAssert(! CIDNSetV[CID].IsKey(UID));
  double Delta = 0.0;
  TUNGraph::TNodeI NI = G->GetNI(UID);
  int NbhsInC = 0;
  for (int e = 0; e < NI.GetDeg(); e++) {
    const int VID = NI.GetNbrNId(e);
    if (! NIDComVH.GetDat(VID).IsKey(CID)) { continue; }
    TIntPr SrcDstNIDPr(TMath::Mn(UID,VID), TMath::Mx(UID,VID));
    TIntSet& JointCom = EdgeComVH.GetDat(SrcDstNIDPr);
    double CurPuv, NewPuv, LambdaSum = SelectLambdaSum(JointCom);
    CurPuv = 1 - exp(- LambdaSum);
    if (JointCom.Len() == 0) { CurPuv = PNoCom; }
    NewPuv = 1 - exp(- LambdaSum - LambdaV[CID]);
    Delta += (log(NewPuv) - log(CurPuv));
    IAssert(!_isnan(Delta));
    NbhsInC++;
  }
  Delta -= LambdaV[CID] * (CIDNSetV[CID].Len() - NbhsInC);
  return Delta;
}