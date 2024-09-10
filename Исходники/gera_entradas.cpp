void seleciona_propagandas(int n, double C, double V[N], double P[N], double w[N][N], int S[N], double *UpperBound, long maxtime) {
	GRBVar y[N][N];
	GRBVar x[N];

	int seed=0;
	GRBEnv env = GRBEnv();
	GRBModel model = GRBModel(env);
	model.getEnv().set(GRB_IntParam_Seed, seed);
	model.set(GRB_StringAttr_ModelName, "Alocacao Propaganda"); // prob. name
	model.set(GRB_IntAttr_ModelSense, GRB_MAXIMIZE); // is a minimization problem  

	for(int i = 0; i < n; i++) {
		char name[100];
		sprintf(name,"x_%d",i);
		x[i] = model.addVar(0.0, 1.0, V[i],GRB_BINARY, name); 
	}

	for( int i = 0; i < n; i++) {

		for(int j = i+1; j < n; j++) {
			char name[100];
			sprintf(name,"y_%d_%d",i, j);
			y[i][j] = model.addVar(0.0, 1.0, w[i][j], GRB_BINARY, name); 
		}
	}
	
	model.update();
	
	GRBLinExpr expr;
	for(int i = 0; i < n; i++) {
		expr += (x[i] * P[i]);
	}
	model.addConstr(expr <= C);
	model.update();
	
	for(int i = 0; i < n; i++) {
		
		for(int j =i+1; j < n; j++) {
			model.addConstr(y[i][j] <= x[i]);
			model.addConstr(y[i][j] <= x[j]);
			model.addConstr(x[i] + x[j] <= (y[i][j] + 1));
		}
	}
	model.update();
	
	model.write("model.lp");
	
	model.optimize();
	
	*UpperBound = model.get(GRB_DoubleAttr_ObjVal);
	
}