void MatterStable::TwoPhaseBoundary::FindMinMax(
    VecCl &V,
    int CentInd,
    double &ResV,
    double &ResP,
    int Min) {
    IntegralFunc_Add = 0;
    if(Min)
        IntegralFunc_Negative = 0;
    else
        IntegralFunc_Negative = 1;
    ResV = Fmin(
        IntegralFunc_PV_Int_Static,
        V[min(CentInd + 2, NumPnt)],
        V[max(1, CentInd - 2)],
        V[CentInd],
        Mis * 0.1,
        ResP);
    if(!Min)
        ResP = -ResP;
}