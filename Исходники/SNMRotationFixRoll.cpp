/**
*  @brief
*    Called when the scene node modifier needs to be updated
*/
void SNMRotationFixRoll::OnUpdate()
{
	// Get the transform of the owner scene node
	Transform3 &cTransform = GetSceneNode().GetTransform();

	/*
	// This will 'flat' the rotation for example for an up-vector of '0 1 0' on the xz-plane
	Vector3    vLocalY = cTransform.GetRotation()*UpVector.Get();
	Quaternion qQuat   = vLocalY.GetRotationTo(UpVector.Get());
	cTransform.SetRotation(qQuat*cTransform.GetRotation());
	*/
	Matrix3x3 mRot;
	mRot.LookAt(cTransform.GetPosition(), cTransform.GetPosition() - cTransform.GetRotation().GetZAxis(), UpVector.Get());
	Quaternion qQ = mRot;
	qQ.UnitInvert();
	if (Speed > 0.0f)
		qQ.Slerp(cTransform.GetRotation(), qQ, Timing::GetInstance()->GetTimeDifference()*Speed);
	cTransform.SetRotation(qQ);
}