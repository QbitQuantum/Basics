	void LaserSensorModel::weightParticle( Particle& particle, 
											const SensorData& data )
	{
		if(!data.hasScan){
			return;
		}
		
		// get the laser ranges we expect to see for this particle
		std::vector<double> zhat = RayTrace( particle, data );

// 		lastTraces.push_back( zhat );
		
		// If the ray tracing is infeasible (signalled by empty return), we set the particle weight to zero
		if( zhat.empty() ) {
			particle.setW( 0 );
			return;
		}

// 		double cumProb = 0;
		double cumProb = 1; // initialize the cumulative probability of all the laser probabilities for this particle
					
		// find out what the probability of seeing the laser from this position is
		std::vector<double> probs(numPoints);
		for( unsigned int s = 0; s < numPoints; s++ ) {

			double rTrue = data.points[s*laserSubsample];
			double rEst = zhat[s];
			
			double indivProb = CalculateGaussian( rEst, rTrue )
							+ CalculateUniform( rTrue )
							+ CalculateExponential( rTrue )
							+ CalculateMaxRange( rTrue );

			probs[s] = indivProb;
			
			// find the probability of the real laser measurement under this distribution, and mulitply it into the cumulative
// 			cumProb = cumProb * indivProb;
// 			cumProb += indivProb;

// 			std::cout << "rEst: " << rEst << ", rTrue: " << rTrue << std::endl;
// 			std::cout << "indivProb: " << indivProb << ", cumProb: " << cumProb << std::endl;
			
		} // end find-cumlative-probability-of-every-laser-beam-for-this-particle

		std::sort( probs.begin(), probs.end() );
		for( unsigned int i = numProbsToSkip; i < numPoints; i++ ) {
			cumProb = cumProb * probs[i];
		}
// 		for( unsigned int i = 0; i < probs.size(); i++ ) {
// 			cumProb += probs[i];
// 		}
	
		particle.setW( cumProb * particle.getW() ); // update the particle weight
				
	}// end LaserSensorModel::weightParticle