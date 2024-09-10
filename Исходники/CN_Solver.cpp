void LpSolver::addObjective(string mode, 
	CplexConverter& cplexConverter, IloModel model, 
	IloNumVarArray x, IloRangeArray c){
	
	// cerr << mode << endl;

	IloEnv env = model.getEnv();

	if (mode == "MIN_SRC_COST"){

		IloExpr cost(env);

		// add cost to all atomic edges
		for (int i = 0; i < cplexConverter.variables.size(); ++i){
			cost += x[i] * cplexConverter.variables[i].interest_rate;
		}

		for(auto &atoIn : cplexConverter.src->atomicEdge_in){
			int aeId = atoIn.second->atomicEdgeId;
			for (int j = 0; j < cplexConverter.atomicIdToVarIdDict[aeId].size(); j++){
				// var Id
				int vId = cplexConverter.atomicIdToVarIdDict[aeId][j];
				cost += cplexConverter.variables[vId].interest_rate * x[vId];

				// cout << "adding " << cplexConverter.variables[vId].interest_rate 
				// 		<< " * " << vId << endl;
			}
		}
		model.add(IloMinimize(env, cost));

	} else if (mode == "MIN_CREDIT_COST") {

		IloExpr cost(env);

		// add cost to all atomic edges
		for (int i = 0; i < cplexConverter.variables.size(); ++i){
			cost += x[i] * cplexConverter.variables[i].interest_rate;
		}

		for (int i = 0; i < cplexConverter.variables.size(); ++i){
			int aeId = cplexConverter.variables[i].atomicEdgeId;
			if (!cplexConverter.graph->atomicEdges[aeId]->isDebt){
				cost += x[i];
			}
		}
		model.add(IloMinimize(env, cost));

	} else if (mode == "MIN_CREDIT_SRC") {

		IloExpr cost(env);

		for(auto &atoIn : cplexConverter.src->atomicEdge_in){
			int aeId = atoIn.second->atomicEdgeId;
			for (int j = 0; j < cplexConverter.atomicIdToVarIdDict[aeId].size(); j++){
				// var Id
				int vId = cplexConverter.atomicIdToVarIdDict[aeId][j];
				cost += cplexConverter.variables[vId].interest_rate * x[vId];
				if (!cplexConverter.graph->atomicEdges[aeId]->isDebt){
					cost += x[vId];
				}			

				// cout << "adding " << cplexConverter.variables[vId].interest_rate 
				// 		<< " * " << vId << endl;
			}
		}
		model.add(IloMinimize(env, cost));

	}	else if (mode == "MIN_DEGREE_SRC") {

		IloExpr cost(env);

		for(auto &atoIn : cplexConverter.src->atomicEdge_in){
			int aeId = atoIn.second->atomicEdgeId;
			AtomicEdge* atEdge = cplexConverter.graph->atomicEdges[aeId];			
			for (int j = 0; j < cplexConverter.atomicIdToVarIdDict[aeId].size(); j++){
				// var Id
				int vId = cplexConverter.atomicIdToVarIdDict[aeId][j];
				cost += cplexConverter.variables[vId].interest_rate * x[vId];					
				if (!atEdge->isDebt){
					cost += atEdge->nodeTo->degree * x[vId];
				} else {
					cost += atEdge->nodeFrom->degree * x[vId];
				}
				// cout << "adding " << cplexConverter.variables[vId].interest_rate 
				// 		<< " * " << vId << endl;
			}
		}
		model.add(IloMinimize(env, cost));

	}	
		else if (mode == "MAX_IR_COST") {

		IloExpr cost(env);
		// add cost to all atomic edges
		for (int i = 0; i < cplexConverter.variables.size(); ++i){
			cost += 100 - x[i] * cplexConverter.variables[i].interest_rate;
		}
		model.add(IloMinimize(env, cost));

	}	else if (mode == "MIN_SUMIR_COST") {

		IloExpr cost(env);
		// add cost to all atomic edges
		for (int i = 0; i < cplexConverter.variables.size(); ++i){
			cost += x[i] * cplexConverter.variables[i].interest_rate;
		}
		model.add(IloMinimize(env, cost));

	} 	else if (mode == "MIN_DEGREE_COST") {

		IloExpr cost(env);

		// add cost to all atomic edges
		for (int i = 0; i < cplexConverter.variables.size(); ++i){
			cost += x[i] * cplexConverter.variables[i].interest_rate;
		}
		
		for (int i = 0; i < cplexConverter.variables.size(); ++i){
			int aeId = cplexConverter.variables[i].atomicEdgeId;
			AtomicEdge* atEdge = cplexConverter.graph->atomicEdges[aeId];
			
			for (int j = 0; j < cplexConverter.atomicIdToVarIdDict[aeId].size(); j++){
				// var Id
				int vId = cplexConverter.atomicIdToVarIdDict[aeId][j];
				if (!atEdge->isDebt){
					cost += atEdge->nodeTo->degree * x[vId];
				} else {
					cost += atEdge->nodeFrom->degree * x[vId];
				}	
			}

		}
		model.add(IloMinimize(env, cost));

	} else {
		// default
		model.add(IloMinimize(env, 1));
	}


}