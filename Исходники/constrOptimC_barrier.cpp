// [[Rcpp::export]]
NumericVector constrOptimC(NumericVector init, NumericMatrix ui, NumericVector ci){
	double p[4] = {0, 5, 0, .5};
	int n = init.length(), m=ci.length(); 
	size_t nt = init.length(), mt = ci.length();  
	
	RcppGSL::vector<double> x(init);
	RcppGSL::matrix<double> ui1(ui); 
	RcppGSL::vector<double> ci1(ci); 
	double mu_n= 1; 
	double *mu = &mu_n; 
	struct constr_par mypar={ui1, ci1, mu, p}; 
	gsl_set_error_handler_off();
	
	// Initiate multimin minimizer; 
	const gsl_multimin_fdfminimizer_type *T;
  	gsl_multimin_fdfminimizer *s;	
	T = gsl_multimin_fdfminimizer_vector_bfgs;
	s = gsl_multimin_fdfminimizer_alloc (T, n);
	
	// Claim minimizing function; 
  	gsl_multimin_function_fdf my_func;
  	my_func.n = n;
	my_func.f = RC;
	my_func.df = dRC;
	my_func.fdf = RdRC;
	my_func.params = &mypar;
	
	// Claim the original function; 
	gsl_multimin_function_fdf orig_func;
  	orig_func.n = n;
	orig_func.f = FC;
	orig_func.df = gradC;
	orig_func.params = p;
	
	// Initiate the constrained optimization structure; 
	struct constr_multimin my_constrOpitm = {s, my_func, orig_func, 1e-4, 100, 1e-05}; 
	NumericVector out(n+1); 
	gsl_vector *opt;
	opt = gsl_vector_alloc(nt); 
	double f; 
	f = my_constrOpitm.inner_multimin(x, opt);
	out = my_constrOpitm.constr_optim(x); 
	
	gsl_vector_free(ci1); gsl_vector_free(x); gsl_vector_free(opt); 
	gsl_matrix_free(ui1); 
	return(out);
}