void
piglit_init(int argc, char **argv)
{
	piglit_require_extension("GL_ARB_vertex_program");

	glEnable(GL_VERTEX_PROGRAM_ARB);

	SRAND(17);
}