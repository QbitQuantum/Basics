	void rotation()
	{
		pmath::Vec2f angVec = m_rigidBody->GetPosition() - prevPos;

		if (m_direction * m_rigidBody->GetPosition().x > 0)
		{
			m_sliding = 1.8;
		}
		else
		{
			m_sliding = 1;
		}

		angle = m_sliding * atanf(angVec.y / angVec.x);
		parent->transform.SetRotation(pmath::radiansToDegrees(angle));
	}