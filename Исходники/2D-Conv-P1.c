void main(int argc, char **argv) {
	
	double start_t, end_t;
	
	int my_rank, p;
	complex A[512*512], B[512*512], C[512*512];

	/* initialize MPI */
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &p);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	/* Create MPI Datatype for Complex */
    const float nitems=2;
    int          blocklengths[2] = {1,1};
    MPI_Datatype types[2] = {MPI_FLOAT, MPI_FLOAT};
    MPI_Aint     offsets[2];

    offsets[0] = offsetof(complex, r);
    offsets[1] = offsetof(complex, i);

    MPI_Type_create_struct(nitems, blocklengths, offsets, types, &mpi_complex);
    MPI_Type_commit(&mpi_complex);
	
	/* Initialize Data*/
	if(my_rank == 0) {
		initialize_data(f1_name, A);
		initialize_data(f2_name, B);
		start_t = MPI_Wtime();
		dist_data(A, p);
		dist_data(B, p);
	} else {
		recv_data(A, p, my_rank);
		recv_data(B, p, my_rank);
	}
	
	/* 2D FFT on A */
	execute_fft(A, 1, p, my_rank);
	collect_data(A, p, my_rank);
	if(my_rank == 0) {
		transpose(A);
		dist_data(A, p);
	} else {
		recv_data(A, p, my_rank);
	}
	execute_fft(A, 1, p, my_rank);
	
	/* 2D FFT on B */
	execute_fft(B, 1, p, my_rank);
	collect_data(B, p, my_rank);
	if(my_rank == 0) {
		transpose(B);
		dist_data(B, p);
	} else {
		recv_data(B, p, my_rank);
	}
	execute_fft(B, 1, p, my_rank);
	
	/* Multiplication Step */
	execute_mm(A, B, C, p, my_rank);
	
	/* 2D FFT on C */
	execute_fft(C, -1, p, my_rank);
	collect_data(C, p, my_rank);
	if(my_rank == 0) {
		transpose(C);
		dist_data(C, p);
	} else {
		recv_data(C, p, my_rank);
	}
	execute_fft(C, -1, p, my_rank);
	collect_data(C, p, my_rank);
	
	end_t = MPI_Wtime();
	
	if(my_rank == 0) {
		output_data(f_out, C);
		printf("\nElapsed time = %g s\n", end_t - start_t);
		printf("--------------------------------------------\n");
	}
	
	MPI_Finalize();
}