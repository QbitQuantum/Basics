void doCapsuleSphereTest(double capsuleHeight, double capsuleRadius,
						 const Vector3d& capsulePosition, const Quaterniond& capsuleQuat,
						 double sphereRadius, const Vector3d& spherePosition, const Quaterniond& sphereQuat,
						 bool hasContacts, double depth,
						 const Vector3d& sphereProjection = Vector3d::Zero(),
						 const Vector3d& expectedNorm = Vector3d::Zero())
{
	std::shared_ptr<CollisionPair> pair = std::make_shared<CollisionPair>(
		makeCapsuleRepresentation(capsuleHeight, capsuleRadius, capsuleQuat, capsulePosition),
		makeSphereRepresentation(sphereRadius, sphereQuat, spherePosition));

	CapsuleSphereDcdContact calc;
	calc.calculateContact(pair);
	EXPECT_EQ(hasContacts, pair->hasContacts());

	if (pair->hasContacts())
	{
		std::shared_ptr<Contact> contact(pair->getContacts().front());

		EXPECT_TRUE(eigenEqual(expectedNorm, contact->normal));
		EXPECT_NEAR(depth, contact->depth, SurgSim::Math::Geometry::DistanceEpsilon);
		EXPECT_TRUE(contact->penetrationPoints.first.rigidLocalPosition.hasValue());
		EXPECT_TRUE(contact->penetrationPoints.second.rigidLocalPosition.hasValue());

		Vector3d capsuleLocalNormal = capsuleQuat.inverse() * expectedNorm;
		Vector3d penetrationPoint0(sphereProjection - capsuleLocalNormal * capsuleRadius);
		Vector3d sphereLocalNormal = sphereQuat.inverse() * expectedNorm;
		Vector3d penetrationPoint1(sphereLocalNormal * sphereRadius);
		EXPECT_TRUE(eigenEqual(penetrationPoint0, contact->penetrationPoints.first.rigidLocalPosition.getValue()));
		EXPECT_TRUE(eigenEqual(penetrationPoint1, contact->penetrationPoints.second.rigidLocalPosition.getValue()));
	}
}