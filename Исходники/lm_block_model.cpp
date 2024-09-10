void CLMBlockModel::optimise()
{
    this->run(); //Full recompute of all the 0-states, which will never be recomputed again.
	CLMFullModel fullModelFn(this);
    CLevMar LM(fullModelFn, true, 1e-7);
    Eigen::VectorXd params = fullModelFn.init();
    cout << params.transpose() << endl;
    LM.minimise(params, 5);
    cout << "Optimisation complete" << endl;
}