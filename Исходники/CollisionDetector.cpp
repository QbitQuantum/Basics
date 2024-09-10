bool CollisionDetector::CylinderSphereCollision(PhysicsNode& p0, PhysicsNode& p1, CollisionData* data) {
	CollisionCylinder& cylinder = *(CollisionCylinder*)p0.GetCollisionVolume();
	CollisionSphere& sphere = *(CollisionSphere*)p1.GetCollisionVolume();

	Vector3 cylCenterVector = cylinder.GetEnd() - cylinder.GetStart();

	Vector3 pos1 = p1.GetPosition() - cylinder.GetStart();

	float distanceFactorFromEP1 = Vector3::Dot(p1.GetPosition() - cylinder.GetStart(), cylCenterVector) / Vector3::Dot(cylCenterVector, cylCenterVector);
	if(distanceFactorFromEP1 < 0) distanceFactorFromEP1 = 0;// clamp to endpoints if neccesary
	if(distanceFactorFromEP1 > 1) distanceFactorFromEP1 = 1;
	Vector3 closestPoint = cylinder.GetStart() + (cylCenterVector * distanceFactorFromEP1);

	Vector3 collisionVector = p1.GetPosition() - closestPoint;
	float distance = collisionVector.Length();
	Vector3 collisionNormal = collisionVector / distance;

	if(distance < sphere.GetRadius() + cylinder.GetRadius())
	{
	  //collision occurred. use collisionNormal to reflect sphere off cyl

		float factor = Vector3::Dot(p1.GetLinearVelocity(), collisionNormal);

		p1.SetLinearVelocity(p1.GetLinearVelocity() - (collisionNormal * factor * 0.8f));

		const float distSq = LengthSq(collisionNormal);

		//get the max distance before collision
		const float sumRadius = sphere.GetRadius() + cylinder.GetRadius();

		p1.SetPosition(p1.GetPosition() + Vector3(collisionNormal * (sumRadius - sqrtf(distSq))));
		return true;
	}
	return false;
}