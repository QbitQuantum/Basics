//----------------------------------------------------------------------------
void BVSphere::Merge(const BoundingVolume* pBV)
{
	Vec3 dir = mCenter - pBV->GetCenter();
	Real distance = dir.Normalize();
	Vec3 myFar = mCenter + dir * mRadius;
	Vec3 otherFar = pBV->GetCenter() + dir * pBV->GetRadius();
	Real mydot = myFar.Dot(dir);
	Real otherdot = otherFar.Dot(dir);
	Vec3 mostFar0 = mydot > otherdot ? myFar : otherFar;

	dir = pBV->GetCenter() - mCenter;
	dir.Normalize();
	myFar = mCenter + dir * mRadius;
	otherFar = pBV->GetCenter() + dir * pBV->GetRadius();
	mydot = myFar.Dot(dir);
	otherdot = otherFar.Dot(dir);
	Vec3 mostFar1 = mydot > otherdot ? myFar : otherFar;

	mCenter = (mostFar0 + mostFar1) * .5f;
	mRadius = (mostFar0 - mostFar1).Length() * .5f;
}