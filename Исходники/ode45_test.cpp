void test3() {
#ifdef MAKE_TEST3
    std::cout << "Multidimensional test:" << std::endl;
    
    // Construct data for the IVP
    double T = 1;
    // Many dimensions
    int n = 5;
    
    // Multidimensional rhs
    Eigen::VectorXd y0(2*n);
    for(int i = 0; i < n; ++i) {
        y0(i)=(i+1.)/n;
        y0(i+n)=-1;
    }
    
    // Multidimensional rhs
    auto f = [n] (Eigen::VectorXd y) {
        Eigen::VectorXd fy(2*n);
        
        Eigen::VectorXd g(n);
        g(0) = y(0)*(y(1)+y(0));
        g(n-1) = y(n-1)*(y(n-1)+y(n-2));
        for(int i = 1; i < n-1; ++i) {
            g(i) = y(i)*(y(i-1)+y(i+1));
        }
        
        Eigen::SparseMatrix<double> C(n,n);
        C.reserve(3);
        for(int i = 0; i < n; ++i) {
            C.insert(i,i) = 2;
            if(i < n-1) C.insert(i,i+1) = -1;
            if(i >= 1)  C.insert(i,i-1) = -1;
        }
        C.makeCompressed();
        fy.head(n) = y.head(n);
        
        Eigen::SparseLU< Eigen::SparseMatrix<double> >  solver;
        solver.analyzePattern(C);
        solver.compute(C);
        fy.tail(n) = solver.solve(g);
        return fy;
    };
    
    // Constructor:
    ode45<Eigen::VectorXd> O(f);
    
    // Setup options
    O.options.do_statistics = true;
    
    // Solve
    auto sol = O.solve(y0, T);
    
    // Print info
    O.print();

    std::cout << "T = " << sol.back().second << std::endl;
    std::cout << "y(T) = " << std::endl << sol.back().first << std::endl;
#endif
}