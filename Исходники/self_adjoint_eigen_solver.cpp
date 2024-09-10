int main()
{
    std::ostringstream osi;
    std::ostringstream osf;

    MatrixXd X = MatrixXd::Random(5,5);
    MatrixXd A = X + X.transpose();
    
    osi << A << std::endl;

    SelfAdjointEigenSolver<MatrixXd> es(A);

//    std::cout << es.eigenvalues() << std::endl;
//    std::cout << es.eigenvectors() << std::endl;

    MatrixXd D = es.eigenvalues().asDiagonal();
    MatrixXd V = es.eigenvectors();

    osf << V * D * V.inverse() << std::endl;

    return verify( osi.str(),osf.str() );
}