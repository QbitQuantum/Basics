bool PhysicsSystem::RaySphereCollision(const CollisionRay &r, const CollisionSphere &s, CollisionData *collisionData ){

	Vector3 relativePos = r.m_pos - s.m_pos;

	float relativeDist = relativePos.Length();

	float dot = Vector3::Dot(relativePos, r.m_dir);

	if(dot > s.m_radius) {
		return false;
	}

	float d = (s.m_radius * s.m_radius) - ((relativeDist * relativeDist) - (dot * dot));

	bool thisCollision = false;

	if(d > 0) {
		thisCollision = true;


		//I guess this would be put in collision data.... use this later :D
		//intersectpos = r.m_pos + (direction * (relativeDist - sqrt(d)));
	}

	return thisCollision;
}