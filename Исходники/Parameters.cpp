void parameters::Likelihood(const VectorXd & eff){
	 VectorXd loc;
	 loc.resize(m_proba.rows());
	 loc=(m_proba.rowwise().sum().array().log());
	 m_loglikelihood=eff.transpose()*loc;
	 m_bic=m_loglikelihood - 0.5*m_nbparam*log(eff.sum());
}