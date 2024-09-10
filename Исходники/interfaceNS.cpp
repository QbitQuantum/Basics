// we process each dimension individually using this function
RcppExport SEXP noSplitcv(SEXP R_x,SEXP R_xv,SEXP R_ngroup, SEXP R_xtest,SEXP R_ngrouptest ,SEXP R_args){

	NumericVector x(R_x);
	NumericVector xv(R_xv);
	NumericVector xtest(R_xtest);
	NumericVector ngroup(R_ngroup);
	NumericVector ngrouptest(R_ngrouptest);
	List args(R_args);
  
	std::string weights = Rcpp::as<std::string>(args["weights"]); 
	double gamma = Rcpp::as<double>(args["gamma"]); 
	double epsilon = Rcpp::as<double>(args["epsilon"]);
	NumericMatrix W = args["W"];
	NumericVector lambdalist = args["lambdalist"];

	NumericVector error(lambdalist.length());

	vector<double> sl = calculateSlope(x,ngroup,xv,weights,gamma,W,x.length());
 
	Group *G = maketree(&x[0], x.length(), &sl[0],&ngroup[0],epsilon);

	error_cv(G,&lambdalist[0],lambdalist.length(),&xtest[0], &ngrouptest[0],&error[0]);

	delete_tree(G); 

	return(error);
}