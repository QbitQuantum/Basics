int loadProblem(char *fname,unsigned long len ){
	
	CheckInputArgument(pvApiCtx, 9, 9); // We need total 9 input arguments.
	CheckOutputArgument(pvApiCtx, 1, 1); // Return value will be termination status (0 for no-errors and 1/non-zero for errors)


	double *QItems=NULL,*PItems=NULL,*ConItems=NULL,*conUB=NULL,*conLB=NULL,*varUB=NULL,*varLB=NULL;
	unsigned int nVars,nCons;


	unsigned int arg = 1,temp1,temp2;

	if ( !getIntFromScilab(arg,&nVars) && arg++ && !getIntFromScilab(arg,&nCons) && arg++ &&
		!getDoubleMatrixFromScilab(arg,&temp1,&temp2,&QItems) && temp1 == nVars && temp2 == nVars && arg++ &&
		!getDoubleMatrixFromScilab(arg,&temp1,&temp2,&PItems) && temp2 == nVars && arg++ &&
		!getDoubleMatrixFromScilab(arg,&temp1,&temp2,&ConItems) && temp1 == nCons &&((nCons !=0 && temp2 == nVars)||(temp2==0)) && arg++ &&
		!getDoubleMatrixFromScilab(arg,&temp1,&temp2,&conLB)  && temp2 == nCons && arg++ &&
		!getDoubleMatrixFromScilab(arg,&temp1,&temp2,&conUB)  && temp2 == nCons && arg++ &&
		!getDoubleMatrixFromScilab(arg,&temp1,&temp2,&varLB) && temp2 == nVars && arg++ && 
		!getDoubleMatrixFromScilab(arg,&temp1,&temp2,&varUB) && temp2 == nVars){



		using namespace Ipopt;
		SmartPtr<TNLP> Prob = new QuadNLP(nVars,nCons,QItems,PItems,ConItems,conUB,conLB,varUB,varLB);
		SmartPtr<IpoptApplication> app = IpoptApplicationFactory();
  		app->RethrowNonIpoptException(true);

		// Change some options
		// Note: The following choices are only examples, they might not be
		//       suitable for your optimization problem.
		app->Options()->SetNumericValue("tol", 1e-7);
		app->Options()->SetStringValue("mu_strategy", "adaptive");
		app->Options()->SetStringValue("output_file", "ipopt.out");

		// Indicates whether all equality constraints are linear 
		app->Options()->SetStringValue("jac_c_constant", "yes");
		// Indicates whether all inequality constraints are linear 
		app->Options()->SetStringValue("jac_d_constant", "yes");	
		// Indicates whether the problem is a quadratic problem 
		app->Options()->SetStringValue("hessian_constant", "yes");


		// The following overwrites the default name (ipopt.opt) of the
		// options file
		// app->Options()->SetStringValue("option_file_name", "hs071.opt");
	
		// Initialize the IpoptApplication and process the options
		ApplicationReturnStatus status;
	 	status = app->Initialize();
		if (status != Solve_Succeeded) {
		  	sciprint("\n*** Error during initialization!\n");
			return0toScilab();
	   	 return (int) status;
	 	 }
		 // Ask Ipopt to solve the problem
		 status = app->OptimizeTNLP(Prob);
	
 		if (status == Solve_Succeeded) {
   			sciprint("\n*** The problem solved!\n");
 			 }
  		else {
    			sciprint( "\n*** The problem FAILED!\n");
  			}
	
  		// As the SmartPtrs go out of scope, the reference count
  		// will be decremented and the objects will automatically
  		// be deleted.
	

		}
	else {

		sciprint("\nError:: check argument %d\n",arg);
		return0toScilab();
		return 1;
		}
		
	return0toScilab();
	}