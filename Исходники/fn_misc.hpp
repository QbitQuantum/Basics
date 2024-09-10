inline
typename arma_float_only<eT>::result
log_add(eT log_a, eT log_b)
  {
  if(log_a < log_b)
    {
    std::swap(log_a, log_b);
    }
  
  const eT negdelta = log_b - log_a;
  
  if( (negdelta < Math<eT>::log_min()) || (arma_isfinite(negdelta) == false) )
    {
    return log_a;
    }
  else
    {
    #if defined(ARMA_HAVE_LOG1P)
      return (log_a + log1p(std::exp(negdelta)));
    #else
      return (log_a + std::log(1.0 + std::exp(negdelta)));
    #endif
    }
  }