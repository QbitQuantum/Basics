int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Proper usage ./prog numThreads" << std::endl;
        return 1;
    }
    int numThreads = strtof(argv[1], NULL);
    for(int i=1; i<m-1; i++) {
        for (int j = 1; j < n-1; j++) {
            Un[i][j]=0.0;
        }

    }

    for (int i = 0; i < m; i++) {
        Un[i][0] = exactSolution(x(i), y(0));
        Un[i][n -1] = exactSolution(x(i), y(n - 1));
        Unp1[i][0] = exactSolution(x(i), y(0));
        Unp1[i][n -1] = exactSolution(x(i), y(n - 1));
    }
    for (int i = 0; i < n; i++) {
        Un[0][i] = exactSolution(x(0), y(i));
        Un[m - 1][i] = exactSolution(x(m-1), y(i));
        Unp1[0][i] = exactSolution(x(0), y(i));
        Unp1[m - 1][i] = exactSolution(x(m-1), y(i));
    }
    int iterations=0;
    double iterationError = 1.;
    double time = omp_get_wtime();
    while(iterationError > tolerance && iterations < maxIterations) {
        iterations++; //
        // if(iterations % 1000 == 0) std::cout<<"iteration " << iterations << std::endl;
        #pragma omp parallel for num_threads(numThreads)
        for(int i=1; i< m-1; i++) {
            for (int j = 1; j < n -1; j++) {

                Unp1[i][j] = (dy*dy*dx*dx*S(x(i), y(j)) - \
                              dy*dy*(Un[i -1][j] + Un[i + 1][j]) - \
                              dx*dx*(Un[i][j -1] + Un[i][j+1])) / (-2*dy*dy - 2*dx*dx);
            }
        }
        iterationError=0.0;
        // Calculate diff between Un, Up+1
        #pragma omp parallel for num_threads(numThreads)
        for(int i = 0; i< m; i++) {
            for (int j = 0; j < n; j++) {
                error[i][j] = fabs(Unp1[i][j] - Un[i][j]);

            }
        }
        for (int i = 0; i<m; i++)
            for (int j = 0; j <n; j++)
                iterationError = (iterationError > error[i][j] ? iterationError : error[i][j]);



// Testing revealed it was faster to *NOT* parallelize this loop.
        for(int i=0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                Un[i][j] = Unp1[i][j];
            }
        }

        // if(iterations % 1000 == 0) std::cout<< "The error between two iterates is " << iterationError << std::endl;
    }

    double time2 = omp_get_wtime();

    double solution_error=0.0;
    for(int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            double local_solution_error=fabs(Unp1[i][j]- exactSolution(x(i), y(j)) );
            {
                if (local_solution_error > solution_error)
                    solution_error = local_solution_error;
            }
        }
    }


    // Output:
    std::cout                                                              << std::endl << std::endl;
    std::cout<< "-------------------------------------------------------"               << std::endl;
    std::cout<< "SUMMARY:"                                                 << std::endl << std::endl;
    std::cout<< "The error between two iterates is "    << iterationError << std::endl << std::endl;
    std::cout<< "The maximum error in the solution is " << solution_error               << std::endl;
    std::cout<< "The time taken is " << time2 - time << std::endl;
    std::cout<< "-------------------------------------------------------"  << std::endl << std::endl;
    return 0;
}