int monitoramento_em_grafo_bipartido( ListGraph &g, NodeName &vname, ListGraph::NodeMap<double> &custo, ListGraph::NodeMap<int> &solucao)
{
  int seed=0;
  GRBEnv env = GRBEnv();
  GRBModel model = GRBModel(env);
  model.getEnv().set(GRB_IntParam_Seed, seed);
  model.set(GRB_StringAttr_ModelName, "Monitoramento em Grafo Bipartido"); // prob. name
  model.set(GRB_IntAttr_ModelSense, GRB_MINIMIZE); // is a minimization problem
  // ------------------------------------------------------
  // Construa o modelo daqui para baixo
  // ------------------------------------------------------

  // Exemplos de como voce pode declarar variaveis indexadas nos vertices ou nas arestas.
  // Nao necessariamente voce precisa dos dois tipos
  // ListGraph::NodeMap<GRBVar> x(g); // variables for each node
  // ListGraph::EdgeMap<GRBVar> y(g); // variables for each edge
  ListGraph::NodeMap<GRBVar> x(g); // variables for each node
  ListGraph::EdgeMap<GRBVar> y(g); // variables for each edge
  int name = 0;
  char namme[100];
  for(ListGraph::NodeIt v(g); v != INVALID; ++v) {
    sprintf(namme,"PC_%s",vname[v].c_str());
    x[v] = model.addVar(0.0, 1.0, custo[v],GRB_CONTINUOUS,namme); }
  model.update();
  try {
    for(ListGraph::EdgeIt e(g); e != INVALID; ++e) {
      //Para cada aresta, um dos lados e 1
      GRBLinExpr expr;
      expr += x[g.u(e)];
      expr += x[g.v(e)];
      model.addConstr(expr >= 1);
    }
    model.update();
    // ------------------------------------------------------
    // Construa o modelo daqui para cima
    // ------------------------------------------------------
    //model.write("model.lp"); system("cat model.lp");
    model.optimize();
    for (ListGraph::NodeIt v(g); v!=INVALID; ++v) {
      if (x[v].get(GRB_DoubleAttr_X)>1-EPS) solucao[v] = 1;
      else solucao[v] = 0;
      //solucao[v] = 1;
    }
    return(1);

  } catch (...) {cout << "Error during callback..." << endl; return(0);}
}