// We are going to override (is that the right word?) the draw()
// method of ModelerView to draw out RobotArm
void RobotArm::draw()
{
	/* pick up the slider values */

	float theta = VAL( BASE_ROTATION );
	float phi = VAL( LOWER_TILT );
	float psi = VAL( UPPER_TILT );
	float cr = VAL( CLAW_ROTATION );
	float h1 = VAL( BASE_LENGTH );
	float h2 = VAL( LOWER_LENGTH );
	float h3 = VAL( UPPER_LENGTH );
	float pc = VAL( PARTICLE_COUNT );

    // This call takes care of a lot of the nasty projection 
    // matrix stuff
    ModelerView::draw();

    // Save the camera transform that was applied by
    // ModelerView::draw() above.
    // While we're at it, save an inverted copy of this matrix.  We'll
    // need it later.
    Mat4f matCam = glGetMatrix( GL_MODELVIEW_MATRIX );
    matCamInverse = matCam.inverse();



	static GLfloat lmodel_ambient[] = {0.4,0.4,0.4,1.0};

	// define the model

	ground(-0.2);

	base(0.8);

    glTranslatef( 0.0, 0.8, 0.0 );			// move to the top of the base
    glRotatef( theta, 0.0, 1.0, 0.0 );		// turn the whole assembly around the y-axis. 
	rotation_base(h1);						// draw the rotation base

    glTranslatef( 0.0, h1, 0.0 );			// move to the top of the base
	glPushMatrix();
			glTranslatef( 0.5, h1, 0.6 );	
	glPopMatrix();
    glRotatef( phi, 0.0, 0.0, 1.0 );		// rotate around the z-axis for the lower arm
	glTranslatef( -0.1, 0.0, 0.4 );
	lower_arm(h2);							// draw the lower arm

    glTranslatef( 0.0, h2, 0.0 );			// move to the top of the lower arm
    glRotatef( psi, 0.0, 0.0, 1.0 );		// rotate  around z-axis for the upper arm
	upper_arm(h3);							// draw the upper arm

	glTranslatef( 0.0, h3, 0.0 );
	glRotatef( cr, 0.0, 0.0, 1.0 );

	Mat4f mvMatrix = glGetMatrix(GL_MODELVIEW_MATRIX);
	Vec4f clawEmitPos = matCamInverse * mvMatrix * Vec4f(0.0, 0.0, 0.0, 1.0);
	if (ps != NULL)
	{
		Vec3f clawPos = Vec3f(clawEmitPos[0], clawEmitPos[1], clawEmitPos[2]);
		ps->setEmitterPosition(clawPos, 1);
	}
	claw(1.0);




	//*** DON'T FORGET TO PUT THIS IN YOUR OWN CODE **/
	endDraw();
}