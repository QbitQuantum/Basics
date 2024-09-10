int main(int argc, char **argv)
{
	int ret;
	unsigned part;
	double timing;
	double start, end;
	unsigned row, pos;
	unsigned ind;

	/* CSR matrix description */
	float *nzval;
	uint32_t nnz;
	uint32_t *colind;
	uint32_t *rowptr;
	
	/* Input and Output vectors */
	float *vector_in_ptr;
	float *vector_out_ptr;

	/*
	 *	Parse command-line arguments
	 */
	parse_args(argc, argv);

	/*
	 *	Launch StarPU
	 */
	ret = starpu_init(NULL);
	if (ret == -ENODEV)
		return 77;
	STARPU_CHECK_RETURN_VALUE(ret, "starpu_init");

	/*
	 *	Create a 3-band sparse matrix as input example
	 */
	nnz = 3*size-2;
	starpu_malloc((void **)&nzval, nnz*sizeof(float));
	starpu_malloc((void **)&colind, nnz*sizeof(uint32_t));
	starpu_malloc((void **)&rowptr, (size+1)*sizeof(uint32_t));
	assert(nzval && colind && rowptr);

	/* fill the matrix */
	for (row = 0, pos = 0; row < size; row++)
	{
		rowptr[row] = pos;

		if (row > 0)
		{
			nzval[pos] = 1.0f;
			colind[pos] = row-1;
			pos++;
		}
		
		nzval[pos] = 5.0f;
		colind[pos] = row;
		pos++;

		if (row < size - 1)
		{
			nzval[pos] = 1.0f;
			colind[pos] = row+1;
			pos++;
		}
	}

	STARPU_ASSERT(pos == nnz);

	rowptr[size] = nnz;
	
	/* initiate the 2 vectors */
	starpu_malloc((void **)&vector_in_ptr, size*sizeof(float));
	starpu_malloc((void **)&vector_out_ptr, size*sizeof(float));
	assert(vector_in_ptr && vector_out_ptr);

	/* fill them */
	for (ind = 0; ind < size; ind++)
	{
		vector_in_ptr[ind] = 2.0f;
		vector_out_ptr[ind] = 0.0f;
	}

	/*
	 *	Register the CSR matrix and the 2 vectors
	 */
	starpu_csr_data_register(&sparse_matrix, STARPU_MAIN_RAM, nnz, size, (uintptr_t)nzval, colind, rowptr, 0, sizeof(float));
	starpu_vector_data_register(&vector_in, STARPU_MAIN_RAM, (uintptr_t)vector_in_ptr, size, sizeof(float));
	starpu_vector_data_register(&vector_out, STARPU_MAIN_RAM, (uintptr_t)vector_out_ptr, size, sizeof(float));

	/*
	 *	Partition the CSR matrix and the output vector
	 */
	csr_f.nchildren = nblocks;
	vector_f.nchildren = nblocks;
	starpu_data_partition(sparse_matrix, &csr_f);
	starpu_data_partition(vector_out, &vector_f);

	/*
	 *	If we use OpenCL, we need to compile the SpMV kernel
	 */
#ifdef STARPU_USE_OPENCL
	compile_spmv_opencl_kernel();
#endif

	start = starpu_timing_now();

	/*
	 *	Create and submit StarPU tasks
	 */
	for (part = 0; part < nblocks; part++)
	{
		struct starpu_task *task = starpu_task_create();
		task->cl = &spmv_cl;
	
		task->handles[0] = starpu_data_get_sub_data(sparse_matrix, 1, part);
		task->handles[1] = vector_in;
		task->handles[2] = starpu_data_get_sub_data(vector_out, 1, part);
	
		ret = starpu_task_submit(task);
		if (STARPU_UNLIKELY(ret == -ENODEV))
		{
			FPRINTF(stderr, "No worker may execute this task\n");
			exit(0);
		}
	}

	starpu_task_wait_for_all();
	end = starpu_timing_now();

	/*
	 *	Unregister the CSR matrix and the output vector
	 */
	starpu_data_unpartition(sparse_matrix, STARPU_MAIN_RAM);
	starpu_data_unpartition(vector_out, STARPU_MAIN_RAM);

	/*
	 *	Unregister data
	 */
	starpu_data_unregister(sparse_matrix);
	starpu_data_unregister(vector_in);
	starpu_data_unregister(vector_out);

	/*
	 *	Display the result
	 */
	for (row = 0; row < STARPU_MIN(size, 16); row++)
	{
                FPRINTF(stdout, "%2.2f\t%2.2f\n", vector_in_ptr[row], vector_out_ptr[row]);
	}

	starpu_free(nzval);
	starpu_free(colind);
	starpu_free(rowptr);
	starpu_free(vector_in_ptr);
	starpu_free(vector_out_ptr);

	/*
	 *	Stop StarPU
	 */
	starpu_shutdown();

	timing = end - start;
	FPRINTF(stderr, "Computation took (in ms)\n");
	FPRINTF(stdout, "%2.2f\n", timing/1000);

	return 0;
}