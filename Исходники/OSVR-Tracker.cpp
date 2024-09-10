/**
* Handle OSVR tracking.
***/
void* OSVR_Tracker::Provoke(void* pThis, int eD3D, int eD3DInterface, int eD3DMethod, DWORD dwNumberConnected, int& nProvokerIndex)
{
	// update game timer
	m_cGameTimer.Tick();

	static UINT unFrameSkip = 200;
	if (unFrameSkip > 0)
	{
		unFrameSkip--;
		return nullptr;
	}

	if ((!m_psOSVR_ClientContext) || (!m_psOSVR_ClientInterface))
	{
		// create client context handle
		m_psOSVR_ClientContext =
			osvrClientInit("com.mtbs3d.vireio.osvr.tracker", 0);

		// get client interface
		osvrClientGetInterface(m_psOSVR_ClientContext, "/me/head", &m_psOSVR_ClientInterface);
	}
	else
	{
		// update the client context
		osvrClientUpdate(m_psOSVR_ClientContext);

		// let's read the tracker state.
		OSVR_ReturnCode cRet =
			osvrGetPoseState(m_psOSVR_ClientInterface, &m_sTimestamp, &m_sState);
		if (cRet != OSVR_RETURN_SUCCESS)
		{
			OutputDebugStringA("No pose state!\n");
		}
		else
		{
			m_bControlUpdate = true;

			// backup old euler angles and velocity
			float afEulerOld[3];
			float afEulerVelocityOld[3];
			memcpy(&afEulerOld[0], &m_afEuler[0], sizeof(float)* 3);
			memcpy(&afEulerVelocityOld[0], &m_afEulerVelocity[0], sizeof(float)* 3);

			// quaternion -> euler angles
			const float w = (float)m_sState.rotation.data[0];
			const float x = (float)m_sState.rotation.data[1];
			const float y = (float)m_sState.rotation.data[2];
			const float z = (float)m_sState.rotation.data[3];

			float sqw = w*w;
			float sqx = x*x;
			float sqy = y*y;
			float sqz = z*z;

			float unit = sqx + sqy + sqz + sqw;
			float test = x*y + z*w;

			if (test > 0.499*unit)
			{
				// singularity at north pole
				m_afEuler[1] = 2 * atan2(x, w);
				m_afEuler[2] = FLOAT_PI / 2;
				m_afEuler[0] = 0;
			}
			else if (test < -0.499*unit)
			{
				// singularity at south pole
				m_afEuler[1] = -2 * atan2(x, w);
				m_afEuler[2] = -FLOAT_PI / 2;
				m_afEuler[0] = 0;
			}
			else
			{
				m_afEuler[1] = atan2(2 * y*w - 2 * x*z, sqx - sqy - sqz + sqw);
				m_afEuler[2] = asin(2 * test / unit);
				m_afEuler[0] = atan2(2 * x * w - 2 * y * z, -sqx + sqy - sqz + sqw);
			}

			// PITCH = atan2(2.0 * (x * y + w * z), w * w + x * x - y * y - z * z);
			// ROLL = atan2(2 * y * w - 2 * x * z, 1 - 2 * y * y - 2 * z * z);

			// get euler velocity + acceleration
			float afEulerAcceleration[3];
			for (UINT unI = 0; unI < 3; unI++)
			{
				// get the velocity
				m_afEulerVelocity[unI] = (m_afEuler[unI] - afEulerOld[unI]) / (float)m_cGameTimer.DeltaTime();

				// get the acceleration
				afEulerAcceleration[unI] = (m_afEulerVelocity[unI] - afEulerVelocityOld[unI]) / (float)m_cGameTimer.DeltaTime();
			}

			// get predicted euler
			for (UINT unI = 0; unI < 3; unI++)
			{
				// compute predicted euler
				m_afEulerPredicted[unI] = (0.5f * afEulerAcceleration[unI] * ((float)m_cGameTimer.DeltaTime() * (float)m_cGameTimer.DeltaTime())) + (m_afEulerVelocity[unI] * (float)m_cGameTimer.DeltaTime()) + m_afEuler[unI];
			}

			// set position
			m_afPosition[0] = (float)m_sState.translation.data[0];
			m_afPosition[1] = (float)m_sState.translation.data[1];
			m_afPosition[2] = (float)m_sState.translation.data[2];

#ifdef _DEBUG
			// output debug data
			std::wstringstream szPose;
			szPose << L"Got POSE state: Position = ("
				<< m_sState.translation.data[0] << L", "
				<< m_sState.translation.data[1] << L", "
				<< m_sState.translation.data[2] << L"), orientation = ("
				<< osvrQuatGetW(&(m_sState.rotation)) << L", "
				<< osvrQuatGetX(&(m_sState.rotation)) << L", "
				<< osvrQuatGetY(&(m_sState.rotation)) << L", "
				<< osvrQuatGetZ(&(m_sState.rotation)) << L")";
			OutputDebugString(szPose.str().c_str());
#endif
		}
	}

	return nullptr;
}