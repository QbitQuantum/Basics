int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("GL interop");
	glutIconifyWindow();
	glutDisplayFunc(computeVBO);
	glutIdleFunc(computeVBO);

	initVBO();

	CreateContext();
	if(!context)
	{
		std::cerr << "Failed to create OpenCL context." << std::endl;
		return EXIT_FAILURE;
	}

	CreateCommandQueue();
	if(!commandQueue)
	{
		Cleanup();
		return EXIT_FAILURE;
	}

	CreateProgram();
	if(!program)
	{
		Cleanup();
		return EXIT_FAILURE;
	}

	kernel = clCreateKernel(program, "init_vbo_kernel", NULL);
	if(!kernel)
	{
		std::cerr << "Failed to create kernel" << std::endl;
		Cleanup();
		return EXIT_FAILURE;
	}

	if (!CreateMemObjects())
	{
		Cleanup();
		return EXIT_FAILURE;
	}

	glutMainLoop();

	std::cout << std::endl;
	std::cout << "Executed program succesfully." << std::endl;
	Cleanup();
}