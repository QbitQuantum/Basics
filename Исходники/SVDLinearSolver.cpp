void SVDLinearSolver<TMatrix,TVector>::solve(Matrix& M, Vector& x, Vector& b)
{
#ifdef SOFA_DUMP_VISITOR_INFO
    simulation::Visitor::printComment("SVD");
#endif
#ifdef DISPLAY_TIME
    CTime timer;
    double time1 = (double) timer.getTime();
#endif
    const bool verbose  = f_verbose.getValue();

    /// Convert the matrix and the right-hand vector to Eigen objects
    Eigen::MatrixXd m(M.rowSize(),M.colSize());
    Eigen::VectorXd rhs(M.rowSize());
    for(unsigned i=0; i<(unsigned)M.rowSize(); i++ )
    {
        for( unsigned j=0; j<(unsigned)M.colSize(); j++ )
            m(i,j) = M[i][j];
        rhs(i) = b[i];
    }

    msg_info_when(verbose) << "solve, Here is the matrix m:  "
                           << m ;

    /// Compute the SVD decomposition and the condition number
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(m, Eigen::ComputeThinU | Eigen::ComputeThinV);
    f_conditionNumber.setValue( (Real)(svd.singularValues()(0) / svd.singularValues()(M.rowSize()-1)) );



    if(verbose)
    {
        msg_info() << "solve, the singular values are:" << sendl << svd.singularValues()  << msgendl
                   << "Its left singular vectors are the columns of the thin U matrix: " << msgendl
                   << svd.matrixU() << msgendl
                   << "Its right singular vectors are the columns of the thin V matrix:" msgendl
                   << svd.matrixV() ;
    }else{
        msg_info() << "solve, the singular values are:" << sendl << svd.singularValues()  << msgendl;
    }

    /// Solve the equation system and copy the solution to the SOFA vector
//    Eigen::VectorXd solution = svd.solve(rhs);
//    for(unsigned i=0; i<M.rowSize(); i++ ){
//        x[i] = solution(i);
//    }
    Eigen::VectorXd Ut_b = svd.matrixU().transpose() *  rhs;
    Eigen::VectorXd S_Ut_b(M.colSize());
    for( unsigned i=0; i<(unsigned)M.colSize(); i++ )   /// product with the diagonal matrix, using the threshold for near-null values
    {
        if( svd.singularValues()[i] > f_minSingularValue.getValue() )
            S_Ut_b[i] = Ut_b[i]/svd.singularValues()[i];
        else
            S_Ut_b[i] = (Real)0.0 ;
    }
    Eigen::VectorXd solution = svd.matrixV() * S_Ut_b;
    for(unsigned i=0; i<(unsigned)M.rowSize(); i++ )
    {
        x[i] = (Real) solution(i);
    }

#ifdef DISPLAY_TIME
        time1 = (double)(((double) timer.getTime() - time1) * timeStamp / (nb_iter-1));
        dmsg_info() << " solve, SVD = "<<time1;
#endif
        dmsg_info() << "solve, rhs vector = " << msgendl << rhs.transpose() << msgendl
                    << " solution =   \n" << msgendl << x << msgendl
                    << " verification, mx - b = " << msgendl << (m * solution - rhs ).transpose() << msgendl;
}