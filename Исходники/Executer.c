int makeDir(char* identifierPath, char* path) {
	/* Questa funzione crea la directory, se il path esiste. */

	char* fullPath = createFullPath(identifierPath, path);
	int returnCode = ALLOK;

	SEMAPHORE_TYPE pathSemaphore = getPathSemaphore(fullPath, sharedMemory);

	#ifndef _WIN32
		int n;
		if ((n = sem_Trywait(pathSemaphore)) == EAGAIN) {
			returnCode = TEMP_UNAVAIBLE;
		} else {
			if (mkdir(fullPath, 0755) != 0) {
				log_err("Error while making new directory.");
				returnCode = parseErrno(errno);
			}

			sem_Post(pathSemaphore);
		}
		sem_Close(pathSemaphore);
	#else
		if (TRYWaitForSingleObject(pathSemaphore) == WAIT_TIMEOUT) {
			returnCode = TEMP_UNAVAIBLE;
		} else {
			if (mkdir(fullPath) != 0) {
				log_err("Error while making new directory.");
				returnCode = parseErrno(errno);
			}

			RELEASESemaphore(pathSemaphore);
		}
		CLOSEHandle(pathSemaphore);
	#endif

	free(fullPath);
	return returnCode;
}