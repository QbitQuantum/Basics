// todo: some weighting scheme
SparseArray calcCorrNN(const vector<btVector3>& estPts, const vector<btVector3>& obsPts, const vector<float>& pVis) {
  int nEst = estPts.size();
  int nObs = obsPts.size();
  float r = (float)nObs/nEst;
  SparseArray out(nEst);
  MatrixXf distsEstObs = pairwiseSquareDist(toEigenMatrix(estPts), toEigenMatrix(obsPts));
  vector<int> estToObs = argminAlongRows(distsEstObs);
  vector<int> obsToEst = argminAlongRows(distsEstObs.transpose());
  for (int iEst=0; iEst<nEst; iEst++) 
    out[iEst].push_back(IndVal(estToObs[iEst],.5*pVis[iEst]));
  for (int iObs=0; iObs<nObs; iObs++) out[obsToEst[iObs]].push_back(IndVal(iObs,.5/r));
  return out;
}