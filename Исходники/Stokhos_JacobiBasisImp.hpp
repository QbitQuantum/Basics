bool
Stokhos::JacobiBasis<ordinal_type, value_type>::
computeRecurrenceCoefficients(ordinal_type n,
			      Teuchos::Array<value_type>& alpha,
			      Teuchos::Array<value_type>& beta,
			      Teuchos::Array<value_type>& delta,
			      Teuchos::Array<value_type>& gamma) const
{
  value_type a = alphaIndex_;
  value_type b = betaIndex_;

  if (a==0.0 && b==0.0)
  {
    alpha[0] = 0.0;
    beta[0] = 1.0;
    delta[0] = 1.0;
    gamma[0] = 1.0;
  }
  else
  {
    alpha[0] = getB(0)/getA(0);
    beta[0] = 1.0;
    delta[0] = getC(0)/getA(0);
    gamma[0] = 1.0;
  }
  for (ordinal_type i=1; i<n; i++) 
  {
    alpha[i] = getB(i)/getA(i);
    beta[i] = getD(i)/getA(i);
    delta[i] = getC(i)/getA(i);
    gamma[i] = 1.0;
  }

  return false;
}