/* ---------------------------------------------------------------------------- */
int main(int argc, char **argv)
{
	struct aiLogStream stream;

	glutInitWindowSize(900,600);
	glutInitWindowPosition(100,100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	glutCreateWindow("Assimp - Very simple OpenGL sample");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	/* get a handle to the predefined STDOUT log stream and attach
	   it to the logging system. It remains active for all further
	   calls to aiImportFile(Ex) and aiApplyPostProcessing. */
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
	aiAttachLogStream(&stream);

	/* ... same procedure, but this stream now writes the
	   log messages to assimp_log.txt */
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE,"assimp_log.txt");
	aiAttachLogStream(&stream);

	/* the model name can be specified on the command line. If none
	  is specified, we try to locate one of the more expressive test 
	  models from the repository (/models-nonbsd may be missing in 
	  some distributions so we need a fallback from /models!). */
	if( 0 != loadasset( argc >= 2 ? argv[1] : "X/dwarf.x")) {
		if( argc != 1 || (0 != loadasset( "X/dwarf.x") && 0 != loadasset( "X/Testwuson.X"))) { 
			return -1;
		}
	}

	glClearColor(0.1f,0.1f,0.1f,1.f);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);    /* Uses default lighting parameters */

	glEnable(GL_DEPTH_TEST);

	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);

	/* XXX docs say all polygons are emitted CCW, but tests show that some aren't. */
	char * buf = 0;
	size_t sz = 0;
	if(_dupenv_s(&buf,&sz,"MODEL_IS_BROKEN"))
		glFrontFace(GL_CW);

	glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);

	glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();

	/* cleanup - calling 'aiReleaseImport' is important, as the library 
	   keeps internal resources until the scene is freed again. Not 
	   doing so can cause severe resource leaking. */
	aiReleaseImport(scene);

	/* We added a log stream to the library, it's our job to disable it
	   again. This will definitely release the last resources allocated
	   by Assimp.*/
	aiDetachAllLogStreams();
	return 0;
}