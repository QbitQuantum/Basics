btHingeConstraint::btHingeConstraint(btRigidBody& rbA,btRigidBody& rbB, const btVector3& pivotInA,const btVector3& pivotInB,
									 btVector3& axisInA,btVector3& axisInB)
									 :btTypedConstraint(HINGE_CONSTRAINT_TYPE, rbA,rbB),
									 m_angularOnly(false),
									 m_enableAngularMotor(false)
{
	m_rbAFrame.getOrigin() = pivotInA;
	
	// since no frame is given, assume this to be zero angle and just pick rb transform axis
	btVector3 rbAxisA1 = rbA.getCenterOfMassTransform().getBasis().getColumn(0);

	btVector3 rbAxisA2;
	btScalar projection = axisInA.dot(rbAxisA1);
	if (projection >= 1.0f - SIMD_EPSILON) {
		rbAxisA1 = -rbA.getCenterOfMassTransform().getBasis().getColumn(2);
		rbAxisA2 = rbA.getCenterOfMassTransform().getBasis().getColumn(1);
	} else if (projection <= -1.0f + SIMD_EPSILON) {
		rbAxisA1 = rbA.getCenterOfMassTransform().getBasis().getColumn(2);
		rbAxisA2 = rbA.getCenterOfMassTransform().getBasis().getColumn(1);      
	} else {
		rbAxisA2 = axisInA.cross(rbAxisA1);
		rbAxisA1 = rbAxisA2.cross(axisInA);
	}

	m_rbAFrame.getBasis().setValue( rbAxisA1.getX(),rbAxisA2.getX(),axisInA.getX(),
									rbAxisA1.getY(),rbAxisA2.getY(),axisInA.getY(),
									rbAxisA1.getZ(),rbAxisA2.getZ(),axisInA.getZ() );

	btQuaternion rotationArc = shortestArcQuat(axisInA,axisInB);
	btVector3 rbAxisB1 =  quatRotate(rotationArc,rbAxisA1);
	btVector3 rbAxisB2 =  axisInB.cross(rbAxisB1);	
	
	m_rbBFrame.getOrigin() = pivotInB;
	m_rbBFrame.getBasis().setValue( rbAxisB1.getX(),rbAxisB2.getX(),-axisInB.getX(),
									rbAxisB1.getY(),rbAxisB2.getY(),-axisInB.getY(),
									rbAxisB1.getZ(),rbAxisB2.getZ(),-axisInB.getZ() );
	
	//start with free
	m_lowerLimit = btScalar(1e30);
	m_upperLimit = btScalar(-1e30);
	m_biasFactor = 0.3f;
	m_relaxationFactor = 1.0f;
	m_limitSoftness = 0.9f;
	m_solveLimit = false;

}