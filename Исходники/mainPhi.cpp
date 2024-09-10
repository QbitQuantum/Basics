void test_MPI(int argc, char *argv[]){

	ClusterNet *gpu = new ClusterNetCPU();
	Matrix<float> *A = gpu->rand(100,100);
	Matrix<float> *B = gpu->rand(2,2);

	cout << "pre gradient init" << endl;
	GradientAccumulator *ga = new GradientAccumulator(gpu);
	cout << "pre init mpi" << endl;
	ga->init_MPI();

	float a[4] = {0,0,0,0};
	if(ga->my_rank == 0)
	{
		for(int i = 0; i < 4; i++)
			a[i] = (float)i;
	}
	else
	{
		for(int i = 0; i < 4; i++)
			a[i] = (float)i*2;
	}

	cout << "pre gpu" << endl;
	//gpu->OPS->to_gpu(a, B);


	Matrix<float> *M = new Matrix<float>();
	M->rows = 2;
	M->cols = 2;
	M->size = 4;
	M->bytes = 4*4;
	M->data = a;
        M->isRowMajor = true;

	cout << "pre init matrix" << endl;
	ga->init_Matrix(M);
	cout << "pre send matrix" << endl;
	ga->send_MPI();
	cout << "pre recv matrix" << endl;
	ga->recv_MPI();
	cout <<"testingg"<< endl;
	//gpu->OPS->to_host(ga->buffer,a);

	MPI_Barrier(MPI_COMM_WORLD);
	if(ga->my_rank == 0)
	{
		cout << "Myrank " << ga->my_rank << endl;
		for(int i = 0; i < 4; i++)
	cout <<		ga->matrix->data[i] << " ";
	cout << endl;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	if(ga->my_rank == 1)
	{
		cout << "Myrank " << ga->my_rank << endl;
		for(int i = 0; i < 4; i++)
	cout <<		ga->matrix->data[i] << " ";
	cout << endl;
	}


}