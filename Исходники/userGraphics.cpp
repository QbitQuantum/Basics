void drawArrow2(Vector3F & location, Vector3F & direction, double headLength) 
{
	Vector3F zup; 
	zup << 0,0,1;
	
	Vector3F normedDirection = direction.normalized();
	
	// Note: We need to create a rotation such that the z-axis points in the direction of the 'direction' argument
	//       Thus, we can realize the rotation with a pure x-y axial rotation
	//       The rotation matrix of the rotated frame 'r' to the current frame 'c' (c_R_r) has special form.
	//       It's 3-rd column in particular has form: [ wy*sin(theta) -wx*sin(theta) (1- cos(theta))]'
	//       where theta , [wx wy 0] is the angle, axis of rotation
	
	// Find the rotation angle by comparing the z-axis of the current and rotated frame
	const double cosTheta = zup.dot(normedDirection);
	const double theta = acos(cosTheta);
	const double sinTheta = sin(theta);
	
	// Exploit the special form of the rotation matrix (explained above) for find the axis of rotation
	double rX, rY, rZ;
	if(theta > 0) {	
		rX = - normedDirection(1)/sinTheta;
		rY =   normedDirection(0)/sinTheta;
		rZ = 0;
	}
	else {
		rX = 0;
		rY = 0;
		rZ = 1;
	}
	
	// before calling this function, be sure glMatrixMode is GL_MODELVIEW and camera->applyView is called.
	glPushMatrix();
	glTranslatef(location(0), location(1), location(2));
	glRotated(RADTODEG * theta, rX, rY, rZ);
	
	double detail = 16;
	double headWidth = 0.01;
	double shaftLength = direction.norm();
	if (shaftLength > headLength) 
	{
		shaftLength -= headLength;
	}
	else 
	{
		headLength = shaftLength ;
		shaftLength = 0;
	}

	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0,shaftLength );
	glVertex3f(0.0, 0.0, 0.0);
	glEnd();	

	glTranslatef(0, 0, shaftLength);
	//Draw Arrowhead
	gluCylinder(frame->glPane->quadratic,headWidth,0.0f,headLength,detail,detail);
	
	//Draw Arrowhead Base
	gluDisk(frame->glPane->quadratic,0.0f,headWidth,detail,detail);
	
	glPopMatrix();
	
}