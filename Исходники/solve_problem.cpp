int main(int argv, char* argc[])
{

    mpi_check(MPI_Init(&argv, &argc));

    // identify the process
    char hostname[256];
    gethostname(hostname, sizeof(hostname));
    printf("Process with PID %d on %s ready to run\n", getpid(), hostname);
    fflush(stdout);

    int mpi_rank, mpi_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

    Index N = -1;
    Index NS = -1;
    if(argv == 3)
    {
        N = atoi(argc[1]);
        NS = atoi(argc[2]);
    } 

    // if rank == MASTER
    if(mpi_rank == 0)
    {

        if (argv != 3) {
            cout << "Usage: $mpirun -n NP ./solve_problem N NS ";
            return 0;
        }

        // Create an instance of your nlp...
        SmartPtr<MittelmannBndryCntrlDiri1> tnlp = new MittelmannBndryCntrlDiri1();


        if (N <= 0 || NS <= 0) {
            printf("Given problem size is invalid.\n");
            return -3;
        }

        bool retval = tnlp->InitializeProblem(N, NS);
        if (!retval) {
            printf("Cannot initialize problem.  Abort.\n");
            return -4;
        }

        // Create an instance of the IpoptApplication
        // We are using the factory, since this allows us to compile this
        // example with an Ipopt Windows DLL
        SmartPtr<IpoptApplication> app = IpoptApplicationFactory();

        app->Options()->SetNumericValue("tol", 1e-7);
        app->Options()->SetStringValue("mu_strategy", "adaptive");
        app->Options()->SetStringValue("output_file", "ipopt.out");
        app->Options()->SetIntegerValue("problem_dimension", N);
        app->Options()->SetIntegerValue("problem_scenarios", NS);

        // const std::string prefix = ""; Index nl;
        // cout << "Retval:" << app->Options()->GetIntegerValue("problem_dimension", nl, prefix) << endl;
        // cout << "problem_dimension: " << nl << endl;

        ApplicationReturnStatus status = app->Initialize();
        if (status != Solve_Succeeded) {
            printf("\n\n*** Error during initialization!\n");
            return (int) status;
        }
        // Set option to use internal scaling
        // DOES NOT WORK FOR VLUKL* PROBLEMS:
        // app->Options()->SetStringValueIfUnset("nlp_scaling_method", "user-scaling");

        status = app->OptimizeTNLP(GetRawPtr(tnlp));
    }
    else
    {
        // child process waits for master to initiate the solution phase
        int pardiso_mtype = -2; // symmetric H_i
        int schur_factorization = 1; //augmented factorization
        SchurSolve schurSolver = SchurSolve(pardiso_mtype, schur_factorization, MPI_COMM_WORLD);
        schurSolver.initSystem_OptimalControl(NULL, N, NS);
        
        while(1) {
            //do test on termination, set by master process
            int terminate = 0;
            MPI_Bcast(&terminate, 1, MPI_INT, 0, MPI_COMM_WORLD);
            if (terminate)
                break;
            
            //get flag new_matrix to child processes
            bool new_matrix;
            MPI_Bcast(&new_matrix, 1, MPI_C_BOOL, 0, MPI_COMM_WORLD);

            //update system if necessary
            if(new_matrix)
            {
                schurSolver.updateSystem(NULL);
            }

            int nrhs = 1;
            schurSolver.solveSystem(NULL, NULL, nrhs);
        }
    }

    mpi_check(MPI_Finalize());

    return 0;
}