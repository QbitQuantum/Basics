//#############################################################################
int TrTrackA::StraightLineFit(){

    int _Nhit = _Hit.size();

  // Reset fit values
    Chi2 = FLT_MAX;
    Ndof = 2*_Nhit-4;
    Theta = 0.0;
    Phi = 0.0;
    U[0] = 0.0;
    U[1] = 0.0;
    U[2] = 1.0;
    P0[0] = 0.0;
    P0[1] = 0.0;
    P0[2] = 0.0;
    Rigidity = FLT_MAX;

  // Consistency check on the number of hits
    if (_Nhit<3) return -2;
    P0[2] = _Hit[0].Coo[2];

  // Get hit positions and uncertainties
  // Scale errors (we will use sigmas in microns)
    double hits[_Nhit][3];
    double sigma[_Nhit][3];
    for (int i=0;i<_Nhit;i++){
      for (int j=0;j<3;j++){
          hits[i][j] = _Hit[i].Coo[j];
          sigma[i][j] = 1.e4*_Hit[i].ECoo[j];
      }
    }

  // Lenghts
    double lenz[_Nhit];
    for (int i=0;i<_Nhit;i++) lenz[i] = hits[i][2] - P0[2];

  // F and G matrices
    const int idim = 4;
    double d[2*_Nhit][idim];
    for (int i=0;i<_Nhit;i++) {
      int ix = i;
      int iy = i+_Nhit;
      for (int j=0;j<idim;j++) { d[ix][j] = 0; d[iy][j] = 0;}
      d[ix][0] = 1.;
      d[iy][1] = 1.;
      d[ix][2] = lenz[i];
      d[iy][3] = lenz[i];
    }

  // F*S_x*x + G*S_y*y
    double dx[idim];
    for (int j=0;j<idim;j++) {
      dx[j] = 0.;
      for (int l=0;l<_Nhit;l++) {
        dx[j] += d[l][j]/sigma[l][0]/sigma[l][0]*hits[l][0];
        dx[j] += d[l+_Nhit][j]/sigma[l][1]/sigma[l][1]*hits[l][1];
      }
    }

  // (F*S_x*F + G*S_y*G)
    double Param[idim];
    double InvCov[idim][idim];
    for (int j=0;j<idim;j++) {
      for (int k=0;k<idim;k++) {
        InvCov[j][k] = 0.;
        for (int l=0;l<_Nhit;l++) {
          InvCov[j][k] += d[l][j]/sigma[l][0]/sigma[l][0]*d[l][k];
          InvCov[j][k] += d[l+_Nhit][j]/sigma[l][1]/sigma[l][1]*d[l+_Nhit][k];
        } 
      }
    }
      
  // (F*S_x*F + G*S_y*G)**{-1}
    double determ = 0.0;
    TMatrixD ParaCovariance = TMatrixD(idim,idim,(Double_t*)InvCov," ");
    ParaCovariance = ParaCovariance.Invert(&determ);
    if (determ<=0) return -1;

  // Solution
    for (int k=0;k<idim;k++) {
      Param[k] = 0.;
      for (int i=0;i<idim;i++) {
        Param[k] += ParaCovariance(k,i)*dx[i];
      }
    }

  // Chi2 (xl and yl in microns, since sigmas are in microns too)
    Chi2 = 0.;
    for (int l=0;l<_Nhit;l++) {
      double xl = hits[l][0]*1.e4;
      double yl = hits[l][1]*1.e4;
      for (int k=0;k<idim;k++) {
        xl -= d[l][k]*Param[k]*1.e4;
        yl -= d[l+_Nhit][k]*Param[k]*1.e4;
      }
      Chi2 += xl/sigma[l][0]/sigma[l][0]*xl + yl/sigma[l][1]/sigma[l][1]*yl;
    }

  // Final result
    P0[0] = Param[0];
    P0[1] = Param[1];
    Phi = atan2(Param[3],Param[2]);
    Theta = acos(-sqrt(1-Param[2]*Param[2]-Param[3]*Param[3]));
    U[0] = sin(Theta)*cos(Phi);
    U[1] = sin(Theta)*sin(Phi);
    U[2] = cos(Theta);

    return 0;

}