// ====================================================================== 
Operator GetScaledOperator(const Operator& A, const double alpha) 
{
  ML_Operator* ScaledA = 0;
  ScaledA = ML_Operator_ExplicitlyScale(A.GetML_Operator(),
                                        (double)alpha);

  if (ScaledA == 0)
    ML_THROW("ML_Operator_ExplicitlyScale returned 0", -1);

  Operator res;
  res.Reshape(A.GetDomainSpace(), A.GetRangeSpace(), ScaledA,
              true, A.GetRCPOperatorBox());
    
  return(res);
}