int dotest(struct starpu_disk_ops *ops, char *base)
{
	int *A, *C;

	/* Initialize StarPU with default configuration */
	int ret = starpu_init(NULL);

	if (ret == -ENODEV) goto enodev;

	/* Initialize path and name */
	const char *name_file_start = "STARPU_DISK_COMPUTE_DATA_";
	const char *name_file_end = "STARPU_DISK_COMPUTE_DATA_RESULT_";

	char * path_file_start = malloc(strlen(base) + 1 + strlen(name_file_start) + 1);
	strcpy(path_file_start, base);
	strcat(path_file_start, "/");
	strcat(path_file_start, name_file_start);

	char * path_file_end = malloc(strlen(base) + 1 + strlen(name_file_end) + 1);
	strcpy(path_file_end, base);
	strcat(path_file_end, "/");
	strcat(path_file_end, name_file_end);

	/* register a disk */
	int new_dd = starpu_disk_register(ops, (void *) base, 1024*1024*1);
	/* can't write on /tmp/ */
	if (new_dd == -ENOENT) goto enoent;

	unsigned dd = (unsigned) new_dd;

	/* allocate two memory spaces */
	starpu_malloc_flags((void **)&A, NX*sizeof(int), STARPU_MALLOC_COUNT);
	starpu_malloc_flags((void **)&C, NX*sizeof(int), STARPU_MALLOC_COUNT);

	FPRINTF(stderr, "TEST DISK MEMORY \n");

	unsigned int j;
	/* you register them in a vector */
	for(j = 0; j < NX; ++j)
	{
		A[j] = j;
		C[j] = 0;
	}

	/* you create a file to store the vector ON the disk */
	FILE * f = fopen(path_file_start, "wb+");
	if (f == NULL)
		goto enoent2;

	/* store it in the file */
	fwrite(A, sizeof(int), NX, f);

	/* close the file */
	fclose(f);

	int descriptor = open(path_file_start, O_RDWR);
#ifdef STARPU_HAVE_WINDOWS
	_commit(descriptor);
#else
	fsync(descriptor);
#endif
	close(descriptor);

	/* create a file to store result */
	f = fopen(path_file_end, "wb+");
	if (f == NULL)
		goto enoent2;

	/* replace all datas by 0 */
	fwrite(C, sizeof(int), NX, f);

	/* close the file */
	fclose(f);

        descriptor = open(path_file_end, O_RDWR);
#ifdef STARPU_HAVE_WINDOWS
        _commit(descriptor);
#else
        fsync(descriptor);
#endif
	close(descriptor);

	/* And now, you want to use your datas in StarPU */
	/* Open the file ON the disk */
	void * data = starpu_disk_open(dd, (void *) name_file_start, NX*sizeof(int));
	void * data_result = starpu_disk_open(dd, (void *) name_file_end, NX*sizeof(int));

	starpu_data_handle_t vector_handleA, vector_handleC;

	/* register vector in starpu */
	starpu_vector_data_register(&vector_handleA, dd, (uintptr_t) data, NX, sizeof(int));

	/* and do what you want with it, here we copy it into an other vector */
	starpu_vector_data_register(&vector_handleC, dd, (uintptr_t) data_result, NX, sizeof(int));

	starpu_data_cpy(vector_handleC, vector_handleA, 0, NULL, NULL);

	/* free them */
	starpu_data_unregister(vector_handleA);
	starpu_data_unregister(vector_handleC);

	/* close them in StarPU */
	starpu_disk_close(dd, data, NX*sizeof(int));
	starpu_disk_close(dd, data_result, NX*sizeof(int));

	/* check results */
	f = fopen(path_file_end, "rb+");
	if (f == NULL)
		goto enoent2;
	/* take datas */
	fread(C, sizeof(int), NX, f);

	/* close the file */
	fclose(f);

	int try = 1;
	for (j = 0; j < NX; ++j)
		if (A[j] != C[j])
		{
			FPRINTF(stderr, "Fail A %d != C %d \n", A[j], C[j]);
			try = 0;
		}