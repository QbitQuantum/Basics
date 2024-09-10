int main(int argc, char *argv[]) 
{
  int nt;
  Digraph g;  // graph declaration
  string digraph_steiner_filename;
  DiNodeName vname(g);  // name of graph nodes
  Digraph::NodeMap<double> px(g),py(g);  // xy-coodinates for each node
  Digraph::NodeMap<int> vcolor(g);// color of nodes
  Digraph::ArcMap<int> ecolor(g); // color of edges
  ArcWeight lpvar(g);    // used to obtain the contents of the LP variables
  ArcWeight weight(g);   // edge weights
  Digraph::ArcMap<GRBVar> x(g); // binary variables for each arc
  vector <DiNode> V;
  int seed=0;
  srand48(1);

  // uncomment one of these lines to change default pdf reader, or insert new one
  //set_pdfreader("open");    // pdf reader for Mac OS X
  //set_pdfreader("xpdf");    // pdf reader for Linux
  //set_pdfreader("evince");  // pdf reader for Linux

    
  // double cutoff;   // used to prune non promissing branches (of the B&B tree)
  if (argc!=2) {cout<< endl << "Usage: "<< argv[0]<<"  <digraph_steiner_filename>"<< endl << endl;
    cout << "Examples:      " << argv[0] << " gr_berlin52.steiner" << endl;
    cout << "               " << argv[0] << " gr_usa48.steiner" << endl << endl;
    exit(0);}

  digraph_steiner_filename = argv[1];

  //int time_limit = 3600; // solution must be obtained within time_limit seconds
  GRBEnv env = GRBEnv();
  GRBModel model = GRBModel(env);
  model.getEnv().set(GRB_IntParam_LazyConstraints, 1);
  model.getEnv().set(GRB_IntParam_Seed, seed);
  model.set(GRB_StringAttr_ModelName, "Oriented Steiner Tree with GUROBI"); // prob. name
  model.set(GRB_IntAttr_ModelSense, GRB_MINIMIZE); // is a minimization problem

  ReadListDigraphSteiner(digraph_steiner_filename,g,vname,weight,px,py,1,nt,V); 
  Steiner_Instance T(g,vname,px,py,weight,nt,V);
  //for (DiNodeIt v(g);v!=INVALID;++v){ if(v==T.V[0])vcolor[v]=RED; else vcolor[v]=BLUE;}
  //for (int i=1;i<T.nt;i++) vcolor[T.V[i]] = MAGENTA;
  //for (ArcIt e(g); e != INVALID; ++e) ecolor[e] = BLUE;
  //ViewListDigraph(g,vname,px,py,vcolor,ecolor,"Triangulated graph");
  
  // Generate the binary variables and the objective function
  // Add one binary variable for each edge and set its cost in the objective function
  for (Digraph::ArcIt e(g); e != INVALID; ++e) {
    char name[100];
    sprintf(name,"X_%s_%s",vname[g.source(e)].c_str(),vname[g.target(e)].c_str());
    x[e] = model.addVar(0.0, 1.0, weight[e],GRB_BINARY,name); }
  model.update(); // run update to use model inserted variables
  try {
    //if (time_limit >= 0) model.getEnv().set(GRB_DoubleParam_TimeLimit,time_limit);
    //model.getEnv().set(GRB_DoubleParam_ImproveStartTime,10); //try better sol. aft. 10s
    // if (cutoff > 0) model.getEnv().set(GRB_DoubleParam_Cutoff, cutoff );

    ConnectivityCuts cb = ConnectivityCuts(T , x);
    model.setCallback(&cb);
    model.update();
    //model.write("model.lp"); system("cat model.lp");
    model.optimize();

    double soma=0.0;
    for (DiNodeIt v(g);v!=INVALID;++v) vcolor[v]=BLUE; // all nodes BLUE
    for (int i=0;i<T.nt;i++) vcolor[T.V[i]]=MAGENTA; // change terminals to MAGENTA
    vcolor[T.V[0]]=RED; // change root to RED
    for (Digraph::ArcIt e(g); e!=INVALID; ++e) {
      lpvar[e] = x[e].get(GRB_DoubleAttr_X);
      if (lpvar[e] > 1.0 - EPS) { soma += weight[e]; ecolor[e] = RED; }
      else ecolor[e] = NOCOLOR; }
    cout << "Steiner Tree Value = " << soma << endl;
    ViewListDigraph(g,vname,px,py,vcolor,ecolor,
	"Steiner Tree cost in graph with "+IntToString(T.nnodes)+
	" nodes and "+IntToString(T.nt)+" terminals: "+DoubleToString(soma));
  } catch (...) {cout << "Error during callback..." << endl; }
  return 0;
}