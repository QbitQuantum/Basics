/**
 * ray triangle intersection
 */
bool UMTriangle::intersects(const UMRay& ray) const
{
	// 3 points
	const UMVec3d& v0 = mesh_->vertex_list()[vertex_index_.x];
	const UMVec3d& v1 = mesh_->vertex_list()[vertex_index_.y];
	const UMVec3d& v2 = mesh_->vertex_list()[vertex_index_.z];

	return intersects(v0, v1, v2, ray);
}