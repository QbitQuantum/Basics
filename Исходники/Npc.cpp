void Npc::Move(const Vector3f& destination, float elapsedTime) 
{
	if (elapsedTime == 0)
		return;
	// Gravité
	float distanceY = (m_speedGravity * elapsedTime) + (GRAVITY * elapsedTime * elapsedTime / 2.0f);
	if (!CheckCollision(Vector3f(m_pos.x, m_pos.y - distanceY, m_pos.z)))
	{
		m_speedGravity -= GRAVITY * elapsedTime;
	}
	else
	{
		m_speedGravity = 0;
		distanceY = 0;
	}

	// Test si atteint la destination
	if(	abs(destination.x - m_pos.x) < 1
		&& abs(destination.y - m_pos.y) < 1 
		&& abs(destination.z - m_pos.z) < 1) {
	}
	else {
		Vector3f deplacement;
		deplacement = m_rot * m_speed * elapsedTime;

		// chemin le plus court
		Vector3f distance;
		distance.x = m_pos.x - destination.x;
		distance.y = m_pos.y - destination.y;
		distance.z = m_pos.z - destination.z;

		// calculer l'angle entre les 2 vecteurs
		// fix imprecision float
		float n = distance.Dot(deplacement) / (distance.Lenght() * deplacement.Lenght());
		if (n > 1)
			n = 1;
		else if (n < -1)
			n = -1;
		float angleA = acos(n);
		Vector3f axis = distance.Cross(deplacement);
		axis.Normalize();
		// rotation autour de laxe
		float rotation;
		if (abs(angleA) >= m_maxRot && abs(angleA) < PII - m_maxRot)
			rotation = (angleA > 0) ? -m_maxRot : m_maxRot;
		else
			rotation = angleA - PII;
		Quaternion q;
		q.FromAxis(rotation, axis);
		q.Normalise();

		m_rot = q * m_rot;
		m_rot.Normalise();

		// Check collisions
		Vector3f curPos = m_pos;
		Vector3f newPos;
		newPos.x = curPos.x + deplacement.x;
		newPos.y = curPos.y;
		newPos.z = curPos.z;
		if(!CheckCollision(newPos + Vector3f(0,1,0)))
			m_pos.x += deplacement.x;

		newPos.x = curPos.x;
		newPos.y = curPos.y + deplacement.y;
		newPos.z = curPos.z;
		if(!CheckCollision(newPos + Vector3f(0,1,0)))
			m_pos.y += deplacement.y;

		newPos.x = curPos.x;
		newPos.y = curPos.y;
		newPos.z = curPos.z + deplacement.z;
		if(!CheckCollision(newPos + Vector3f(0,1,0)))
			m_pos.z += deplacement.z;

	}

	if (!m_flying)
		m_pos.y += distanceY;
}