Point2f Reprojector::compute_plane_size(float depth)
{
    float width = FOV_WIDTH * (depth / FOV_DEPTH);
    float height = width / 4 * 3;
	return Point2f(width, height);
}