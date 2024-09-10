void GLFW_test2::_error_callback(int error, const char* description)
{
	fputs(description, stderr);
}