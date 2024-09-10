/*
   See Waggoner and Zha, "A Gibbs sampler for structural vector autoregressions", 
   JEDC 2003, for discription of notations.  We take the square root of a 
   symmetric and positive definite X to be any matrix Y such that Y*Y'=X.  Note 
   that this is not the usual definition because we do not require Y to be 
   symmetric and positive definite.
*/
void SBVAR_symmetric_linear::SetSimulationInfo(void)
{
  if (NumberObservations() == 0)
    throw dw_exception("SetSimulationInfo(): cannot simulate if no observations");

  TDenseMatrix all_YY, all_XY, all_XX;
  if (flat_prior)
    {
      all_YY=YY;
      all_XY=XY;
      all_XX=XX;
    }
  else
    {
      TDenseMatrix all_Y, all_X;
      all_Y=VCat(sqrt(lambda)*Data(),sqrt(lambda_bar)*prior_Y);
      all_X=VCat(sqrt(lambda)*PredeterminedData(),sqrt(lambda_bar)*prior_X);
      all_YY=Transpose(all_Y)*all_Y;
      all_XY=Transpose(all_X)*all_Y;
      all_XX=Transpose(all_X)*all_X;
    }

  Simulate_SqrtH.resize(n_vars);
  Simulate_P.resize(n_vars);
  Simulate_SqrtS.resize(n_vars);
  Simulate_USqrtS.resize(n_vars);

  for (int i=n_vars-1; i >= 0; i--)
    {
      TDenseMatrix invH=Transpose(V[i])*(all_XX*V[i]);
      Simulate_SqrtH[i]=Inverse(Cholesky(invH,CHOLESKY_UPPER_TRIANGULAR),SOLVE_UPPER_TRIANGULAR);
      Simulate_P[i]=Simulate_SqrtH[i]*(Transpose(Simulate_SqrtH[i])*(Transpose(V[i])*(all_XY*U[i])));
      Simulate_SqrtS[i]=sqrt(lambda_T)*Inverse(Cholesky(Transpose(U[i])*(all_YY*U[i]) - Transpose(Simulate_P[i])*(invH*Simulate_P[i]),CHOLESKY_UPPER_TRIANGULAR),SOLVE_UPPER_TRIANGULAR);
      Simulate_USqrtS[i]=U[i]*Simulate_SqrtS[i];
    }

  simulation_info_set=true;
}