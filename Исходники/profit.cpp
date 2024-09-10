void profit_load(graph g, IloCplex cplex, IloModel model, IloNumVarArray x, IloNumVarArray p, IloNumVarArray z, int **columns, vector<int>& allocation, vector<double>& pricing) {
  IloNumVarArray startVar(model.getEnv());
  IloNumArray startVal(model.getEnv());
  for(int j = 0; j < g->items; j++) {
    if(boundp(j) > 0){
      startVar.add(p[j]);
      startVal.add(pricing[j]);
    }
  }
  for(int i = 0; i < g->bidders; i++) {
    for(int e = 0; e < g->dbidder[i]; e++) {
      int j = g->b_adj[i][e];
      startVar.add(x[columns[i][j]]);
      startVal.add(allocation[i] == j ? 1 : 0);
    }
  }
  for(int i = 0; i < g->bidders; i++) {
    if(boundu(i) > 0){
      startVar.add(z[i]);
      startVal.add(allocation[i] != -1 ? pricing[allocation[i]] : 0);
    }
  }
  cplex.addMIPStart(startVar, startVal);
}