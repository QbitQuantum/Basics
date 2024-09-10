void __attribute__((noreturn)) run_xz( char **argv, char **envp ) {
	execve(XZ_BINARY, argv, envp);
	error(0, errno, "execution of "XZ_BINARY" binary failed");
	exit(EXIT_FAILURE);
}