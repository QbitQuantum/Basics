GMMDesc initutil::gonzalezKwedlo(commonutil::DataSet const& input, idx_type k, std::mt19937& gen, fp_type sampleFactor)
{  
	
// 	std::cout << "sampleFactor = " << sampleFactor << std::endl;	
// 	std::cout << "use2GMM = " << use2GMM << std::endl;	
	
	idx_type sampleSize = sampleFactor * input.points.cols();
	
	idx_type d = input.points.rows();
	idx_type n = input.points.cols();
	
	initutil::check(k, d, n);

	GMMDesc desc;
	Vector sample;

	
	GMMDesc gmmdesc = gmmutil::optimalGaussian(input);
	Matrix covar = gmmdesc.covariances.at(0);
	fp_type trace = covar.trace()/(10.*d*k);	
	desc.means.resize(0,0);
	desc.weights.resize(0);

		
	std::uniform_real_distribution<> urd(0,1);
	std::uniform_int_distribution<> uid(0,input.points.cols()-1);
	
	Matrix randMatrix(d,d);
	Matrix randOrthonormalMatrix(d,d);
	Vector eigenvalues(d);
	
	for (idx_type i=0; i<k; ++i)
	{
		
		if (i==0)
			// draw first point uniformly
			sample = input.points.col(commonutil::randomIndex(input.weights, gen)); 
		else
		{
			// draw next point w.r.t. current mixture
			
			if(sampleFactor < 1)
			{
				commonutil::DataSet samples;
				samples.points.resize(d,sampleSize);
				samples.weights.resize(sampleSize);
				idx_type index;
				for(idx_type j=0; j<sampleSize; ++j){
					index = uid(gen);
				
// std::cout << "index = " << index << std::endl;
					
					samples.points.col(j) = input.points.col(index);
					samples.weights(j) = input.weights(index);
				}
				Vector densities = gmmutil::adaptiveDensities(samples, desc, 1.);	
				
// std::cout << "densities.size() = " << densities.size() << std::endl;

				densities.maxCoeff(&index);
				sample = samples.points.col(index); 

			}
			else
			{
				idx_type index;
				Vector densities = gmmutil::adaptiveDensities(input, desc, 1.);	

// std::cout << "densities.size() = " << densities.size() << std::endl;

				densities.maxCoeff(&index);
				sample = input.points.col(index); 
			}
			
		}
		
		desc.means.conservativeResize(d,i+1);
		desc.means.col(i) = sample;
		
		desc.weights.conservativeResize(i+1);
		desc.weights(i) = urd(gen);
			
		// random covariance
		for (idx_type i=0; i<d; ++i)
			for (idx_type j=0; j<d; ++j)
				randMatrix(i,j)=urd(gen);
		Eigen::HouseholderQR<Matrix> qr(randMatrix);
		randOrthonormalMatrix = qr.householderQ();
		commonutil::fill(eigenvalues,gen, 1.,10.);
		fp_type tmp = trace/eigenvalues.sum();
		eigenvalues = tmp * eigenvalues;
		randMatrix = randOrthonormalMatrix.transpose()*eigenvalues.asDiagonal()*randOrthonormalMatrix;
			
		desc.covariances.push_back(randMatrix);
		
	}
	

	desc.weights /= desc.weights.sum();

	return desc;
}