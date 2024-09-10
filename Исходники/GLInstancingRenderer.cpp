	void mouseMoveCallback(float x, float y)
	{
		if (m_altPressed || m_controlPressed)
		{
			float xDelta = x-m_mouseXpos;
			float yDelta = y-m_mouseYpos;
			
			if (m_leftMouseButton)
			{
	//			if (b3Fabs(xDelta)>b3Fabs(yDelta))
	//			{
					m_azi -= xDelta*MOUSE_MOVE_MULTIPLIER;
	//			} else
	//			{
					m_ele += yDelta*MOUSE_MOVE_MULTIPLIER;
	//			}
			}
			if (m_middleMouseButton)
			{
				m_cameraTargetPosition += m_cameraUp * yDelta*0.01;

				
				b3Vector3 fwd = m_cameraTargetPosition-m_cameraPosition;
				b3Vector3 side = m_cameraUp.cross(fwd);
				side.normalize();
				m_cameraTargetPosition += side * xDelta*0.01;

			}
			if (m_rightMouseButton)
			{
					m_cameraDistance -= xDelta*0.01;
					m_cameraDistance -= yDelta*0.01;
					if (m_cameraDistance<1)
						m_cameraDistance=1;
					if (m_cameraDistance>1000)
						m_cameraDistance=1000;
			}
		}

		//printf("m_azi/pitch = %f\n", m_azi);
//		printf("m_ele/yaw = %f\n", m_ele);

		m_mouseXpos = x;
		m_mouseYpos = y;
		m_mouseInitialized = true;
	}