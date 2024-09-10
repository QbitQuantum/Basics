double pp_model::log_likelihood_up_to(double t){
  if(m_poisson_regression)
    return poisson_regression_log_likelihood_interval(0,static_cast<int>(ceil(t)));
  m_r = m_data_cont ? m_data_cont->find_data_index(t) : 0;
  return log_likelihood_interval_with_count(0,t,m_r);
}