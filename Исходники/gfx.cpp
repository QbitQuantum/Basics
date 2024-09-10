void Renderer::screenPosToDirection(const Common::Point screen, float &pitch, float &heading) {
	double x, y, z;

	// Screen coords to 3D coords
	gluUnProject(screen.x, kOriginalHeight - screen.y, 0.9, _cubeModelViewMatrix, _cubeProjectionMatrix, (GLint *)_cubeViewport, &x, &y, &z);

	// 3D coords to polar coords
	Math::Vector3d v = Math::Vector3d(x, y, z);
	v.normalize();

	Math::Vector2d horizontalProjection = Math::Vector2d(v.x(), v.z());
	horizontalProjection.normalize();

	pitch = 90 - Math::Angle::arcCosine(v.y()).getDegrees();
	heading = Math::Angle::arcCosine(horizontalProjection.getY()).getDegrees();

	if (horizontalProjection.getX() > 0.0)
		heading = 360 - heading;
}