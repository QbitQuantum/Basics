int
main(int   argc,
     char *argv[])
{
  if (argc < 2) {
    cout << "Usage: tsp_c++ filename" << endl;
    return 1;
  }

  int n = atoi(argv[1]);
  double* x = new double[n];
  double* y = new double[n];

  for (int i = 0; i < n; i++) {
    x[i] = ((double) rand())/RAND_MAX;
    y[i] = ((double) rand())/RAND_MAX;
  }

  GRBEnv *env = NULL;
  GRBVar **vars = new GRBVar*[n];

  try {
    int i, j;

    env = new GRBEnv();
    GRBModel model = GRBModel(*env);

    // Must disable dual reductions when using lazy constraints

    model.getEnv().set(GRB_IntParam_DualReductions, 0);

    // Create binary decision variables

    for (i = 0; i < n; i++)
      vars[i] = model.addVars(n);
    model.update();

    for (i = 0; i < n; i++) {
      for (j = 0; j < n; j++) {
        vars[i][j].set(GRB_CharAttr_VType, GRB_BINARY);
        vars[i][j].set(GRB_DoubleAttr_Obj, distance(x, y, i, j));
        vars[i][j].set(GRB_StringAttr_VarName, "x_"+itos(i)+"_"+itos(j));
      }
    }

    // Integrate new variables

    model.update();

    // Degree-2 constraints

    for (i = 0; i < n; i++) {
      GRBLinExpr expr = 0;
      for (j = 0; j < n; j++)
        expr += vars[i][j];
      model.addConstr(expr == 2, "deg2_"+itos(i));
    }

    // Forbid edge from node back to itself

    for (i = 0; i < n; i++)
      vars[i][i].set(GRB_DoubleAttr_UB, 0);

    // Symmetric TSP

    for (i = 0; i < n; i++)
      for (j = 0; j < i; j++)
        model.addConstr(vars[i][j] == vars[j][i]);

    // Set callback function

    subtourelim cb = subtourelim(vars, n);
    model.setCallback(&cb);

    // Optimize model

    model.optimize();

    // Extract solution

    if (model.get(GRB_IntAttr_SolCount) > 0) {
      double **sol = new double*[n];
      for (i = 0; i < n; i++)
        sol[i] = model.get(GRB_DoubleAttr_X, vars[i], n);

      int* tour = new int[n];
      int len;

      findsubtour(n, sol, &len, tour);

      cout << "Tour: ";
      for (i = 0; i < len; i++)
        cout << tour[i] << " ";
      cout << endl;

      for (i = 0; i < n; i++)
        delete[] sol[i];
      delete[] sol;
      delete[] tour;
    }

  } catch (GRBException e) {
    cout << "Error number: " << e.getErrorCode() << endl;
    cout << e.getMessage() << endl;
  } catch (...) {
    cout << "Error during optimization" << endl;
  }

  for (int i = 0; i < n; i++)
    delete[] vars[i];
  delete[] vars;
  delete[] x;
  delete[] y;
  delete env;
  return 0;
}