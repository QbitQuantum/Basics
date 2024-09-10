/**
*  @brief
*    Constructor
*/
JointUniversal::JointUniversal(PLPhysics::World &cWorld, PLPhysics::Body *pParentBody, PLPhysics::Body *pChildBody,
							   const Vector3 &vPivotPoint, const Vector3 &vPinDir1, const Vector3 &vPinDir2) :
	PLPhysics::JointUniversal(cWorld, static_cast<World&>(cWorld).CreateJointImpl(), pParentBody, pChildBody, vPivotPoint, vPinDir1, vPinDir2)
{
	// Deactivate the physics simulation if required
	const bool bSimulationActive = cWorld.IsSimulationActive();
	if (bSimulationActive)
		cWorld.SetSimulationActive(false);

	// Get the Newton physics world
	Newton::NewtonWorld *pNewtonWorld = static_cast<World&>(cWorld).GetNewtonWorld();

	// Flush assigned bodies (MUST be done before creating the joint!)
	if (pParentBody)
		static_cast<BodyImpl&>(pParentBody->GetBodyImpl()).Flush();
	if (pChildBody)
		static_cast<BodyImpl&>(pChildBody ->GetBodyImpl()).Flush();

	// Get the Newton physics parent and child bodies
	const Newton::NewtonBody *pNewtonParentBody = pParentBody ? static_cast<BodyImpl&>(pParentBody->GetBodyImpl()).GetNewtonBody() : nullptr;
	const Newton::NewtonBody *pNewtonChildBody  = pChildBody  ? static_cast<BodyImpl&>(pChildBody ->GetBodyImpl()).GetNewtonBody() : nullptr;


	// [TODO] ??
	/*
	if (pNewtonParentBody)
		NewtonBodySetUserData(pNewtonParentBody, nullptr);
	if (pNewtonChildBody)
		NewtonBodySetUserData(pNewtonChildBody, nullptr);
	*/


	// Get body initial transform matrix
	if (pParentBody) {
		// Get transform matrix
		Quaternion qQ;
		pParentBody->GetRotation(qQ);
		Vector3 vPos;
		pParentBody->GetPosition(vPos);
		Matrix3x4 mTrans;
		mTrans.FromQuatTrans(qQ, vPos);

		// And transform the initial joint anchor into the body object space
		mTrans.Invert();
		m_vLocalAnchor = mTrans*vPivotPoint;
	}

	// Create the Newton physics joint
	Newton::NewtonJoint *pNewtonJoint = NewtonConstraintCreateUniversal(pNewtonWorld, m_vPivotPoint, m_vPinDir1,
																		m_vPinDir2, pNewtonChildBody, pNewtonParentBody);

	// Set Newton universal callback function
	NewtonUniversalSetUserCallback(pNewtonJoint, JointUserCallback);

	// Initialize the Newton physics joint
	static_cast<JointImpl&>(GetJointImpl()).InitializeNewtonJoint(*this, *pNewtonJoint);

	// Reactivate the physics simulation if required
	if (bSimulationActive)
		cWorld.SetSimulationActive(bSimulationActive);
}