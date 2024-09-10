void Projectile::Update(float elapsedTime) 
{
	// Test si les conditions de fin du projectile sont vraies
	if (m_timeToLive <= 0 || !m_shot || elapsedTime == 0)
		return;

	// Test si atteint la cible
	if(	abs(m_destination.x - m_pos.x) < m_collisionRadius.x 
		&& abs(m_destination.y - m_pos.y) < m_collisionRadius.y 
		&& abs(m_destination.z - m_pos.z) < m_collisionRadius.z) {
			Hit();
			return;
	}
	Vector3f speed = m_rot * m_speed;
	speed = speed * m_speed.Lenght();
	// Met a jour la valeur de la vitesse en 
	// fonction de l'acceleration et du temps
	m_speed += m_acceleration * elapsedTime;

	m_timeToLive -= elapsedTime;

	// distance entre le projectile et sa destination
	// chemin le plus court
	Vector3f distance;
	distance.x = m_pos.x - m_destination.x;
	distance.y = m_pos.y - m_destination.y;
	distance.z = m_pos.z - m_destination.z;

	// calculer l'angle entre les 2 vecteurs
	// fix imprecision float
	float n = distance.Dot(speed) / (distance.Lenght() * speed.Lenght());
	if (n > 1)
		n = 1;
	else if (n < -1)
		n = -1;
	float angleA = acos(n);
	std::cout << angleA << std::endl;
	Vector3f axis = distance.Cross(speed);
	axis.Normalize();
	// rotation autour de laxe
	float rotation;
	if (abs(angleA) >= m_maxRot && abs(angleA) < PII - m_maxRot) {
		rotation = (angleA > 0) ? -m_maxRot : m_maxRot;
		rotation *= elapsedTime;
	}
	else
		rotation = angleA - PII;
	Quaternion q;
	q.FromAxis(rotation, axis);
	q.Normalise();

	m_rot = q * m_rot;
	m_rot.Normalise();
	
	// calcul la nouvelle position
	m_pos += speed * elapsedTime;
}