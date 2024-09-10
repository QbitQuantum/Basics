static OBB obbApproximation(const ViewFrustum& frustum) noexcept
{
	using std::tanf;
	const float yHalfRadAngle = (frustum.verticalFov() / 2.0f) * sfz::DEG_TO_RAD();
	const float xHalfRadAngle = frustum.aspectRatio() * yHalfRadAngle;
	const float nearMFar = frustum.far() - frustum.near();
	return OBB{frustum.pos() + frustum.dir() * (frustum.near() + (nearMFar / 2.0f)),
	           cross(frustum.up(), frustum.dir()), frustum.up(), frustum.dir(),
	           frustum.far() * tanf(xHalfRadAngle) * 2.0f, frustum.far() * tanf(yHalfRadAngle) * 2.0f, nearMFar};
}