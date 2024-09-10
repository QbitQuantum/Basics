void WatchMeProcess::VOnUpdate(unsigned long deltaMs)
{
    StrongActorPtr pTarget = MakeStrongPtr(g_pApp->m_pGame->VGetActor(m_target));
	StrongActorPtr pMe = MakeStrongPtr(g_pApp->m_pGame->VGetActor(m_me));

    shared_ptr<TransformComponent> pTargetTransform = MakeStrongPtr(pTarget->GetComponent<TransformComponent>(TransformComponent::g_Name));
    shared_ptr<TransformComponent> pMyTransform = MakeStrongPtr(pMe->GetComponent<TransformComponent>(TransformComponent::g_Name));

	if (!pTarget || !pMe || !pTargetTransform || !pMyTransform)
	{
		GCC_ERROR("This shouldn't happen");
		Fail();
	}

	Vec3 targetPos = pTargetTransform->GetPosition();
	Mat4x4 myTransform = pMyTransform->GetTransform();
	Vec3 myDir = myTransform.GetDirection();
	myDir = Vec3(0.0f, 0.0f, 1.0f);
	Vec3 myPos = pMyTransform->GetPosition();

	Vec3 toTarget = targetPos - myPos;
	toTarget.Normalize();

	float dotProduct = myDir.Dot(toTarget);
	Vec3 crossProduct = myDir.Cross(toTarget);

	float angleInRadians = acos(dotProduct);

	if (crossProduct.y < 0)
		angleInRadians = -angleInRadians;
	
	Mat4x4 rotation;
	rotation.BuildRotationY(angleInRadians);
	rotation.SetPosition(myPos);
	pMyTransform->SetTransform(rotation);
}