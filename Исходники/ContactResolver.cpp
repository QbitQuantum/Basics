	void ContactResolver::UpdateBodyPenetration(
		RigidBody* body, Contact& contact, int sign, 
		const Vector3D<Real>& relativePos, const Vector3D<Real>& linearChange, 
		const Vector3D<Real>& angularChange)
	{
		UNUSED(body)
		Vector3D<Real> deltaPosition = linearChange + angularChange.CrossProduct(relativePos);
		contact.m_penetration += deltaPosition.Dot(contact.m_contactNormal) * sign;
	}