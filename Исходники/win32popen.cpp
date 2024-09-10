/*
 * Wrapper for fclose() to use for popen* files, so we can retrieve the
 * exit code for the child process and return as a result of the close.
 *
 * This function uses the _PyPopenProcs dictionary in order to map the
 * input file pointer to information about the process that was
 * originally created by the popen* call that created the file pointer.
 * The dictionary uses the file pointer as a key (with one entry
 * inserted for each file returned by the original popen* call) and a
 * single list object as the value for all files from a single call.
 * The list object contains the Win32 process handle at [0], and a file
 * count at [1], which is initialized to the total number of file
 * handles using that list.
 *
 * This function closes whichever handle it is passed, and decrements
 * the file count in the dictionary for the process handle pointed to
 * by this file.  On the last close (when the file count reaches zero),
 * this function will wait for the child process and then return its
 * exit code as the result of the close() operation.  This permits the
 * files to be closed in any order - it is always the close() of the
 * final handle that will return the exit code.
 */
static int _PyPclose(FILE *file)
{
	int result;
	DWORD exit_code;
	HANDLE hProcess;
	PyObject *procObj, *hProcessObj, *intObj, *fileObj;
	long file_count;
   
	/* Close the file handle first, to ensure it can't block the
	 * child from exiting if it's the last handle.
	 */
	result = fclose(file);

	if (_PyPopenProcs) {
		CEnterLeavePython _celp;
		if ((fileObj = PyLong_FromVoidPtr(file)) != NULL &&
		    (procObj = PyDict_GetItem(_PyPopenProcs,
					      fileObj)) != NULL &&
		    (hProcessObj = PyList_GetItem(procObj,0)) != NULL &&
		    (intObj = PyList_GetItem(procObj,1)) != NULL) {

			hProcess = PyLong_AsVoidPtr(hProcessObj);
			file_count = PyInt_AsLong(intObj);

			if (file_count > 1) {
				/* Still other files referencing process */
				file_count--;
				PyList_SetItem(procObj,1,
					       PyInt_FromLong(file_count));
			} else {
				Py_BEGIN_ALLOW_THREADS
				/* Last file for this process */
				if (result != EOF &&
				    WaitForSingleObject(hProcess, INFINITE) != WAIT_FAILED &&
				    GetExitCodeProcess(hProcess, &exit_code)) {
					/* Possible truncation here in 16-bit environments, but
					 * real exit codes are just the lower byte in any event.
					 */
					result = exit_code;
				} else {
					/* Indicate failure - this will cause the file object
					 * to raise an I/O error and translate the last Win32
					 * error code from errno.  We do have a problem with
					 * last errors that overlap the normal errno table,
					 * but that's a consistent problem with the file object.
					 */
					if (result != EOF) {
						/* If the error wasn't from the fclose(), then
						 * set errno for the file object error handling.
						 */
						errno = GetLastError();
					}
					result = -1;
				}
				/* Free up the native handle at this point */
				CloseHandle(hProcess);
				Py_END_ALLOW_THREADS
			}

			/* Remove this file pointer from dictionary */
			PyDict_DelItem(_PyPopenProcs, fileObj);

			if (PyDict_Size(_PyPopenProcs) == 0) {
				Py_DECREF(_PyPopenProcs);
				_PyPopenProcs = NULL;
			}

		} /* if object retrieval ok */

		Py_XDECREF(fileObj);
	} /* if _PyPopenProcs */