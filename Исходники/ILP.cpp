std::map<std::string,int>
ILP(char* argv)
{

	map<string, int > results;
	GRBVar* vars = 0;

//	if (argc < 2) {
//		cout << "Usage: lp_c++ filename" << endl;
//		return 1;
//	}

  try {
    GRBEnv env = GRBEnv();
    GRBModel model = GRBModel(env, argv);
    //model.getEnv().set(GRB_DoubleParam_IntFeasTol,1e-6);
   model.getEnv().set(GRB_DoubleParam_Heuristics,0.95);
    model.getEnv().set(GRB_DoubleParam_TimeLimit,timeMax);
    model.getEnv().set(GRB_DoubleParam_MIPGap, ilpGap);
    vars = model.getVars();
    model.optimize();

    int optimstatus = model.get(GRB_IntAttr_Status);

    if (optimstatus == GRB_INF_OR_UNBD) {
      model.getEnv().set(GRB_IntParam_Presolve, 0);
      model.optimize();
      optimstatus = model.get(GRB_IntAttr_Status);
    }

    if (optimstatus == GRB_OPTIMAL) {
      double objval = model.get(GRB_DoubleAttr_ObjVal);
      cout << "Optimal objective: " << objval << endl;
      for(int i =0; i<model.get(GRB_IntAttr_NumVars);i++){
    	  	string varName = vars[i].get(GRB_StringAttr_VarName);
    	  	results[varName] = vars[i].get(GRB_DoubleAttr_X);

    	 // 	cout << vars[i].get(GRB_StringAttr_VarName) << " " << vars[i].get(GRB_DoubleAttr_X) << endl;

      }
      ofstream varNames;
      ofstream varResults;
      varNames.open("varName.txt");
      varResults.open("varResults.txt");


      for(int i =0; i<model.get(GRB_IntAttr_NumVars);i++){
          	  	string varName = vars[i].get(GRB_StringAttr_VarName);
          	  	results[varName] = vars[i].get(GRB_DoubleAttr_X)+0.5; // +0.5 to make sure its round

          	  if(varName == "co2o3storagey3" ){
          	  				cout << "gotte ya" <<endl;
          	  }

          	  	varNames << varName << "\n";
          	  	varResults << varName << "     "<< results[varName] << "\n";

          	  	//cout << vars[i].get(GRB_StringAttr_VarName) << " " << vars[i].get(GRB_DoubleAttr_X) << endl;

            }

      varNames.close();
      varResults.close();

      cout << "size of results is " << sizeof(results)*results.size()<< endl;
      cout << "using mapSize function, size is " << mapSize(results)<<endl;
      toFile(results,mapSize(results));


    } else if (optimstatus == GRB_INFEASIBLE) {
      cout << "Model is infeasible" << endl;

      // compute and write out IIS

      //model.computeIIS();
      //model.write("model.ilp");
    } else if (optimstatus == GRB_UNBOUNDED) {
      cout << "Model is unbounded" << endl;
    } else {
      cout << "Optimization was stopped with status = "
           << optimstatus << endl;

      double objval = model.get(GRB_DoubleAttr_ObjVal);
           cout << "Optimal objective: " << objval << endl;
           for(int i =0; i<model.get(GRB_IntAttr_NumVars);i++){
         	  	string varName = vars[i].get(GRB_StringAttr_VarName);
         	  	results[varName] = vars[i].get(GRB_DoubleAttr_X);

         	 // 	cout << vars[i].get(GRB_StringAttr_VarName) << " " << vars[i].get(GRB_DoubleAttr_X) << endl;

           }
           ofstream varNames;
           ofstream varResults;
           varNames.open("varName.txt");
           varResults.open("varResults.txt");


           for(int i =0; i<model.get(GRB_IntAttr_NumVars);i++){
               	  	string varName = vars[i].get(GRB_StringAttr_VarName);
               	  	results[varName] = vars[i].get(GRB_DoubleAttr_X)+0.5; // +0.5 to make sure its round

               	  if(varName == "co2o3storagey3" ){
               	  				cout << "gotte ya" <<endl;
               	  }

               	  	varNames << varName << "\n";
               	  	varResults << varName << " = "<< results[varName] << "\n";

               	  	//cout << vars[i].get(GRB_StringAttr_VarName) << " " << vars[i].get(GRB_DoubleAttr_X) << endl;

                 }

           varNames.close();
           varResults.close();
    }

  } catch(GRBException e) {
    cout << "Error code = " << e.getErrorCode() << endl;
    cout << e.getMessage() << endl;
  } catch (...) {
    cout << "Error during optimization" << endl;
  }

  return results;

  //return 0;
}