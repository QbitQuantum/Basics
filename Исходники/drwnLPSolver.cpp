double drwnSparseLPSolver::solve()
{
    DRWN_FCN_TIC;
    const int n = _A.cols();
    const int m = _A.rows();

    // find feasible starting point
    if (_x.rows() == 0) {
        _x = VectorXd::Zero(n);
        for (int i = 0; i < n; i++) {
            if (isUnbounded(i)) continue;

            if (_ub[i] == DRWN_DBL_MAX) {
                _x[i] = _lb[i] + 1.0;
            } else if (_lb[i] == -DRWN_DBL_MAX) {
                _x[i] = _ub[i] - 1.0;
            } else {
                _x[i] = 0.5 * (_lb[i] + _ub[i]);
            }
        }
    }

    // initialize kkt system variables
    SparseMatrix<double> F(n + m, n + m);
    VectorXd g = VectorXd::Zero(n + m);

    vector<Eigen::Triplet<double> > entries;
    entries.reserve(n + 2 * _A.nonZeros());
    for (int i = 0; i < n; i++) {
        entries.push_back(Eigen::Triplet<double>(i, i, 1.0));
    }

    for (int k = 0; k < _A.outerSize(); k++) {
        for (SparseMatrix<double>::InnerIterator it(_A, k); it; ++it) {
            entries.push_back(Eigen::Triplet<double>(n + it.row(), it.col(), it.value()));
            entries.push_back(Eigen::Triplet<double>(it.col(), n + it.row(), it.value()));
        }
    }

    F.setFromTriplets(entries.begin(), entries.end());

    // initialize dual variables (if needed)
    VectorXd nu = VectorXd::Zero(m);

    // iterate on interior point method
    double t = drwnLPSolver::t0;
    while (1) {
        // determine feasibility
        const bool bFeasible = ((_b - _A * _x).squaredNorm() < drwnLPSolver::eps);
        if (!bFeasible) {
            DRWN_LOG_VERBOSE("...finding feasible point");
        }

        // centering step and update
        for (unsigned iter = 0; iter < drwnLPSolver::maxiters; iter++) {

            //! \todo solve with blockwise elimination
            // construct KKT system, Fx = g
            // | H A^T | | dx | = |  - g   |
            // | A  0  | | w  |   | b - Ax |

            for (int i = 0; i < n; i++) {
                F.coeffRef(i, i) = 0.0;
                if (_ub[i] != DRWN_DBL_MAX) {
                    F.coeffRef(i, i) += 1.0 / ((_ub[i] - _x[i]) * (_ub[i] - _x[i]));
                }
                if (_lb[i] != -DRWN_DBL_MAX) {
                    F.coeffRef(i, i) += 1.0 / ((_x[i] - _lb[i]) * (_x[i] - _lb[i]));
                }
            }

            for (int i = 0; i < n; i++) {
                g[i] = - t * _c[i];
                if (_ub[i] != DRWN_DBL_MAX) {
                    g[i] += 1.0 / (_x[i] - _ub[i]);
                }
                if (_lb[i] != -DRWN_DBL_MAX) {
                    g[i] += 1.0 / (_x[i] - _lb[i]);
                }
            }
            g.tail(m) = _b - _A * _x;

            // check terminating condition
            const double r_primal = g.tail(m).squaredNorm();
            const double r_dual = (_A.transpose() * nu - g.head(n)).squaredNorm();
            //if (!bFeasible && (r_primal + r_dual < drwnLPSolver::eps)) break;
            if (!bFeasible && (r_primal < drwnLPSolver::eps)) break;

            // solve KKT system
            SimplicialLDLT<SparseMatrix<double> > chol(F);
            const VectorXd dxnu = chol.solve(g);

            const double lambda_sqr = g.head(n).dot(dxnu.head(n));
            if (bFeasible && (0.5 * lambda_sqr < 1.0e-6)) break;

            if (bFeasible) {
                // feasible line search
                const double f_prev = t * _c.dot(_x) + barrierFunction(_x);
                const double delta_f = drwnLPSolver::alpha * g.dot(dxnu.head(n));

                double step = 1.0;
                while (1) {
                    const VectorXd nx = _x + step * dxnu.head(n);
                    if (isWithinBounds(nx)) {
                        const double f = t * _c.dot(nx) + barrierFunction(nx);
                        if (f - f_prev < step * delta_f) {
                            _x = nx;
                            break;
                        }
                    }
                    step *= drwnLPSolver::beta;
                }
            } else {
                // infeasible start line search
                DRWN_LOG_DEBUG("...iteration " << iter << ", primal residual " << r_primal
                    << ", dual residual " << r_dual);

                double step = 1.0;
                while (1) {
                    const VectorXd nx = _x + step * dxnu.head(n);
                    if (isWithinBounds(nx)) {
                        const VectorXd nnu = (1.0 - step) * nu + step * dxnu.tail(m);
                        const double r = (_A.transpose() * nnu - g.head(n)).squaredNorm() +
                            (_b - _A * nx).squaredNorm();
                        if (r <= (1.0 - drwnLPSolver::alpha * step) * (r_primal + r_dual)) {
                            _x = nx;
                            nu = nnu;
                            break;
                        }
                    }
                    step *= drwnLPSolver::beta;
                }
            }
        }

        // check if feasible point was found
        if (!bFeasible && ((_b - _A * _x).squaredNorm() > drwnLPSolver::eps)) {
            DRWN_LOG_WARNING("...could not find a feasible point (residual norm is " <<
                (_b - _A * _x).norm() << ")");
            DRWN_FCN_TOC;
            return DRWN_DBL_MAX;
        }

        DRWN_LOG_VERBOSE("...objective is " << _c.dot(_x));

        // check stopping criteria
        if (m < drwnLPSolver::eps * t) break;

        // update barrier function multiplier
        t *= drwnLPSolver::mu;
    }

    // compute true objective and return
    DRWN_FCN_TOC;
    return _c.dot(_x);
}