void POP03::runProblem()
{
    // Problem 3 (Nataraj)
    // cout << "\n\nSolving problem P03..." << endl;

    int dim = 4;

    // x1,x2,l1,l2
    std::vector<double> costs = {1, 0, 0, 0};
    std::vector<double> lb = {-10,-10,0,-1000};
    std::vector<double> ub = {10,10,100,1000};
    std::vector<double> z0(dim,0);

    std::vector<VariablePtr> vars;
    for (int i = 0; i < dim; i++)
    {
        auto var = std::make_shared<Variable>(costs.at(i), lb.at(i), ub.at(i));
        vars.push_back(var);
    }

    ConstraintSetPtr cs = std::make_shared<ConstraintSet>();

    { // x1^2 = l1
        VariablePtr var = vars.at(0);
        std::vector<double> thislb = {var->getLowerBound()};
        std::vector<double> thisub = {var->getUpperBound()};

        std::vector<unsigned int> deg = {2};

        DenseVector c(3);
        c.setZero();
        c(0) = 0;
        c(1) = 0;
        c(2) = 1;

        DenseMatrix T = getTransformationMatrix(deg, thislb, thisub);
        DenseMatrix coeffs = T*c;

        std::vector< std::vector<double> > knots = getRegularKnotVectors(deg, thislb, thisub);

        BSpline bs(coeffs.transpose(), knots, deg);

        std::vector<VariablePtr> cvars = {var, vars.at(2)};
        ConstraintPtr cbs = std::make_shared<ConstraintBSpline>(cvars, bs, true);
        cs->add(cbs);
    }

    { // x1^3 = l1
        VariablePtr var = vars.at(0);
        std::vector<double> thislb = {var->getLowerBound()};
        std::vector<double> thisub = {var->getUpperBound()};

        std::vector<unsigned int> deg = {3};

        DenseVector c(4); c.setZero();
        c(0) = 0;
        c(1) = 0;
        c(2) = 0;
        c(3) = 1;

        DenseMatrix T = getTransformationMatrix(deg, thislb, thisub);
        DenseMatrix coeffs = T*c;

        std::vector< std::vector<double> > knots = getRegularKnotVectors(deg, thislb, thisub);

        BSpline bs(coeffs.transpose(), knots, deg);

        std::vector<VariablePtr> cvars = {var, vars.at(3)};
        ConstraintPtr cbs = std::make_shared<ConstraintBSpline>(cvars, bs, true);
        cs->add(cbs);
    }

    { // x2 - l1 <= 0, x2 - l2 <= 0

        DenseMatrix A(2,3);
        A.setZero();
        A(0,0) = -1; A(0,1) = 1;
        A(1,0) = 1; A(1,1) = 2; A(1,2) = -1;

        DenseVector b; b.setZero(2); b(1) = -1e-5;

        std::vector<VariablePtr> cvars = {
            vars.at(1),
            vars.at(2),
            vars.at(3)
        };
        ConstraintPtr lincon = std::make_shared<ConstraintLinear>(cvars, A, b, false);
        cs->add(lincon);
    }

    BB::BranchAndBound bnb(cs);
    Timer timer;
    timer.start();
    SolverResult res = bnb.optimize();
    timer.stop();
    cout << "Time: " << timer.getMilliSeconds() << " (ms)" << endl;

    if (res.status == SolverStatus::OPTIMAL)
        fopt_found = res.objectiveValue;
}