    Eigen::VectorXd operator()(const F& obj,  Eigen::VectorXd x) const {
        Eigen::VectorXd g, d;
        Eigen::MatrixXd G;
        LineSearch lineSearch;
        obj(x, g);
        obj(x, G);

        DEBUG_PRINT(x);
        DEBUG_PRINT(g);
        DEBUG_PRINT(G);
        DEBUG_PRINT(G.ldlt().solve(g));
        while(g.norm() > 10e-10) {
#if DEBUG
            std::cout << std::string(20, '-') << std::endl;
#endif
            d = G.ldlt().solve(-g);
            DEBUG_PRINT(G.ldlt().solve(-g).transpose());
            DEBUG_PRINT(G.ldlt().vectorD());

            Real a = 1.;
            a = lineSearch(obj, x, d, a);

            DEBUG_PRINT(a);
            DEBUG_PRINT(obj(x));
            x = x +  a * d;
            obj(x, g);
            obj(x, G);
            DEBUG_PRINT(x.transpose());
            DEBUG_PRINT(g.transpose());
            //	DEBUG_PRINT(G);
        }
        return x;
    }