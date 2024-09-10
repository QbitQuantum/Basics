void SimpleCameraModel::draw() {
	if (!ModelerDrawState::Instance()->showMarkers) { return; }

	Vec3f position, lookAt, up;
	float fov;
	toVectors(position, lookAt, up, fov);
	Vec3f direction = lookAt - position;
	direction.normalize();
	Vec3f side = direction ^ up;
	side.normalize();
	float h = tan(fov * M_PI / 360);
	side *= h; 
	up.normalize();
	up *= h * aspectRatio;

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	glColor3i(1,0,0);
	glLineWidth(2);

	Vec3f topLeft = position + direction - side + up,
		topRight = position + direction + side + up,
		bottomLeft = position + direction - side - up,
		bottomRight = position + direction + side - up;
	glBegin(GL_LINES);
		position.glVertex(); topLeft.glVertex();
		position.glVertex(); topRight.glVertex();
		position.glVertex(); bottomLeft.glVertex();
		position.glVertex(); bottomRight.glVertex();
	glEnd();

	glBegin(GL_LINE_LOOP);
		topLeft.glVertex();
		topRight.glVertex();
		bottomRight.glVertex();
		bottomLeft.glVertex();
	glEnd();

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}