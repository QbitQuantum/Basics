//----------------------------------------------------------------------------
void CameraActor::LookAt(const APoint &pos)
{
	APoint localPos = LocalTransform.GetTranslate();
	AVector dir = pos - localPos;

	float length = dir.Normalize();
	if (length > 0.0f)
	{
		AVector right = dir.UnitCross(AVector::UNIT_Z);
		AVector up = right.UnitCross(dir);

		LocalTransform.SetRotate(HMatrix(right, dir, up, AVector::ZERO, true));
	}
}