//----------------------------------------------------------------------------------------
void CSkeletalObject::SetScaleRotationPosition(float ScaleX, float ScaleY, float ScaleZ, float Roll, float Pitch, float Yaw, float OffsetX, float OffsetY, float OffsetZ)
{
	if (IsLoaded())
	{
		XMMATRIX LocalToWorldNormals = XMMatrixRotationRollPitchYaw(Pitch, Yaw, Roll);
		XMMATRIX LocalToWorld = XMMatrixScaling(ScaleX, ScaleY, ScaleZ) *
			LocalToWorldNormals *
			XMMatrixTranslation(OffsetX, OffsetY, OffsetZ);
		m_pRenderObject->SetLocalToWorld(LocalToWorld, LocalToWorldNormals);
	}
}