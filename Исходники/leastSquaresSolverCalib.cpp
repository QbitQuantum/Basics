Vector2d leastSquareSolverCalib::pointAlignerLoop( Vector2d &x,  MatrixXd &Z, int iterations,  Vector2d &result)
{
    result=x;
    MatrixXd H(2,2);
    H.setZero();

    MatrixXd b(2,1);
    b.setZero();

    Vector2d X;
    std::cout << Z.transpose()<< std::endl;
    for(int i = 0; i < iterations; i++){
        std::cout<<"iteration "<<i <<std::endl;
        X=x;
        for(int j=0;j<Z.cols();j++){

            Matrix2d J = computeJacobian(j,Z);
            Vector2d e=computeError(j,Z);
            std:: cout << "error: "<< e<< std::endl<<std::endl;
            H+=J.transpose()*J;
            b+=J.transpose()*e;
        }
    }
    Vector2d dx;
    std::cout << "H: "<<std::endl<<H<<std::endl<<std::endl<<std::endl;
    std::cout << "b: "<<std::endl<<b<<std::endl;
    LDLT<MatrixXd> ldlt(-H);
    dx=ldlt.solve(b); // using a LDLT factorizationldlt;
    return dx;

}