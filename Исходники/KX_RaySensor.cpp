bool KX_RaySensor::Evaluate()
{
	bool result = false;
	bool reset = m_reset && m_level;
	m_rayHit = false; 
	m_hitObject = NULL;
	m_hitPosition[0] = 0;
	m_hitPosition[1] = 0;
	m_hitPosition[2] = 0;

	m_hitNormal[0] = 1;
	m_hitNormal[1] = 0;
	m_hitNormal[2] = 0;
	
	KX_GameObject* obj = (KX_GameObject*)GetParent();
	MT_Point3 frompoint = obj->NodeGetWorldPosition();
	MT_Matrix3x3 matje = obj->NodeGetWorldOrientation();
	MT_Matrix3x3 invmat = matje.inverse();
	
	MT_Vector3 todir;
	m_reset = false;
	switch (m_axis)
	{
	case SENS_RAY_X_AXIS: // X
		{
			todir[0] = invmat[0][0];
			todir[1] = invmat[0][1];
			todir[2] = invmat[0][2];
			break;
		}
	case SENS_RAY_Y_AXIS: // Y
		{
			todir[0] = invmat[1][0];
			todir[1] = invmat[1][1];
			todir[2] = invmat[1][2];
			break;
		}
	case SENS_RAY_Z_AXIS: // Z
		{
			todir[0] = invmat[2][0];
			todir[1] = invmat[2][1];
			todir[2] = invmat[2][2];
			break;
		}
	case SENS_RAY_NEG_X_AXIS: // -X
		{
			todir[0] = -invmat[0][0];
			todir[1] = -invmat[0][1];
			todir[2] = -invmat[0][2];
			break;
		}
	case SENS_RAY_NEG_Y_AXIS: // -Y
		{
			todir[0] = -invmat[1][0];
			todir[1] = -invmat[1][1];
			todir[2] = -invmat[1][2];
			break;
		}
	case SENS_RAY_NEG_Z_AXIS: // -Z
		{
			todir[0] = -invmat[2][0];
			todir[1] = -invmat[2][1];
			todir[2] = -invmat[2][2];
			break;
		}
	}
	todir.normalize();
	m_rayDirection[0] = todir[0];
	m_rayDirection[1] = todir[1];
	m_rayDirection[2] = todir[2];

	MT_Point3 topoint = frompoint + (m_distance) * todir;
	PHY_IPhysicsEnvironment* pe = m_scene->GetPhysicsEnvironment();

	if (!pe)
	{
		std::cout << "WARNING: Ray sensor " << GetName() << ":  There is no physics environment!" << std::endl;
		std::cout << "         Check universe for malfunction." << std::endl;
		return false;
	} 

	KX_IPhysicsController *spc = obj->GetPhysicsController();
	KX_GameObject *parent = obj->GetParent();
	if (!spc && parent)
		spc = parent->GetPhysicsController();
	
	if (parent)
		parent->Release();
	

	PHY_IPhysicsEnvironment* physics_environment = this->m_scene->GetPhysicsEnvironment();
	

	KX_RayCast::Callback<KX_RaySensor> callback(this, spc);
	KX_RayCast::RayTest(physics_environment, frompoint, topoint, callback);

	/* now pass this result to some controller */

	if (m_rayHit)
	{
		if (!m_bTriggered)
		{
			// notify logicsystem that ray is now hitting
			result = true;
			m_bTriggered = true;
		}
		else
		{
			// notify logicsystem that ray is STILL hitting ...
			result = false;

		}
	}
	else
	{
		if (m_bTriggered)
		{
			m_bTriggered = false;
			// notify logicsystem that ray JUST left the Object
			result = true;
		}
		else
		{
			result = false;
		}

	}
	if (reset)
		// force an event
		result = true;

	return result;
}