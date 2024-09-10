/////////////////////////////////////////////////
// Epidemiological modeling and model fitting
void TEpidemModel::RunModel(const TFltV& StartValV, const double& StartT, const double& StopT, const int& NSteps, TVec<TFltV>& OutValV) {
  TFltV ValV(StartValV), dydx(StartValV.Len()), ValV2(StartValV.Len());
  OutValV.Clr(false);
  for (int v = 0; v < StartValV.Len(); v++) {
    OutValV.Add();
    OutValV[v].Clr(false);
    OutValV[v].Add(StartValV[v]);
  }
  const double h = (StopT-StartT) / NSteps;
  double x = StartT;
  for (int k = 0; k < NSteps; k++) {
    GetDerivs(x, ValV, dydx);
    RungeKutta(ValV, dydx, x, h, ValV2);
    for (int v = 0; v < ValV2.Len(); v++) {
      double X = ValV2[v];
      if (X < 0 || _isnan(X) || !_finite(X)) { X = 0; }
      OutValV[v].Add(X);
    }
    ValV = ValV2;
    x += h;
  }
}