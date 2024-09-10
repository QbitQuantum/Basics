wcFloat wcCostEstimator::cost( const wcMetaVector& meta )
{
	const Eigen::Vector3f V1(Eigen::Vector3f().Ones());
/*
	for( wcPos idx = 0; idx < 3; idx++ )
		if(meta(idx)<WC_PRECISION) return 1.0f;

	wcMetaVector delta0 = (meta - optima);
	wcMetaVector delta1 = (meta - V1);
	wcFloat		 maxQR	= ((V1.transpose()*Qc*V1 + V1.transpose()*Rc*V1)(0));

	return (delta0.transpose()*Qc*delta0 + delta1.transpose()*Rc*delta1)(0)/maxQR;
*/
	for( wcPos idx = 0; idx < 3; idx++ )
		if(meta(idx)<WC_PRECISION) return 1.0f;

	wcMetaVector delta0 = (meta - optima);
	wcFloat		 maxQR	= ((V1.transpose()*Qc*V1))(0);

	return (delta0.transpose()*Qc*delta0)(0)/maxQR;
	
}