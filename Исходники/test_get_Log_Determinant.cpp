int main() {
        int N                   =       10;
        Eigen::MatrixXd A       =       Eigen::MatrixXd::Random(N,N);
        double detc             =       get_Log_Determinant(A);
        double det              =       log(fabs(A.determinant()));
        std::cout << fabs(detc-det) << std::endl;
}