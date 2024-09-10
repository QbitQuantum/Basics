static void polarRectTo3dRect(const PolarRect &polarRect,
                              Math::Vector3d &topLeft, Math::Vector3d &topRight,
                              Math::Vector3d &bottomLeft, Math::Vector3d &bottomRight) {
	static const float scale = 50.0;

	Math::Vector3d direction = Scene::directionToVector(polarRect.centerPitch, 90.0 - polarRect.centerHeading) * scale;

	Math::Vector3d u = Math::Vector3d(direction.z(), 0.0, -direction.x());
	u.normalize();

	Math::Vector3d v = Math::Vector3d::crossProduct(direction, u);
	v.normalize();

	Math::Vector3d sizeU = u * polarRect.width  / 90.0 * scale;
	Math::Vector3d sizeV = v * polarRect.height / 90.0 * scale;

	topRight = direction + sizeV + sizeU;
	bottomRight = direction - sizeV + sizeU;
	bottomLeft = direction - sizeV - sizeU;
	topLeft = direction + sizeV - sizeU;
}