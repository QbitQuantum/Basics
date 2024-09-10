void CParam::initizalize(CData &Data, int nComp, CFeasibilityMap &FM, Uniform &randUnif, int n_simul){
  // Set the minimum value of (no. of correct records)/(no. of all records)
  toolarge_nout = (1-min_Prob_A)/min_Prob_A * Data.n_sample ;

  n_var = Data.n_var;
  n_var_independent = n_var - Data.n_balance_edit;
  K = nComp;
  n_sample = Data.n_sample;

  alpha = 1.0 ;
  Phi = IdentityMatrix(n_var_independent) * 5.0;
  init_pi();
  init_sigmamu(Data);
  init_Y_in(Data);
  init_z_in();

  S_Mat = Data.initial_S_Mat.t();
  init_logUnif_y_tilde(Data,FM,randUnif,n_simul);

  n_z = ColumnVector(K); n_z = 0 ;
  Sigma_k_inv_ll = Matrix(K,n_var_independent);  Sigma_k_inv_ll=0.0;
  X_bar= Matrix(n_var_independent,K); X_bar = 0.0 ;
  CalculateInitProbA(Data);
}