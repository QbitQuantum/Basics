/*
 * @implemented
 */
void abort()
{
	fflush(NULL);
	_fcloseall();
	raise(SIGABRT);
	_write(stderr->_file, msg, sizeof(msg)-1);
	exit(3);
}