int main(int argc, char *argv[]) 
{
  int time_limit;
  char name[1000];
  double cutoff=0.0;
  ListGraph g;
  EdgeWeight lpvar(g);
  EdgeWeight weight(g);
  NodeName vname(g);
  ListGraph::NodeMap<double> posx(g),posy(g);
  string filename;

  int seed=1;


  // uncomment one of these lines to change default pdf reader, or insert new one
  //set_pdfreader("open");    // pdf reader for Mac OS X
  //set_pdfreader("xpdf");    // pdf reader for Linux
  //set_pdfreader("evince");  // pdf reader for Linux

  srand48(seed);
  time_limit = 3600; // solution must be obtained within time_limit seconds
  if (argc!=2) {cout<< endl << "Usage: "<< argv[0]<<" <graph_filename>"<<endl << endl <<
      "Example: " << argv[0] << " gr_berlin52" << endl <<
      "         " << argv[0] << " gr_att48" << endl << endl; exit(0);}
  
  else if (!FileExists(argv[1])) {cout<<"File "<<argv[1]<<" does not exist."<<endl; exit(0);}
  filename = argv[1];
  
  // Read the graph
  if (!ReadListGraph(filename,g,vname,weight,posx,posy)) 
    {cout<<"Error reading graph file "<<argv[1]<<"."<<endl;exit(0);}

  TSP_Data tsp(g,vname,posx,posy,weight); 
  ListGraph::EdgeMap<GRBVar> x(g);
  GRBEnv env = GRBEnv();
  GRBModel model = GRBModel(env);
#if GUROBI_NEWVERSION
  model.getEnv().set(GRB_IntParam_LazyConstraints, 1);
  model.getEnv().set(GRB_IntParam_Seed, seed);
#else
  model.getEnv().set(GRB_IntParam_DualReductions, 0); // Dual reductions must be disabled when using lazy constraints
#endif
  model.set(GRB_StringAttr_ModelName, "Undirected TSP with GUROBI"); // name to the problem
  model.set(GRB_IntAttr_ModelSense, GRB_MINIMIZE); // is a minimization problem
  
  // Add one binary variable for each edge and also sets its cost in the objective function
  for (ListGraph::EdgeIt e(g); e!=INVALID; ++e) {
    sprintf(name,"x_%s_%s",vname[g.u(e)].c_str(),vname[g.v(e)].c_str());
    x[e] = model.addVar(0.0, 1.0, weight[e],GRB_BINARY,name);
  }
  model.update(); // run update to use model inserted variables

  // Add degree constraint for each node (sum of solution edges incident to a node is 2)
  for (ListGraph::NodeIt v(g); v!=INVALID; ++v) {
    GRBLinExpr expr;
    for (ListGraph::IncEdgeIt e(g,v); e!=INVALID; ++e) expr += x[e];
    //aqui model.addConstr(expr == 2 ); what? ignorou!
    model.addConstr(expr == 2 );

  }

  try {
    model.update(); // Process any pending model modifications.
    if (time_limit >= 0) model.getEnv().set(GRB_DoubleParam_TimeLimit,time_limit);

    subtourelim cb = subtourelim(tsp , x);
    model.setCallback(&cb);
    
    tsp.max_perturb2opt_it = 200; //1000; // number of iterations used in heuristic TSP_Perturb2OPT
    TSP_Perturb2OPT(tsp);
    if (tsp.BestCircuitValue < DBL_MAX) cutoff = tsp.BestCircuitValue-BC_EPS; // 
    // optimum value for gr_a280=2579, gr_xqf131=566.422, gr_drilling198=15808.652
    if (cutoff > 0) model.getEnv().set(GRB_DoubleParam_Cutoff, cutoff );
    model.update(); // Process any pending model modifications.
    model.optimize();

    double soma=0.0;
    for (ListGraph::EdgeIt e(g); e!=INVALID; ++e) {
      lpvar[e] = x[e].get(GRB_DoubleAttr_X);
      if (lpvar[e] > 1-BC_EPS ) {
	soma += weight[e];
	if (
	    (vname[g.u(e)] == "243")||(vname[g.v(e)] == "243") ||
	    (vname[g.u(e)] == "242")||(vname[g.v(e)] == "242")
	    ) {
	  cout << "Achei, x("<< vname[g.u(e)] << " , " << vname[g.v(e)] << " = " << lpvar[e] <<"\n";
	}
      }
    }

    cout << "Solution cost = "<< soma << endl;
    Update_Circuit(tsp,x); // Update the circuit in x to tsp circuit variable (if better)
    ViewTspCircuit(tsp);

  }catch (...) {
    if (tsp.BestCircuitValue < DBL_MAX) {
      cout << "Heuristic obtained optimum solution"  << endl;
      ViewTspCircuit(tsp);
      return 0;
    }else {
      cout << "Graph is infeasible"  << endl;
      return 1;
    }
  }
}