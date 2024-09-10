void Object3D::setTransform(Matrix3D& value)
{
	//ridiculous matrix error
	if (value.m_rawData[0] == 0)
		value.m_rawData[0] = 0.0000000000000000000001f;

	Vector3D elements[3];
	value.decompose(elements);

	Vector3D& vec = elements[0];
	if (m_position.m_x != vec.m_x || m_position.m_y != vec.m_y || m_position.m_z != vec.m_z)
	{
		m_position.m_x = vec.m_x;
		m_position.m_y = vec.m_y;
		m_position.m_z = vec.m_z;
		invalidatePosition();
	}

	vec = elements[1];
	if (m_rotation.m_x != vec.m_x || m_rotation.m_y != vec.m_y || m_rotation.m_z != vec.m_z)
	{
		m_rotation.m_x = vec.m_x;
		m_rotation.m_y = vec.m_y;
		m_rotation.m_z = vec.m_z;
		invalidateRotation();
	}

	vec = elements[2];
	if (m_scaling.m_x != vec.m_x || m_scaling.m_y != vec.m_y || m_scaling.m_z != vec.m_z)
	{
		m_scaling.m_x = vec.m_x;
		m_scaling.m_y = vec.m_y;
		m_scaling.m_z = vec.m_z;
		invalidateScale();
	}
}