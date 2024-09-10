typename GaussianProcess<TScalarType>::MatrixType GaussianProcess<TScalarType>::InvertKernelMatrix(const typename GaussianProcess<TScalarType>::MatrixType &K,
                                                      typename GaussianProcess<TScalarType>::InversionMethod inv_method = GaussianProcess<TScalarType>::FullPivotLU,
                                                                                                   bool stable) const{
    // compute core matrix
    if(debug){
        std::cout << "GaussianProcess::InvertKernelMatrix: inverting kernel matrix... ";
        std::cout.flush();
    }

    typename GaussianProcess<TScalarType>::MatrixType core;

    switch(inv_method){
    // standard method: fast but not that accurate
    // Uses the LU decomposition with full pivoting for the inversion
    case FullPivotLU:{
        if(debug) std::cout << " (inversion method: FullPivotLU) " << std::flush;
        try{
            if(stable){
                core = K.inverse();
            }
            else{
                if(debug) std::cout << " (using lapack) " << std::flush;
                core = lapack::lu_invert<TScalarType>(K);
            }
        }
        catch(lapack::LAPACKException& e){
            core = K.inverse();
        }
    }
    break;

    // very accurate and very slow method, use it for small problems
    // Uses the two-sided Jacobi SVD decomposition
    case JacobiSVD:{
        if(debug) std::cout << " (inversion method: JacobiSVD) " << std::flush;
        Eigen::JacobiSVD<MatrixType> jacobisvd(K, Eigen::ComputeThinU | Eigen::ComputeThinV);
        if((jacobisvd.singularValues().real().array() < 0).any() && debug){
            std::cout << "GaussianProcess::InvertKernelMatrix: warning: there are negative eigenvalues.";
            std::cout.flush();
        }
        core = jacobisvd.matrixV() * VectorType(1/jacobisvd.singularValues().array()).asDiagonal() * jacobisvd.matrixU().transpose();
    }
    break;

    // accurate method and faster than Jacobi SVD.
    // Uses the bidiagonal divide and conquer SVD
    case BDCSVD:{
        if(debug) std::cout << " (inversion method: BDCSVD) " << std::flush;
#ifdef EIGEN_BDCSVD_H
        Eigen::BDCSVD<MatrixType> bdcsvd(K, Eigen::ComputeThinU | Eigen::ComputeThinV);
        if((bdcsvd.singularValues().real().array() < 0).any() && debug){
            std::cout << "GaussianProcess::InvertKernelMatrix: warning: there are negative eigenvalues.";
            std::cout.flush();
        }
        core = bdcsvd.matrixV() * VectorType(1/bdcsvd.singularValues().array()).asDiagonal() * bdcsvd.matrixU().transpose();
#else
        // this is checked, since BDCSVD is currently not in the newest release
        throw std::string("GaussianProcess::InvertKernelMatrix: BDCSVD is not supported by the provided Eigen library.");
#endif

    }
    break;

    // faster than the SVD method but less stable
    // computes the eigenvalues/eigenvectors of selfadjoint matrices
    case SelfAdjointEigenSolver:{
        if(debug) std::cout << " (inversion method: SelfAdjointEigenSolver) " << std::flush;
        try{
            core = lapack::chol_invert<TScalarType>(K);
        }
        catch(lapack::LAPACKException& e){
            Eigen::SelfAdjointEigenSolver<MatrixType> es;
            es.compute(K);
            VectorType eigenValues = es.eigenvalues().reverse();
            MatrixType eigenVectors = es.eigenvectors().rowwise().reverse();
            if((eigenValues.real().array() < 0).any() && debug){
                std::cout << "GaussianProcess::InvertKernelMatrix: warning: there are negative eigenvalues.";
                std::cout.flush();
            }
            core = eigenVectors * VectorType(1/eigenValues.array()).asDiagonal() * eigenVectors.transpose();
        }
    }
    break;
    }

    if(debug) std::cout << "[done]" << std::endl;
    return core;
}