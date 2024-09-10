// template <typename tA, typename tB, typename tC, typename tD, typename tE>
// GRBmodel* gurobiQP(GRBenv *env, vector< MatrixBase<tA>* > QblkDiag, VectorXd&
// f, const MatrixBase<tB>& Aeq, const MatrixBase<tC>& beq, const
// MatrixBase<tD>& Ain, const MatrixBase<tE>& bin, VectorXd& lb, VectorXd& ub,
// set<int>& active, VectorXd& x)
GRBmodel* gurobiQP(GRBenv* env, vector<MatrixXd*> QblkDiag, VectorXd& f,
                   const MatrixXd& Aeq, const VectorXd& beq,
                   const MatrixXd& Ain, const VectorXd& bin, VectorXd& lb,
                   VectorXd& ub, set<int>& active, VectorXd& x,
                   double active_set_slack_tolerance) {
  // Note: f, lb, and ub are VectorXd instead of const MatrixBase templates
  // because i want to be able to call f.data() on them

  // NOTE:  this allocates memory for a new GRBmodel and returns it. (you should
  // delete this object when you're done with it)
  // NOTE:  by convention here, the active set indices correspond to Ain, bin
  // first, then lb, then ub.

  GRBmodel* model = NULL;

  int method;
  GRBgetintparam(env, "method", &method);

  int i, j, nparams = f.rows(), Qi, Qj;
  double* lbdata = NULL, * ubdata = NULL;
  if (lb.rows() == nparams) lbdata = lb.data();
  if (ub.rows() == nparams) ubdata = ub.data();
  CGE(GRBnewmodel(env, &model, "QP", nparams, NULL, lbdata, ubdata, NULL, NULL),
      env);

  int startrow = 0, d;
  for (vector<MatrixXd*>::iterator iterQ = QblkDiag.begin();
       iterQ != QblkDiag.end(); iterQ++) {
    MatrixXd* Q = *iterQ;

    // WARNING:  If there are no constraints, then gurobi clearly solves a
    // different problem: min 1/2 x'Qx + f'x
    //  				 This is very strange; see the
    //  solveWGUROBI method in QuadraticProgram
    if (method == 2)  //&& (Aeq.rows()+Ain.rows()>0))
      *Q = .5 * (*Q);

    if (Q->rows() == 1 || Q->cols() == 1) {  // it's a vector
      d = Q->rows() * Q->cols();
      for (i = 0; i < d; i++) {
        Qi = i + startrow;
        CGE(GRBaddqpterms(model, 1, &Qi, &Qi, &(Q->operator()(i))), env);
      }
      startrow = startrow + d;
    } else {  // potentially dense matrix
      d = Q->rows();
      if (d != Q->cols()) {
        cerr << "Q is not square! " << Q->rows() << "x" << Q->cols() << "\n";
        return NULL;
      }

      for (i = 0; i < d; i++)
        for (j = 0; j < d; j++) {
          Qi = i + startrow;
          Qj = j + startrow;
          CGE(GRBaddqpterms(model, 1, &Qi, &Qj, &(Q->operator()(i, j))), env);
        }
      startrow = startrow + d;
    }
    if (startrow > nparams) {
      cerr << "Q is too big!" << endl;
      return NULL;
    }
  }

  CGE(GRBsetdblattrarray(model, "Obj", 0, nparams, f.data()), env);

  if (Aeq.rows() > 0)
    CGE(myGRBaddconstrs(model, Aeq, beq, GRB_EQUAL, 1e-18), env);
  if (Ain.rows() > 0)
    CGE(myGRBaddconstrs(model, Ain, bin, GRB_LESS_EQUAL, 1e-18), env);

  CGE(GRBupdatemodel(model), env);
  CGE(GRBoptimize(model), env);

  CGE(GRBgetdblattrarray(model, GRB_DBL_ATTR_X, 0, nparams, x.data()), env);

  VectorXd slack(Ain.rows());
  CGE(GRBgetdblattrarray(model, "Slack", Aeq.rows(), Ain.rows(), slack.data()),
      env);

  int offset = 0;
  active.clear();
  for (int i = 0; i < Ain.rows(); i++) {
    if (slack(i) < active_set_slack_tolerance) active.insert(i);
  }
  offset = Ain.rows();
  if (lb.rows() == nparams)
    for (int i = 0; i < nparams; i++)
      if (x(i) - lb(i) < active_set_slack_tolerance) active.insert(offset + i);
  if (ub.rows() == nparams)
    for (int i = 0; i < nparams; i++)
      if (ub(i) - x(i) < active_set_slack_tolerance)
        active.insert(offset + i + nparams);

  return model;
}