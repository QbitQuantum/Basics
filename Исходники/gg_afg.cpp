void solve(Instance inst, bool hsol = false){    
    clock_t t0 = CURTIME;
    
    ArcflowMKP graph(inst);    
    const vector<Item> &items = inst.items;   
    
    GRBEnv* env = new GRBEnv();
    GRBModel master = GRBModel(*env);    
    master.set(GRB_StringAttr_ModelName, "GG");
    master.getEnv().set(GRB_IntParam_OutputFlag, 0);
    master.getEnv().set(GRB_IntParam_Threads, 1);          
    master.getEnv().set(GRB_IntParam_Method, 0); 

    GRBConstr rows[inst.m];
    for(int i = 0; i < inst.m; i++){
        GRBLinExpr lin = 0;
        rows[i] = master.addConstr(lin >= items[i].demand);
    }
    master.update();
        
    vector<GRBVar> vars;
    for(int i = 0; i < inst.m; i++){        
        GRBColumn col = GRBColumn();        
        col.addTerm(1, rows[i]);
        vars.push_back(master.addVar(0, GRB_INFINITY, 1, GRB_CONTINUOUS, col));
    }    
    
    printf("m: %d\n", inst.m);
    vector<double> values(inst.m);
    for(int itr = inst.m; ; itr++){
        master.optimize();
        printf("%d: %.6f (%.2fs)\n", itr, master.get(GRB_DoubleAttr_ObjVal), TIMEDIF(t0));        
        for(int i = 0; i < inst.m; i++)
            values[i] = rows[i].get(GRB_DoubleAttr_Pi);            

        vector<int_pair> sol = graph.knapsack(values, 1+EPSILON);
        if(sol.empty()) break;
        
        GRBColumn col = GRBColumn();        
        ForEach(itr, sol) col.addTerm(itr->second, rows[itr->first]);
        
        vars.push_back(master.addVar(0, GRB_INFINITY, 1, GRB_CONTINUOUS, col));
        master.update();
    }
        
    printf("zlp: %.6f\n", master.get(GRB_DoubleAttr_ObjVal));
    printf("nvars: %d\n", master.get(GRB_IntAttr_NumVars));
    printf("time: %.2fs\n", TIMEDIF(t0));
    
    if(hsol){ // find an heuristic solution if hsol = true
        ForEach(itr, vars)
            itr->set(GRB_CharAttr_VType, GRB_INTEGER);
        
        master.getEnv().set(GRB_IntParam_OutputFlag, 1);
        master.getEnv().set(GRB_IntParam_Threads, 1);
        //master.getEnv().set(GRB_IntParam_Presolve, 1);       
        //master.getEnv().set(GRB_IntParam_Method, 2);
        master.getEnv().set(GRB_IntParam_MIPFocus, 1);
        master.getEnv().set(GRB_DoubleParam_Heuristics, 1);
        master.getEnv().set(GRB_DoubleParam_MIPGap, 0);
        master.getEnv().set(GRB_DoubleParam_MIPGapAbs, 1-1e-5);  
        
        master.optimize();
        printf("Total run time: %.2f seconds\n", TIMEDIF(t0));
    }
    
    free(env);
}