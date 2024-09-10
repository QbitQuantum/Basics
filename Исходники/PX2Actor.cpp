//----------------------------------------------------------------------------
void Actor::SetFace(const AVector &dir, const AVector &uping)
{
	AVector right = dir.Cross(uping);
	right.Normalize();
	AVector up = right.Cross(dir);
	up.Normalize();

	Matrix3f matRot(right, dir, up, true);

	LocalTransform.SetRotate(matRot);
}