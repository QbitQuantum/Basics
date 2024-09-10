	void Simulation :: dampVelocities( void )
	{
		// [ Mueller - 2007 Sec: 3.5 ]
		for( unsigned mIdx = 0; mIdx < m_meshes.size(); ++mIdx ){

			Vector x_cm;
			Vector v_cm;
			double sumMass = 0.;
		    for( VertexIter v = m_meshes[mIdx]->vertices.begin(); v != m_meshes[mIdx]->vertices.end(); ++v ){
		    	sumMass += v->mass;
		    	x_cm += v->position * v->mass;
		    	v_cm += v->velocity * v->mass;
		    }
			x_cm /= sumMass;
			v_cm /= sumMass;

			Vector r;
			Vector L;
			Eigen::Matrix3d I = Eigen::Matrix3d::Zero();
		    for( VertexIter v = m_meshes[mIdx]->vertices.begin(); v != m_meshes[mIdx]->vertices.end(); ++v ){
		    	r = v->position - x_cm;
		    	L += cross( r, v->mass * v->velocity );
		    	Eigen::Matrix3d singleI = Eigen::Matrix3d::Zero();
		    	singleI << 0.,  r[2], -r[1],
		    			-r[2],    0.,  r[0],
		    			 r[2], -r[0],    0.;
		    	I += singleI * singleI.transpose() * v->mass;
			}
			Eigen::Vector3d L_tmp ( L[0], L[1], L[2] );
			Eigen::Vector3d omegaTemp = I.inverse() * L_tmp;
			Vector ang_vel_omega( omegaTemp[0], omegaTemp[1], omegaTemp[2] );

		    for( VertexIter v = m_meshes[mIdx]->vertices.begin(); v != m_meshes[mIdx]->vertices.end(); ++v ){
		    	r = v->position - x_cm;
		    	Vector delta_v = v_cm + cross( ang_vel_omega, r ) - v->velocity;
		    	v->velocity = v->velocity + ( m_meshes[mIdx]->dampingStiffness() * delta_v );
			}

		}
	}