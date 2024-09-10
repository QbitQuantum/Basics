/**
 * Configures verbosegc according to the parameters passed.
 * @param filename The name of the file or output stream to log to.
 * @param fileCount The number of files to log to.
 * @param iterations The number of gc cycles to log to each file.
 * @return true on success, false on failure
 */
bool
MM_VerboseManager::configureVerboseGC(OMR_VM *omrVM, char *filename, uintptr_t fileCount, uintptr_t iterations)
{
	MM_EnvironmentBase env(omrVM);

	MM_VerboseWriter *writer = NULL;

	disableWriters();

	WriterType type = parseWriterType(&env, filename, fileCount, iterations);

	writer = findWriterInChain(type);

	if (NULL != writer) {
		writer->reconfigure(&env, filename, fileCount, iterations);
	} else {

		writer = createWriter(&env, type, filename, fileCount, iterations);

		if(NULL == writer) {
			return false;
		}

		_writerChain->addWriter(writer);
	}

	writer->isActive(true);

	return true;
}