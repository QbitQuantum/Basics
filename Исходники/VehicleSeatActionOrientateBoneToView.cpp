Ang3 CVehicleSeatActionOrientateBoneToView::GetDesiredViewAngles(const Vec3& lookPos, const Vec3& aimPos) const
{
	Vec3 forwardDir = (aimPos - lookPos).GetNormalized();
	Vec3 upDir = Vec3(0.f, 0.f, 1.f);
	Vec3 sideDir = forwardDir.Cross(upDir);
	sideDir.Normalize();
	upDir = sideDir.Cross(forwardDir);
	upDir.Normalize();

	Matrix34 matrix;
	matrix.SetFromVectors(sideDir, forwardDir, upDir, Vec3(0.f, 0.f, 0.f));

	Ang3 lookAngles;
	lookAngles.SetAnglesXYZ(matrix);

	return lookAngles;
}