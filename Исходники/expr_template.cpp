int main() {
    CS207::Clock timer;
    unsigned N = 512;
    Matrix A(N, N, 1.23);
    Matrix B(N, N, 2);
    Matrix C(N, N, 5.76);
    double alpha = 3.14;

    // Print out the type information of M
    std::cout << "Type of Expr:\n  "
              << 2.73*(A*B) + alpha*(alpha*A + B + A(0,0)*C) << std::endl;

    timer.start();
    Matrix D = 2.73*(A*B) + alpha*(alpha*A + B + A(0,0)*C);
    double eval_time = timer.seconds();
    std::cout << "Compute Time: " << eval_time << " seconds" << std::endl;
}