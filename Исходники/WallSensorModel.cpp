	void WallSensorModel::weightParticle( Particle& particle, const SensorData& data ) {

		PoseSE2 pose = particle.getPose();
		double x = pose.getX();
		double y = pose.getY();

		if( x < xMin || x > xMax
		 || y < yMin || y > yMax ) {
			particle.setW( 0 );
			return;
		}

		double mapValue = map.GetValue( x, y );
		if( std::abs( mapValue + 1.0 ) < 1E-6 ) {
			particle.setW( 0 );
		}
		else {
			particle.setW( mapValue * particle.getW() );
		}
	}