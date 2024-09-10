/* Main entry point. */
int main(int argc, char *argv[])
{
	int ret;
	int sc;
	pthread_mutexattr_t ma;

	testdata_t *td;
	testdata_t alternativ;

	int do_fork;

	pid_t child_pr = 0, chkpid;
	int status;
	pthread_t child_th;

	long pshared, mf;

	/* Initialize output */
	output_init();

	/* Test system abilities */
	pshared = sysconf(_SC_THREAD_PROCESS_SHARED);
	mf = sysconf(_SC_MAPPED_FILES);

#if VERBOSE > 0
	output("Test starting\n");
	output("System abilities:\n");
	output(" TSH : %li\n", pshared);
	output(" MF  : %li\n", mf);
	if ((mf < 0) || (pshared < 0))
		output("Process-shared attributes won't be tested\n");
#endif

/**********
 * Allocate space for the testdata structure
 */
	if (mf < 0) {
		/* Cannot mmap a file (or not interested in this), we use an alternative method */
		td = &alternativ;
		pshared = -1;	/* We won't do this testing anyway */
#if VERBOSE > 0
		output("Testdata allocated in the process memory.\n");
#endif
	} else {
		/* We will place the test data in a mmaped file */
		char filename[] = "/tmp/mutex_trylock_2-1-XXXXXX";
		size_t sz;
		void *mmaped;
		int fd;
		char *tmp;

		/* We now create the temp files */
		fd = mkstemp(filename);
		if (fd == -1) {
			UNRESOLVED(errno,
				   "Temporary file could not be created");
		}

		/* and make sure the file will be deleted when closed */
		unlink(filename);

#if VERBOSE > 1
		output("Temp file created (%s).\n", filename);
#endif

		sz = (size_t) sysconf(_SC_PAGESIZE);

		tmp = calloc(1, sz);
		if (tmp == NULL) {
			UNRESOLVED(errno, "Memory allocation failed");
		}

		/* Write the data to the file.  */
		if (write(fd, tmp, sz) != (ssize_t) sz) {
			UNRESOLVED(sz, "Writting to the file failed");
		}

		free(tmp);

		/* Now we can map the file in memory */
		mmaped =
		    mmap(NULL, sz, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
		if (mmaped == MAP_FAILED) {
			UNRESOLVED(errno, "mmap failed");
		}

		td = (testdata_t *) mmaped;

		/* Our datatest structure is now in shared memory */
#if VERBOSE > 1
		output("Testdata allocated in shared memory.\n");
#endif
	}

/**********
 * For each test scenario, initialize the attributes and other variables.
 * Do the whole thing for each time to test.
 */
	for (sc = 0; sc < NSCENAR; sc++) {
#if VERBOSE > 1
		output("[parent] Preparing attributes for: %s\n",
		       scenarii[sc].descr);
#endif
		/* set / reset everything */
		do_fork = 0;
		ret = pthread_mutexattr_init(&ma);
		if (ret != 0) {
			UNRESOLVED(ret,
				   "[parent] Unable to initialize the mutex attribute object");
		}

		/* Set the mutex type */
		ret = pthread_mutexattr_settype(&ma, scenarii[sc].m_type);
		if (ret != 0) {
			UNRESOLVED(ret, "[parent] Unable to set mutex type");
		}
#if VERBOSE > 1
		output("[parent] Mutex type : %i\n", scenarii[sc].m_type);
#endif

		/* Set the pshared attributes, if supported */
		if ((pshared > 0) && (scenarii[sc].m_pshared != 0)) {
			ret =
			    pthread_mutexattr_setpshared(&ma,
							 PTHREAD_PROCESS_SHARED);
			if (ret != 0) {
				UNRESOLVED(ret,
					   "[parent] Unable to set the mutex process-shared");
			}
#if VERBOSE > 1
			output("[parent] Mutex is process-shared\n");
#endif
		}
#if VERBOSE > 1
		else {
			output("[parent] Mutex is process-private\n");
		}
#endif

		/* Tell whether the test will be across processes */
		if ((pshared > 0) && (scenarii[sc].fork != 0)) {
			do_fork = 1;
#if VERBOSE > 1
			output("[parent] Child will be a new process\n");
#endif
		}
#if VERBOSE > 1
		else {
			output("[parent] Child will be a new thread\n");
		}
#endif

/**********
 * Initialize the testdata_t structure with the previously defined attributes
 */
		/* Initialize the mutex */
		ret = pthread_mutex_init(&(td->mtx), &ma);
		if (ret != 0) {
			UNRESOLVED(ret, "[parent] Mutex init failed");
		}

		/* Initialize the other datas from the test structure */
		td->status = 0;

/**********
 * Proceed to the actual testing
 */
		/* Trylock the mutex twice before creating children */
		ret = pthread_mutex_trylock(&(td->mtx));
		if (ret != 0) {
			UNRESOLVED(ret, "[parent] Unable to trylock the mutex");
		}
		ret = pthread_mutex_trylock(&(td->mtx));

		if (scenarii[sc].m_type == PTHREAD_MUTEX_RECURSIVE) {
			if (ret != 0) {
				FAILED
				    ("Failed to pthread_mutex_trylock() twice a recursive mutex");
			}

			/* Unlock once so the count is "1" */
			ret = pthread_mutex_unlock(&(td->mtx));
			if (ret != 0) {
				UNRESOLVED(ret, "Failed to unlock the mutex");
			}
		} else if (ret == 0) {
			UNRESOLVED(-1,
				   "Main was able to pthread_mutex_trylock() twice without error");
		}

		/* Create the children */
		if (do_fork != 0) {
			/* We are testing across processes */
			child_pr = fork();
			if (child_pr == -1) {
				UNRESOLVED(errno, "[parent] Fork failed");
			}

			if (child_pr == 0) {
#if VERBOSE > 3
				output
				    ("[child] Child process is starting...\n");
#endif

				if (tf((void *)td) != NULL) {
					UNRESOLVED(-1,
						   "[child] Got an unexpected return value from test function");
				} else {
					/* We cannot use the PASSED macro here since it would terminate the output */
					exit(0);
				}
			}
			/* Only the parent process goes further */
		} else {	/* do_fork == 0 */

			/* We are testing across two threads */
			ret = pthread_create(&child_th, NULL, tf, td);
			if (ret != 0) {
				UNRESOLVED(ret,
					   "[parent] Unable to create the child thread.");
			}
		}

		/* Wait for the child to terminate */
		if (do_fork != 0) {
			/* We were testing across processes */
			ret = 0;
			chkpid = waitpid(child_pr, &status, 0);
			if (chkpid != child_pr) {
				output("Expected pid: %i. Got %i\n",
				       (int)child_pr, (int)chkpid);
				UNRESOLVED(errno, "Waitpid failed");
			}
			if (WIFSIGNALED(status)) {
				output("Child process killed with signal %d\n",
				       WTERMSIG(status));
				UNRESOLVED(-1, "Child process was killed");
			}

			if (WIFEXITED(status)) {
				ret = WEXITSTATUS(status);
			} else {
				UNRESOLVED(-1,
					   "Child process was neither killed nor exited");
			}

			if (ret != 0) {
				exit(ret);	/* Output has already been closed in child */
			}

		} else {	/* child was a thread */

			ret = pthread_join(child_th, NULL);
			if (ret != 0) {
				UNRESOLVED(ret,
					   "[parent] Unable to join the thread");
			}
		}

		/* Check the child status */
		if (td->status != EBUSY) {
			output("Unexpected return value: %d (%s)\n", td->status,
			       strerror(td->status));
			FAILED
			    ("pthread_mutex_trylock() did not return EBUSY in the child");
		}

		/* Unlock the mutex */
		ret = pthread_mutex_unlock(&(td->mtx));
		if (ret != 0) {
			FAILED
			    ("Failed to unlock the mutex -- count is broken?");
		}

		ret = pthread_mutex_unlock(&(td->mtx));
		if (ret == 0) {
			FAILED
			    ("Was able to unlock once more the mutex -- count is broken?");
		}

/**********
 * Destroy the data
 */
		ret = pthread_mutex_destroy(&(td->mtx));
		if (ret != 0) {
			UNRESOLVED(ret, "Failed to destroy the mutex");
		}

		ret = pthread_mutexattr_destroy(&ma);
		if (ret != 0) {
			UNRESOLVED(ret,
				   "Failed to destroy the mutex attribute object");
		}

	}			/* Proceed to the next scenario */

#if VERBOSE > 0
	output("Test passed\n");
#endif

	PASSED;
}