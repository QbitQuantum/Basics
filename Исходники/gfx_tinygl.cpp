void TinyGLRenderer::screenPosToDirection(const Common::Point screen, float &pitch, float &heading) {
	// Screen coords to 3D coords
	Math::Vector3d obj;
	Math::gluMathUnProject<float, int>(Math::Vector3d(screen.x, kOriginalHeight - screen.y, 0.9),
		_cubeModelViewMatrix, _cubeProjectionMatrix, _cubeViewport, obj);

	// 3D coords to polar coords
	obj.normalize();

	Math::Vector2d horizontalProjection = Math::Vector2d(obj.x(), obj.z());
	horizontalProjection.normalize();

	pitch = 90 - Math::Angle::arcCosine(obj.y()).getDegrees();
	heading = Math::Angle::arcCosine(horizontalProjection.getY()).getDegrees();

	if (horizontalProjection.getX() > 0.0)
		heading = 360 - heading;
}