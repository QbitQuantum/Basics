int execs_common(const char *path, const char *args, char *const envp[], char *buf)
{
	int argc=args_fsa(args,NULL,NULL);
	char *argv[argc+1];
	args_fsa(args,argv,buf);
	if (path)
		return execve(path, argv, envp);
	else
		return execvpe(argv[0], argv, envp);
}