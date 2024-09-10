void	neb::glsl::attrib::disable()
{
	glDisableVertexAttribArray(o_);

	checkerror("glDisableVertexAttribArray");
}