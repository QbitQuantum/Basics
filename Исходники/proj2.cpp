Point3D phongShade (float r, float g, float b, Point3D p, int f) {
	// Ambient is set as base color
	Point3D ambient(r, g, b);
	// Specular reflection
	double reflect = 50;
	// Light source
	Point3D light(lightHorz,lightVert, lightDepth);
	renderPixel(lightHorz, lightVert, 1.0, 0.0, 0.0);
	// Direction to viewer
	Point3D viewer(200, 200, 0);
	// Get face normal
	Point3D pa = points[faces[f].a];
	Point3D pb = points[faces[f].b];
	Point3D pc = points[faces[f].c];
	Point3D v = pa - pc;
	Point3D w = pa - pb;
	Point3D fNorm = v.cross(w);
	
	double centerX = getCenterInc('x');
	double centerY = getCenterInc('y');
	double centerZ = getCenterInc('z');
	
	Point3D centerP(centerX, centerY, centerZ); 
	
	if (fNorm.dot(centerP) > 0) {
		fNorm = fNorm * -1;
	}

	fNorm.normalize();
	
	// Get light direction
	light -= p;
	light.normalize();

	// Calculate diffuse factor
	double difScale = fNorm.dot(light);
	// Diffuse
	Point3D diffuse = ambient;
	diffuse = diffuse * max(0.0, difScale);
	diffuse = diffuse * 2;

	// Calculate reflected ray
	Point3D rbounce = fNorm;
	rbounce = rbounce * difScale;
	rbounce = rbounce * 2;
	rbounce -= light; 
	viewer -= p;
	rbounce.normalize();
	viewer.normalize();
	
	// Calculate specular factor
	double specScale = viewer.dot(rbounce);
	Point3D specular(.5,.5,.5);
	
	// Specular
	specular = specular * pow(max(0.0, specScale), reflect);

	Point3D phong;
	phong += diffuse;
	phong += specular;
	return phong;
}