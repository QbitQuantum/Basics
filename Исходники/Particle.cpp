void SingleParticle2dx::DataStructures::Particle::calculateConsistency()
{
	size_type n = 6;
	std::vector<Eigen::VectorXf> points;
	std::vector<Particle*> neighbors = getNeighbors();
	
	for (size_type i=0; i<static_cast<size_type>(neighbors.size()); i++ )
	{
		Eigen::VectorXf new_vec(n);
		new_vec[0] = neighbors[i]->getNewOrientation().getTLTAXIS();
		new_vec[1] = neighbors[i]->getNewOrientation().getTLTANG();
		new_vec[2] = neighbors[i]->getNewOrientation().getTAXA();
		new_vec[3] = neighbors[i]->getParticleShift().getShiftX();
		new_vec[4] = neighbors[i]->getParticleShift().getShiftY();
		new_vec[5] = neighbors[i]->getSimMeasure();
		points.push_back(new_vec);
	}
	
	Eigen::VectorXf mean(n);
	
	for(size_type i=0; i<static_cast<size_type>(points.size()); i++)
	{
		mean += points[i];
	}
	mean /= static_cast<value_type>(points.size());
	
//	std::cout << ": mean = " << mean[0] << " " << mean[1] << " " << mean[2] << " " << mean[3] << " " << mean[4] << " " << mean[5] << std::endl;
	
	Eigen::MatrixXf covMat = Eigen::MatrixXf::Zero(n,n);
	
//	std::cout << mean << std::endl;
	
	for(size_type i=0; i<static_cast<size_type>(points.size()); i++)
	{
		Eigen::VectorXf diff = (points[i]-mean).conjugate();
		covMat += diff * diff.adjoint();
	}
	
//	std::cout << ":det = " << covMat.determinant() << std::endl;
	
	value_type det = covMat.determinant();
	
	if ( !std::isfinite(det) )
	{
		setConsistency(0);
		return;
	}
	
	if ( det < 0.001 )
	{
		setConsistency(0);
		return;
	}
	
	//SingleParticle2dx::Utilities::UtilityFunctions::reqularizeMatrix(covMat);
	
//	std::cout << covMat << std::endl;
	
	Eigen::VectorXf vec(n);
	vec[0] = getNewOrientation().getTLTAXIS();
	vec[1] = getNewOrientation().getTLTANG();
	vec[2] = getNewOrientation().getTAXA();
	vec[3] = getParticleShift().getShiftX();
	vec[4] = getParticleShift().getShiftY();
	vec[5] = getSimMeasure();
	
	value_type result = -0.5 * log(covMat.determinant());
	
//	#pragma omp critical (det_output)
	//{
		//std::cout << ":det = " << det << std::endl;
	//}
	
	if ( covMat.determinant() < 0.000001 )
	{
		setConsistency(0);
		return;
	}
	
//	std::cout << ":first term: " << result << std::endl;
	
	Eigen::VectorXf tmp1 = (covMat.inverse()) * (vec-mean);
	value_type tmp2 = (vec-mean).dot(tmp1);
	
	result -= 0.5 * tmp2;
	
//	std::cout << ":second term: " << -0.5 * tmp2 << std::endl;

	if ( boost::math::isnan(result) || boost::math::isnan(-result) )
	{
		std::cout << "::reset CONS realy done now" << std::endl;
		result = 0;
	}
	
	setConsistency(result);
}