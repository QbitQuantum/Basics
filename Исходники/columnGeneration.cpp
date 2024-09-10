IloNum columnGeneration (IloCplex2 subSolver, IloCplex rmpSolver, 
	IloNumVarArray3 x, IloNumVarArray2 z, IloNumVarArray2 lambda,
	IloObjective2 reducedCost, IloObjective rmpObj,
	IloRangeArray2 maintConEng, IloRangeArray2 removeMod, IloRangeArray2 convex,
	IloNumArray2 addXCol, IloNumArray addZCol,
	IloNumArray2 priceRemoveMod, IloNumArray2 priceMaintConEng, IloNumArray priceConvex, 
	const IloNumArray2 compCosts, const IloNumArray convexityCoef,
	IloBool weightedDW_in, IloBool allowCustomTermination,
	IloInt relChangeSpan, IloNum relChange) {

	// extract optimization enviroment
	IloEnv env = rmpSolver.getEnv();
	
	
	// ANALYSIS: write to file
	const char*	output = "results/colGen_analysis.dat";
	
	// variable declarations..	
	
	// loop counters
	IloInt i, m, t, testCounter;

	testCounter = 0;

	// declare two clock_t objects for start and end time.		
	clock_t start, end;

	// declare an array of size NR_OF_MODULES to temporarily hold the
	// reduced costs from the NR_OF_MODULES different subproblems.
	IloNumArray redCosts(env, NR_OF_MODULES);

	IloBool weightedDW = weightedDW_in;

	// declare an array to hold the RMP objective values: e.g. add
	// one value to array for each iteration.
//	IloNumArray objValues(env);

	// declare an array to hold the lower bounds for the full MP, given
	//  	z(RMP)* + sum_[m in subproblems] redCost(m)^* <= z(full MP)^* <= z(RMP)^*
//	IloNumArray lowerBounds(env);

	// declare two temp IloNum objects for temporarily hold rmp objective value
	// and full MP lower bound. (full: MP with _all_ columns availible).
	IloNum tempRmpObj, tempLowerBound, bestLowerBound;
	bestLowerBound = -IloInfinity;

	// also use a num-array to hold the REL_CHANGE_SPAN most
	// recent RMP objective values. Used to the relative change
	// break criteria (if improvement by col-gen becomes to
	// "slow"/"flat").
	IloNumArray recentObjValues(env, REL_CHANGE_SPAN);

	// declare and initiate col-gen iteration counter
	IloInt itNum = 0;

	// ---- weighted DW decomp - for less trailing in colgen.
	//IloBool weightedDW = IloTrue;

	// declare two IloNum-array to hold all 2x (NR_OF_MODULES x TIME_SPAN)
	// dual vars - or specific, best dual vars (giving highest lower bound)
	IloNumArray2 dualsModBest(env);
	IloNumArray2 dualsEngBest(env);

	// temp..
	//IloBoolArray continueSub(env, NR_OF_MODULES);
	
	// allocate memory for sub-arrays
	for (m = 0; m < NR_OF_MODULES; m++) {

		dualsModBest.add(IloNumArray(env,TIME_SPAN));	
		dualsEngBest.add(IloNumArray(env,TIME_SPAN));

		//continueSub[m] = IloTrue;

		// and maybe: initially set all dual vars to 0?
		for (t = 0; t < TIME_SPAN; t++) {
			dualsModBest[m][t] = 0.0;
			dualsEngBest[m][t] = 0.0;
		}
	}

	// also, a weight for weighted DW:
	IloNum weight = 2.0;

	// counter number of improvements of "best duals"
	IloInt nrOfImprov = 0;

	// const used in weigt
	IloNum weightConst = DW_WEIGHT;

	// initiate numarray for recent objective values
	// UPDATE: this is not really needed now as we check the
	// relative change break criteria only when we know this
	// vector has been filled by REL_CHANGE_SPAN "proper" values...
	recentObjValues[0] = 0.0;
	for (i = 1; i < REL_CHANGE_SPAN; i++) {
		recentObjValues[i] = 0.0;
	}						

	// model before generation start:
	//rmpSolver.exportModel("rmpModel.lp");

	//write results to file
/*	ofstream outFile(output);

	outFile << "Writing out results from initial column generation, T=" << TIME_SPAN << endl
		<< "Form: [(itNum) (dual solution value) (upper bound = tempRmpObj)]" << endl << endl;*/


	//cout << endl << "WE GOT OURSELVES A SEGMENTATION FAULT!" << endl;

	// start timer
	start = clock();

	// also use an alternative time counter..
	time_t start2, end2;
	start2 = time(NULL);

	// loop until break...
	for (;;) {

		// increase iteration counter
		itNum++;

		// solve master
		if ( !rmpSolver.solve() ) {
       			env.error() << "Failed to optimize RMP." << endl;
			throw(-1);
		}
		
		// get the rmp objective value
		tempRmpObj = rmpSolver.getValue(rmpObj);

		// add to objective value array (size: iterations)
	//	objValues.add(tempRmpObj);

		// update recentObjValues:
		recentObjValues.remove(0);
			// remove oldest:
		recentObjValues.add(tempRmpObj);
			// save newest		

		// report something (... report1() )
		// UPDATE: colgen is to quick for anything to see anything reported... so skip this

		// update weight: weight = min{ 2,
		if (itNum>1) { 
			weight = (IloNum(itNum - 1) + IloNum(nrOfImprov))/2;
		}
		if ( weight > weightConst) {
			weight = weightConst;
		}	


		// update duals
		// -> updates obj. functions for subproblems (w.r.t. duals)
		for (m = 0; m < NR_OF_MODULES; m++) {

			//cout << "weight = " << weight << endl;
			//cin.get();

			for (t = 0; t < TIME_SPAN; t++) {

				// if we try weightedWD decomp:
				// for first iteration: just extract duals which will become best duals
				if (itNum > 1 && weightedDW) {

					// price associated with const. removeMod
					priceRemoveMod[m][t] = (rmpSolver.getDual(removeMod[m][t]))/weight + (weight-1)*(dualsModBest[m][t])/weight;

					// price associated with const. maintConEng
					priceMaintConEng[m][t] = (rmpSolver.getDual(maintConEng[m][t]))/weight + (weight-1)*(dualsEngBest[m][t])/weight;	

				}
				// normally:
				else {

					// price associated with const. removeMod
					priceRemoveMod[m][t] = rmpSolver.getDual(removeMod[m][t]);

					// price associated with const. maintConEng
					priceMaintConEng[m][t] = rmpSolver.getDual(maintConEng[m][t]);
				}

				//cout << "priceRemoveMod[m][t] = " << priceRemoveMod[m][t] << endl;

				// update subproblem obj. function coefficients for z[m][t] vars:
				reducedCost[m].setLinearCoef(z[m][t],-(priceRemoveMod[m][t] + priceMaintConEng[m][t]));
			} 

			//cin.get();

			// rmpSolver.getDuals(priceRemoveMod[m], removeMod[m]);
			// rmpSolver.getDuals(priceMaintConEng[m], maintConEng[m]);
			// priceConvex[m] = -rmpSolver.getDual(convex[m][0]);
				
			// if we try weightedWD decomp:
			// for first iteration: just extract duals which will become best duals
	/*		if (itNum > 1 && weightedDW) {

				// price associated with convexity constraint
				priceConvex[m] = -abs(rmpSolver.getDual(convex[m][0]))/weight - (weight-1)*(dualsConvBest[m])/weight;
			} */
		
			// price associated with convexity constraint
			priceConvex[m] = -abs(rmpSolver.getDual(convex[m][0]));

			// update subproblem obj. function's constant term
			reducedCost[m].setConstant(priceConvex[m]);
			
		} // END of updating duals

		// solve subproblems
		for (m = 0; m < NR_OF_MODULES; m++) {

			//if (continueSub[m]) {

				// solve subproblem m
				cout << endl << "Solving subproblem #" << (m+1) << "." << endl;
				if ( !subSolver[m].solve() ) {
       					env.error() << "Failed to optimize subproblem #" << (m+1) << "." << endl;
       					throw(-1);
				}
		
				// extract reduced cost: subSolver[m].getValue(reducedCost[m])
				// into a IloNumArray(env, NR_OF_MODULES) at position m.				
				redCosts[m] = subSolver[m].getValue(reducedCost[m]);

				//env.out() << endl << "Reduced cost for problem #" << (m+1) << ":" << redCosts[m] << endl;

				// if reduced cost is negative, att optimal solution to
				// column pool Q(m)
				if (!(redCosts[m] > -RC_EPS)) {
					
					// add column		
					addColumn(subSolver[m], x[m], z[m], lambda[m], rmpObj, maintConEng[m], removeMod[m],
						convex[m], addXCol, addZCol, compCosts[m], convexityCoef);

					//env.out() << endl << "Added a column to pool Q(" << (m+1) 
					//	<< "). Lambda[" << (m+1) << "].size = " << lambda[m].getSize() << endl; 

					testCounter++;
				}	
				//else {
				//	continueSub[m] = IloFalse;
				//}
			//}
			//else {
			//	redCosts[m] = 0;
			//}	


		} // END of solving subproblems (for this iteration)

		// calculate lower bound on full MP
		tempLowerBound = tempRmpObj + sumArray(redCosts);

		// update best lower bound
		if (tempLowerBound > bestLowerBound) {
			bestLowerBound = tempLowerBound;
		
			// increase counter for number of improved "best duals".
			nrOfImprov++;

			//cout << endl << "WHATEVAAAH" << endl;
			//cin.get();

			// save best duals
			for (m = 0; m < NR_OF_MODULES; m++) {
				for (t = 0; t < TIME_SPAN; t++) {			
					dualsModBest[m][t] = priceRemoveMod[m][t];
					dualsEngBest[m][t] = priceMaintConEng[m][t];
				}
			}
		}						

		// update lower bounds vector
		//lowerBounds.add(bestLowerBound);
		
		// ANALYSIS: print out to file:
		// [(itNum) (dual solution value) (upper bound = tempRmpObj)]
		//outFile << itNum << " " << tempLowerBound << " " << tempRmpObj << endl;

		// if the smallest reduced cost in the updated red-cost vector 
		// with NR_OF_MODULES entries is greater than -RC_EPS: break
		// otherwise, repeat.
		if (minMemberValue(redCosts) > -RC_EPS) {
			env.out() << endl << "All reduced costs non-negative: breaking." << endl;
			bestLowerBound = tempRmpObj;
			break;
		}

		// if relative change in objective value over the last REL_CHANGE_SPAN iterations is
		// less than REL_CHANGE, break.
		//if (allowCustomTermination && (itNum >= REL_CHANGE_SPAN) && (relativeImprovement(recentObjValues) < REL_CHANGE)) {
		if (allowCustomTermination && (itNum >= relChangeSpan) && (relativeImprovement(recentObjValues) < relChange)) {
			env.out() << endl << "Relative change smaller than pre-set acceptance: breaking." << endl;
			break;
		}													

		// if the gap currentUpperBound - currentLowerBound is small enough, break
		if ((tempRmpObj - bestLowerBound) < RC_EPS) {
			env.out() << endl << "Lower<>Upper bound gap less than pre-set acceptance: breaking." << endl;
			cout << endl << "(tempRmpObj - bestLowerBound) = " << (tempRmpObj - bestLowerBound) << endl;
			bestLowerBound = tempRmpObj;
			break;
		}


	} // END of column generation.
		
	// alternative: print the REL_CHANGE_SPAN most recent RMP objective values		
	env.out() << endl;
	/*for (i = 0; i < recentObjValues.getSize(); i++) {
		env.out() << "Recent #" << (i+1) << ": " << recentObjValues[i] << endl;
	}*/

	// solve master using final column setup
      	if ( !rmpSolver.solve() ) {
        	env.error() << "Failed to optimize RMP." << endl;
        	throw(-1);
      	}

	// also add final objective value to objective value array (size: iterations)
//	objValues.add(rmpSolver.getValue(rmpObj));

	// create IloNum object and extract the final RMP objective value.
	IloNum finalObj;
	finalObj = rmpSolver.getValue(rmpObj);

	// end program time counter(s)
	end = clock();
	end2 = time(NULL);

	// print result to file
	//outFile << endl << endl << "Final objective value: " << finalObj << endl
	//	<< "Time required for execution: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds." << endl;

	// outfile.close()	
	//outFile.close(); 
	itNum = 0;
		// re- use iteration counter to count total number of columns generated

	// nr of columns generated from each subproblem		
	for (m = 0; m < NR_OF_MODULES; m++) {
		// ### outFile << "Number of columns generated from subproblem (m = " << m << "): " << (lambda[m].getSize() - 1) << endl;
		cout << "Number of columns generated from subproblem (m = " << m << "): " << (lambda[m].getSize() - 1) << endl;
		//outFile << "Pool (m = " << m << "): " << (lambda[m].getSize() - 1) << endl;
		
		itNum += lambda[m].getSize();
	}
 
	// ###
/*	outFile << endl << "Total number of columns generated: " << itNum << endl;
	outFile << "Time required for column generation: " << (double)(end-start)/CLOCKS_PER_SEC << " seconds." << endl;
	outFile << "ALTERNATIVE: Time required for colgen: " << end2-start2 << " seconds." << endl;
	outFile << "RMP objective function cost: " << finalObj << endl << endl;
	//outFile << "Objective function values for each iteration: " << endl;		
	//outFile << objValues;
	//outFile << endl << endl << "Lower bounds for each iteration: " << endl; 
	//outFile << lowerBounds;
	outFile.close(); */

	//cout << "Initial column generation complete, press enter to continue..." << endl;
	//cin.get();


	// print some results..
	/*env.out() << endl << "RMP objective function cost: " << finalObj << endl;
	env.out() << endl << "Size of objective value vector: " << objValues.getSize() << endl;
	env.out() << endl << "Nr of iterations: " << itNum << endl;	

	cout << endl << "Number of new columns generated: " << testCounter << endl;*/		

	// Note: to explicit output (void function), ass columns are added implicitely via 
	// income argument pointers.		
					
	// clear memory assigned to temporary IloNumArrays:
	redCosts.end();
	//objValues.end();	
	//lowerBounds.end();	
	recentObjValues.end();

	// save best duals
	for (m = 0; m < NR_OF_MODULES; m++) {
		dualsModBest[m].end();
		dualsEngBest[m].end();
	}
	dualsModBest.end();
	dualsEngBest.end();
	//continueSub.end();	

	//cout << endl << "NR OF IMPROVEMENTS: " << nrOfImprov << endl;
	//cin.get();

	// return lower bound
	return bestLowerBound;	

} // END of columnGeneration()