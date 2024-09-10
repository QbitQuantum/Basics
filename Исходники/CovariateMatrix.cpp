    void CovariateMatrix::buildDecorrelationProjectionMatrix()
    {
        // There's no use parallelizing this. Even though it might be 
        // computationally intensive, this operation only needs to be done once per 
        // chain per covariate matrix. 

        // Combine X and Z appropriately to one large covariate matrix X
        // We want a projection onto N(X'X)
        //
        // The projection onto the column space of A= X'X = P(A) = (A) %*% (A'A)^(-1)) %*% (A')

        // The projection onto the null space of X' is then I - P(A)

        // The steps to compute I-P(A) are therefore:
        // 1. Calculate B = (A'A)
        // 2. Calculate C = B^(-1)
        // 3. Calculate D= A'CA
        // 5. Calculate E = I - D


        // Step 0. Create big matrix X.  
        int numVariables = (*ncol_x)+(*ncol_z);
        double *bigX;
        int matrixRows;
        int i;
        // Case 1: X matrix only, time varying. 
        if (*nrow_z == 0)
        {
            matrixRows = *nrow_x;
            bigX = new double[numVariables*(matrixRows)];
            memcpy(bigX, X, numVariables*(*nrow_x)*sizeof(double));    
        }
        // Case 2: X and Z matrices, fixed and time varying
        else
        {
            matrixRows = *nrow_z;
            bigX = new double[numVariables*(matrixRows)];
            memset(bigX, 0, numVariables*(*nrow_z)*sizeof(double));    

            int numLoc = *nrow_x;
            int numTpt = (*nrow_z)/numLoc;
            int xCol, xRow;
            int idx1, idx2;
            // Load up fixed covariates
            for (xCol = 0; xCol < (*ncol_x); xCol++)
            {
                for (xRow = 0; xRow < numLoc; xRow ++)
                {
                    for (i = 0; i < numTpt; i++)
                    {
                        idx1 = xCol*(*nrow_z) + xRow*numTpt + i;
                        idx2 = xCol*numLoc + xRow;
                        bigX[idx1] = X[idx2];
                    }
                }
            }
            // Load up time varying covariates
            int zCol, zRow;
            for (zCol = 0; zCol < (*ncol_z); zCol ++)
            {
                for (zRow = 0; zRow < (*nrow_z); zRow ++) 
                {
                    idx1 = (*ncol_x + zCol)*(*nrow_z) + zRow;
                    idx2 = zCol*(*nrow_z) + zRow;
                    bigX[idx1] = Z[idx2];
                }
            } 
        }

        // Step 1. Calculate A = (XX')
        double* A = bigX;
        
        typedef Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> MatrixType;
        typedef Eigen::Map<MatrixType, Eigen::ColMajor> MatrixMapType;

        MatrixMapType Amap(A, matrixRows, numVariables);
        MatrixMapType outMap(decorrelationProjectionMatrix, numVariables, numVariables);


        MatrixType Bmat = ((Amap.transpose() * Amap));
        MatrixType Cmat = (Bmat.transpose() * Bmat);
        MatrixType Dmat = (Bmat * Cmat.inverse() * Bmat.transpose()); 
        MatrixType Emat = Eigen::MatrixXd::Identity(Dmat.rows(), Dmat.cols()) - Dmat;         
        outMap.noalias() = Emat;
 
        delete[] bigX;
    }