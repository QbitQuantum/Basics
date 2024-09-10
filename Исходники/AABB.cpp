void AABB::TransformAsAABB(const Quat &transform)
{
	float3 newCenter = transform.Transform(CenterPoint());
	float3 newDir = Abs((transform.Transform(Size()) / 2.f));
	minPoint = newCenter - newDir;
	maxPoint = newCenter + newDir;
}