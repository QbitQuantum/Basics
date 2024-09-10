bool setupStdio(Pid createdPid, Pid requesterPid, File_t *outStdin, File_t *outStdout, File_t *outStderr, File_t inStdin, File_t inStdout,File_t inStderr)
{
	uint32_t thisPid = GetPid();
	if (!createPipe(thisPid, requesterPid, createdPid, inStdin, outStdin, STDIN_FILENO)) return false;
	if (!createPipe(thisPid, requesterPid, createdPid, inStdout, outStdout, STDOUT_FILENO)) return false;
	if (!createPipe(thisPid, requesterPid, createdPid, inStderr, outStderr, STDERR_FILENO)) return false;

	return true;
}