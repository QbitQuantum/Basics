// this function builds a projection matrix for rendering from the shadow's POV.
// First, it computes the appropriate z-range and sets an orthogonal projection.
// Then, it translates and scales it, so that it exactly captures the bounding box
// of the current frustum slice
float CShadowMap::ApplyCropMatrix(frustum &f)
{
	float shad_modelview[16];
	float shad_proj[16];
	float shad_crop[16];
	float shad_mvp[16];
	float maxX = -2000.0f;
    float maxY = -2000.0f;
	float maxZ;
    float minX =  2000.0f;
    float minY =  2000.0f;
	float minZ;

	matrix4<float> nv_mvp;
	vec4f transf;	
	
	// find the z-range of the current frustum as seen from the light
	// in order to increase precision
	glGetFloatv(GL_MODELVIEW_MATRIX, shad_modelview);
	nv_mvp.set_value(shad_modelview);
	
	// note that only the z-component is need and thus
	// the multiplication can be simplified
	// transf.z = shad_modelview[2] * f.point[0].x + shad_modelview[6] * f.point[0].y + shad_modelview[10] * f.point[0].z + shad_modelview[14];
	transf = nv_mvp*vec4f(f.point[0], 1.0f);
	minZ = -1000/*transf.z*/;
	maxZ = 1000/*transf.z*/;
	for(int i=1; i<8; i++)
	{
		transf = nv_mvp*vec4f(f.point[i], 1.0f);
		if(transf.z > maxZ) maxZ = transf.z;
		if(transf.z < minZ) minZ = transf.z;
	}
	// make sure all relevant shadow casters are included
	// note that these here are dummy objects at the edges of our scene
	for(int i=0; i<NUM_OBJECTS; i++)
	{
		transf = nv_mvp*vec4f(BSphere[i].center, 1.0f);
		if(transf.z + BSphere[i].radius > maxZ) maxZ = transf.z + BSphere[i].radius;
		//if(transf.z - BSphere[i].radius < minZ) minZ = transf.z - BSphere[i].radius;
	}
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// set the projection matrix with the new z-bounds
	// note the inversion because the light looks at the neg. z axis
	// gluPerspective(LIGHT_FOV, 1.0, maxZ, minZ); // for point lights
	glOrtho(-1.0, 1.0, -1.0, 1.0, -maxZ, -minZ);
	glGetFloatv(GL_PROJECTION_MATRIX, shad_proj);
	glPushMatrix();
	glMultMatrixf(shad_modelview);
	glGetFloatv(GL_PROJECTION_MATRIX, shad_mvp);
	glPopMatrix();

	// find the extends of the frustum slice as projected in light's homogeneous coordinates
	nv_mvp.set_value(shad_mvp);
	for(int i=0; i<8; i++)
	{
		transf = nv_mvp*vec4f(f.point[i], 1.0f);

		transf.x /= transf.w;
		transf.y /= transf.w;

		if(transf.x > maxX) maxX = transf.x;
		if(transf.x < minX) minX = transf.x;
		if(transf.y > maxY) maxY = transf.y;
		if(transf.y < minY) minY = transf.y;
	}

	float scaleX = 2.0f/(maxX - minX);
	float scaleY = 2.0f/(maxY - minY);
	float offsetX = -0.5f*(maxX + minX)*scaleX;
	float offsetY = -0.5f*(maxY + minY)*scaleY;

	// apply a crop matrix to modify the projection matrix we got from glOrtho.
	nv_mvp.make_identity();
	nv_mvp.element(0,0) = scaleX;
	nv_mvp.element(1,1) = scaleY;
	nv_mvp.element(0,3) = offsetX;
	nv_mvp.element(1,3) = offsetY;
	transpose(nv_mvp);
	nv_mvp.get_value(shad_crop);
	glLoadMatrixf(shad_crop);
	glMultMatrixf(shad_proj);

	return minZ;
}