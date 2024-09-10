int sphere_eval_data_mp::receive(ParallelismConfig & mpi_config)
{
	
	int *buffer = new int[2];
	MPI_Bcast(buffer, 1, MPI_INT, mpi_config.head(), mpi_config.comm());
	
	if (buffer[0] != SPHERE_SOLVER) {
		std::cout << "worker failed to confirm it is receiving the SPHERE_SOLVER type eval data" << std::endl;
		mpi_config.abort(777);
	}
	
	SolverMultiplePrecision::receive(mpi_config);
	
	
	// now can actually receive the data from whoever.
	MPI_Bcast(buffer, 2, MPI_INT, mpi_config.head(), mpi_config.comm());
	
	num_natural_vars = buffer[0];
	num_static_linears = buffer[1];
	
	delete[] buffer;
	
	//starting linears already created and initted
	static_linear = (vec_mp *) br_malloc(num_static_linears*sizeof(vec_mp));
	
	if (this->MPType==2) {
		static_linear_full_prec = (vec_mp *) br_malloc(num_static_linears*sizeof(vec_mp));
		
		for (int ii=0; ii<num_static_linears; ii++) {
			
			init_vec_mp(static_linear[ii],1);
			init_vec_mp2(static_linear_full_prec[ii],1,1024);
			
			bcast_vec_mp(static_linear_full_prec[ii], mpi_config.id(), mpi_config.head());
			
			vec_cp_mp(static_linear[ii],static_linear_full_prec[ii]);
			
		}
		
		for (int ii=0; ii<2; ii++) {
			
			bcast_vec_mp(starting_linear_full_prec[ii], mpi_config.id(), mpi_config.head());
			
			vec_cp_mp(starting_linear[ii],starting_linear_full_prec[ii]);
		}
		
		bcast_vec_mp(center_full_prec, mpi_config.id(), mpi_config.head());
		
		bcast_comp_mp(radius_full_prec, mpi_config.id(), mpi_config.head());
		
		vec_cp_mp(center, center_full_prec);
		set_mp(radius, radius_full_prec);
	}
	else{ // MPType == 1
		for (int ii=0; ii<num_static_linears; ii++) {
			init_vec_mp(static_linear[ii],1);
			bcast_vec_mp(static_linear[ii], mpi_config.id(), mpi_config.head());
		}
		
		for (int ii=0; ii<2; ii++) {
			bcast_vec_mp(starting_linear[ii], mpi_config.id(), mpi_config.head());
		}
		
		bcast_vec_mp(center, mpi_config.id(), mpi_config.head());
		bcast_comp_mp(radius, mpi_config.id(), mpi_config.head());
	}
	
	
	return SUCCESSFUL;
	
}