void Aimbot::Aim()
{
	if (!pAimTarget || !LocalPlayer)
		return;

	Vec3 vHeadPos; 
	Vec3 vHeadPosLocal = *(Vec3*)(ImageBase + 0x74BF48); //Magic numbers galore~
	
	if (!pAimTarget->GetBoneOrigin(pAimTarget->m_head_id, vHeadPos))
		return;
	
	Vec3 vAimDirection = vHeadPos - vHeadPosLocal;

	vAimDirection.normalize();	

	float pitch = (atan2(vAimDirection.y, vAimDirection.magnitude2d_2()) * RAD);
	float yaw = (atan2(vAimDirection.x, vAimDirection.z) * RAD);
	
	LocalPlayer->m_pitch = pitch;
	LocalPlayer->m_yaw = -yaw;
}