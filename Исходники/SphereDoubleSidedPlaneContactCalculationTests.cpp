void doSphereDoubleSidedPlaneTest(std::shared_ptr<SphereShape> sphere,
								  const Quaterniond& sphereQuat,
								  const Vector3d& sphereTrans,
								  std::shared_ptr<DoubleSidedPlaneShape> plane,
								  const Quaterniond& planeQuat,
								  const Vector3d& planeTrans,
								  bool expectedIntersect,
								  const double& expectedDepth = 0 ,
								  const Vector3d& expectedNorm = Vector3d::Zero())
{
	using SurgSim::Math::Geometry::ScalarEpsilon;
	using SurgSim::Math::Geometry::DistanceEpsilon;

	std::shared_ptr<ShapeCollisionRepresentation> planeRep =
		std::make_shared<ShapeCollisionRepresentation>("Collision Plane");
	planeRep->setShape(plane);
	planeRep->setLocalPose(SurgSim::Math::makeRigidTransform(planeQuat, planeTrans));

	std::shared_ptr<ShapeCollisionRepresentation> sphereRep =
		std::make_shared<ShapeCollisionRepresentation>("Collision Sphere");
	sphereRep->setShape(sphere);
	sphereRep->setLocalPose(SurgSim::Math::makeRigidTransform(sphereQuat, sphereTrans));

	SphereDoubleSidedPlaneContact calcNormal;
	std::shared_ptr<CollisionPair> pair = std::make_shared<CollisionPair>(sphereRep, planeRep);

	// Again this replicates the way this is calculated in the contact calculation just with different
	// starting values
	Vector3d sphereLocalNormal = sphereQuat.inverse() * expectedNorm;
	Vector3d spherePenetration = -sphereLocalNormal * sphere->getRadius();
	Vector3d planePenetration = -sphereLocalNormal * (sphere->getRadius() - expectedDepth);
	planePenetration = (sphereQuat * planePenetration) + sphereTrans;
	planePenetration = planeQuat.inverse() * (planePenetration - planeTrans);

	calcNormal.calculateContact(pair);
	if (expectedIntersect)
	{
		ASSERT_TRUE(pair->hasContacts());
		std::shared_ptr<Contact> contact = pair->getContacts().front();
		EXPECT_NEAR(expectedDepth, contact->depth, 1e-10);
		EXPECT_TRUE(eigenEqual(expectedNorm, contact->normal));
		EXPECT_TRUE(contact->penetrationPoints.first.rigidLocalPosition.hasValue());
		EXPECT_TRUE(contact->penetrationPoints.second.rigidLocalPosition.hasValue());
		EXPECT_TRUE(eigenEqual(spherePenetration,
							   contact->penetrationPoints.first.rigidLocalPosition.getValue()));
		EXPECT_TRUE(eigenEqual(planePenetration,
							   contact->penetrationPoints.second.rigidLocalPosition.getValue()));
	}
	else
	{
		EXPECT_FALSE(pair->hasContacts());
	}
}