void myInit(void)
{	
	glClearColor(0.0,0.0,0.0,0.0);
	//------------------------------------------------------------Object & Texture
	readFile("/Users/jiharu/svn/594CM/gl_obj/obj/triangular/Shatter1.obj");
	loadTextures();
	
	//DEFINE NIGTHS in some INIT function..
	glEnable(GL_LIGHTING); //enable lighting
	glShadeModel (GL_SMOOTH); //GL_SMOOTH, GL_FLAT
#pragma mark -
#pragma mark light
	//------------------------------------------------------------Light
	//define the lighting model
	float ambient[] = {0.08, 0.08, 0.01, 1.0};
	float diffuse[] = {0.7, 0.7, 0.0, 1.0};
	float specular[] = {0.3, 0.3, 0.3, 1.0};
	
	glEnable(GL_LIGHT0); //turn on one of the lights
	//	glDisable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);	
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	
	//------------------------------------------------------------Spot Light 1, 2, & 3
	float spot_direction1[] = { 0.0, -1.0, 0.0 }; 
	float ambient1[] = {0.01, .2, 0.5, 1.0};
	float diffuse1[] = {0.01, 0.5, 0.5, 1.0};
	float specular1[] = {0.0, 0.3, 1.0, 1.0};
	
	glEnable(GL_LIGHT1); //turn on one of the lights
	//	glDisable(GL_LIGHT1);	
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);	
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
	
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5); 
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5); 
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2);
	glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);	// degrees
	glLightf (GL_LIGHT1, GL_SPOT_EXPONENT, 2.0);
	
	float spot_direction2[] = { 0.0, -1.0, 0.0 }; 	
	float ambient2[] = {0.9, 0.1, 0.01, 1.0};
	float diffuse2[] = {0.9, 0.5, 0.0, 1.0};
	float specular2[] = {1.0, 0.1, 0.1, 1.0};
	
	glEnable(GL_LIGHT2); //turn on one of the lights
	//	glDisable(GL_LIGHT2);	
	glLightfv(GL_LIGHT2, GL_AMBIENT, ambient2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);	
	glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);
	
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.5); 
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.8); 
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2);
	glLightf (GL_LIGHT2, GL_SPOT_CUTOFF, 45.0);	// degrees
	glLightf (GL_LIGHT2, GL_SPOT_EXPONENT, 1.0);
		
	float spot_direction3[] = { .5, -1.0, 0.0 }; 
	float ambient3[] = {0.5, 0.5, 0.5, 1.0};
	float diffuse3[] = {1.0, 1.0, 1.0, 1.0};
	float specular3[] = {1.0, 1.0, 1.0, 1.0};
	
	glEnable(GL_LIGHT3); //turn on one of the lights
	//	glDisable(GL_LIGHT2);	
	glLightfv(GL_LIGHT3, GL_AMBIENT, ambient3);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, diffuse3);	
	glLightfv(GL_LIGHT3, GL_SPECULAR, specular3);
	
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, spot_direction3);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.5); 
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.8); 
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.2);
	glLightf (GL_LIGHT3, GL_SPOT_CUTOFF, 45.0);	// degrees
	glLightf (GL_LIGHT3, GL_SPOT_EXPONENT, 2.0);
	
	#pragma mark material
	//------------------------------------------------------------material
	//define the material of the object
	float mat_shininess[] = { 50. };
	float mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
	float mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
	float mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float mat_emission[] = {1.0, 0.1, 0.1, 1.0};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular); 
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission); 
	
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClearAccum(0.0, 0.0, 0.0, 0.0);
	
	checkForGLErrors("clearInit");
}