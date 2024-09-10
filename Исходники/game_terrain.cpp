Vec3f GameTerrain::unproject(Vec3f win_pos, const Mat4f &modelview, const Mat4f &projection, const Rect &viewport)
{
	Mat4f matrix = projection;
	matrix = matrix * modelview;
	matrix.inverse();
	Vec4f v(
		2*(win_pos.x - (float)viewport.left)/(float)viewport.get_width() - 1,
		2*(win_pos.y - (float)(viewport.top))/(float)viewport.get_height() - 1,
		2*win_pos.z - 1,
		1.0f);
	Vec4f result = matrix * v;
	return Vec3f(result.x/result.w, result.y/result.w, result.z/result.w);
}