void gkAuxRenderer::AuxRenderSkeleton( const Vec3& from, const Vec3& to, ColorF& color /*= ColorF(1.0,1.0,1.0,1.0)*/, float radius /*= 0.05f*/, bool ignoreZ /*= false */ )
{
	Vec3 dir = to - from;
	Vec3 dirInPlane = Vec3::CreateProjection(Vec3(0,0,1), dir.GetNormalized());
	if (dirInPlane.IsEquivalent(Vec3(0,0,0)))
	{
		dirInPlane = Vec3::CreateProjection(Vec3(1,0,0), dir.GetNormalized());
	}

	float len = dir.GetLength();
	dirInPlane.Normalize();
	dirInPlane *= radius * len;

	Vec3 dirInPlane1 = dirInPlane.GetRotated(dir.GetNormalized(), DEG2RAD(120.0f));
	Vec3 dirInPlane2 = dirInPlane.GetRotated(dir.GetNormalized(), DEG2RAD(-120.0f));

	Vec3 jointPt = from + dir.GetNormalized() * len * 0.8f;

	AuxRender3DLine(from, jointPt + dirInPlane, color, true);
	AuxRender3DLine(from, jointPt + dirInPlane1, color, true);
	AuxRender3DLine(from, jointPt + dirInPlane2, color, true);

	AuxRender3DLine(to, jointPt + dirInPlane, ColorF(1,0,0,1), true);
	AuxRender3DLine(to, jointPt + dirInPlane1, ColorF(1,0,0,1), true);
	AuxRender3DLine(to, jointPt + dirInPlane2, ColorF(1,0,0,1), true);

	AuxRender3DLine(jointPt + dirInPlane, jointPt + dirInPlane2, ColorF(1,0,0,1), true);
	AuxRender3DLine(jointPt + dirInPlane1, jointPt + dirInPlane2, ColorF(1,0,0,1), true);
	AuxRender3DLine(jointPt + dirInPlane, jointPt + dirInPlane1, ColorF(1,0,0,1), true);



}