void glfw_error_callback (int error, const char* description) {
	fputs (description, stderr);
	gl_log_err ("%s\n", description);
}