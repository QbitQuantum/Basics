void BilinearRelaxationTest::runProblem()
{

    std::vector<double> cost, lb, ub, z0;

    cost.push_back(0);
    cost.push_back(0);
    cost.push_back(1);

    lb.push_back(-1.);
    lb.push_back(-1.);
    lb.push_back(-INF);

    ub.push_back(1);
    ub.push_back(2.5);
    ub.push_back(INF);

    z0.push_back(1);
    z0.push_back(-0.5);
    z0.push_back(-0.5);

    std::vector<VariablePtr> vars;
    for (unsigned int i = 0; i < 3; i++)
    {
        auto var = std::make_shared<Variable>(cost.at(i), lb.at(i), ub.at(i));
        var->setValue(z0.at(i));
        vars.push_back(var);
    }

    // Constraints
    ConstraintSetPtr constraints = std::make_shared<ConstraintSet>();

    ConstraintPtr myBilinearConstraint = std::make_shared<ConstraintBilinear>(vars,1,0,0);
    constraints->add(myBilinearConstraint);

    DataTable data;

    double dx = 0.5;
    for (double x1 = lb.at(0); x1 <= ub.at(0); x1+=dx)
    {
        for (double x2 = lb.at(1); x2 <= ub.at(1); x2+=dx)
        {
            std::vector<double> x;
            x.push_back(x1);
            x.push_back(x2);

            DenseVector xd; xd.setZero(2);
            xd(0) = x1;
            xd(1) = x2;
            DenseVector yd = bilinearFunction(xd);

            data.addSample(x,yd(0));
        }
    }

    ConstraintSetPtr constraints2 = std::make_shared<ConstraintSet>();
    BSpline bs = BSpline::Builder(data).degree(3).build();
    ConstraintPtr cbspline = std::make_shared<ConstraintBSpline>(vars, bs, true);
    constraints2->add(cbspline);

    // Test accuracy of B-spline
//    DenseVector (*foo)(DenseVector);
//    foo = &bilinearFunction;
//    BSpline* bs = new BSpline(*data, 3);
//    bool testpassed = bs->testBspline(foo);
//    if (testpassed)
//    {
//        cout << "B-spline is very accurate:)" << endl;
//    }
//    else
//    {
//        cout << "B-spline is NOT very accurate:(" << endl;
//    }

    BB::BranchAndBound solver(constraints);
    //SolverIpopt solver(constraints);
    SolverResult res = solver.optimize();

    cout << res << endl;

    zopt_found = res.primalVariables;
    fopt_found = res.objectiveValue;

}