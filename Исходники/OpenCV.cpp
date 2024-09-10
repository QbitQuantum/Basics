cv::Scalar VectorToCVScalarColor(Vector4f vec)
{
	vec.Clamp(0, 1);
	// Scale to 255.
	vec *= 255.f;
	return cv::Scalar(vec.z, vec.y, vec.x, vec.w);
}