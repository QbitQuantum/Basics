bool ccClipBox::move3D(const CCVector3d& uInput)
{
	if (m_activeComponent == NONE || !m_box.isValid())
		return false;

	CCVector3d u = uInput;

	//Arrows
	if (m_activeComponent >= X_MINUS_ARROW && m_activeComponent <= CROSS)
	{
		if (m_glTransEnabled)
			m_glTrans.inverse().applyRotation(u);

		switch(m_activeComponent)
		{
		case X_MINUS_ARROW:
			m_box.minCorner().x += static_cast<PointCoordinateType>(u.x);
			if (m_box.minCorner().x > m_box.maxCorner().x)
				m_box.minCorner().x = m_box.maxCorner().x;
			break;
		case X_PLUS_ARROW:
			m_box.maxCorner().x += static_cast<PointCoordinateType>(u.x);
			if (m_box.minCorner().x > m_box.maxCorner().x)
				m_box.maxCorner().x = m_box.minCorner().x;
			break;
		case Y_MINUS_ARROW:
			m_box.minCorner().y += static_cast<PointCoordinateType>(u.y);
			if (m_box.minCorner().y > m_box.maxCorner().y)
				m_box.minCorner().y = m_box.maxCorner().y;
			break;
		case Y_PLUS_ARROW:
			m_box.maxCorner().y += static_cast<PointCoordinateType>(u.y);
			if (m_box.minCorner().y > m_box.maxCorner().y)
				m_box.maxCorner().y = m_box.minCorner().y;
			break;
		case Z_MINUS_ARROW:
			m_box.minCorner().z += static_cast<PointCoordinateType>(u.z);
			if (m_box.minCorner().z > m_box.maxCorner().z)
				m_box.minCorner().z = m_box.maxCorner().z;
			break;
		case Z_PLUS_ARROW:
			m_box.maxCorner().z += static_cast<PointCoordinateType>(u.z);
			if (m_box.minCorner().z > m_box.maxCorner().z)
				m_box.maxCorner().z = m_box.minCorner().z;
			break;
		case CROSS:
			m_box += CCVector3::fromArray(u.u);
			break;
		default:
			assert(false);
			return false;
		}
		
		//send 'modified' signal
		emit boxModified(&m_box);
	}
	else if (m_activeComponent == SPHERE)
	{
		//handled by move2D!
		return false;
	}
	else if (m_activeComponent >= X_MINUS_TORUS && m_activeComponent <= Z_PLUS_TORUS)
	{
		//we guess the rotation order by comparing the current screen 'normal'
		//and the vector prod of u and the current rotation axis
		CCVector3d Rb(0,0,0);
		switch(m_activeComponent)
		{
		case X_MINUS_TORUS:
			Rb.x = -1;
			break;
		case X_PLUS_TORUS:
			Rb.x = 1;
			break;
		case Y_MINUS_TORUS:
			Rb.y = -1;
			break;
		case Y_PLUS_TORUS:
			Rb.y = 1;
			break;
		case Z_MINUS_TORUS:
			Rb.z = -1;
			break;
		case Z_PLUS_TORUS:
			Rb.z = 1;
			break;
		default:
			assert(false);
			return false;
		}
		
		CCVector3d R = Rb;
		if (m_glTransEnabled)
			m_glTrans.applyRotation(R);

		CCVector3d RxU = R.cross(u);

		//look for the most parallel dimension
		int minDim = 0;
		double maxDot = m_viewMatrix.getColumnAsVec3D(0).dot(RxU);
		for (int i=1; i<3; ++i)
		{
			double dot = m_viewMatrix.getColumnAsVec3D(i).dot(RxU);
			if (fabs(dot) > fabs(maxDot))
			{
				maxDot = dot;
				minDim = i;
			}
		}

		//angle is proportional to absolute displacement
		double angle_rad = u.norm()/m_box.getDiagNorm() * M_PI;
		if (maxDot < 0.0)
			angle_rad = -angle_rad;

		ccGLMatrixd rotMat;
		rotMat.initFromParameters(angle_rad,Rb,CCVector3d(0,0,0));

		CCVector3 C = m_box.getCenter();
		ccGLMatrixd transMat;
		transMat.setTranslation(-C);
		transMat = rotMat * transMat;
		transMat.setTranslation(transMat.getTranslationAsVec3D() + CCVector3d::fromArray(C.u));

		m_glTrans = m_glTrans * ccGLMatrix(transMat.inverse().data());
		enableGLTransformation(true);
	}
	else
	{
		assert(false);
		return false;
	}

	update();

	return true;
}