//testing initial system for particle filter
// [[Rcpp::export]]
List initPF(NumericMatrix data, NumericVector init_state, int n_particles){
  //initialize system
  int n_iter = data.nrow(); //number of iterations for main particle filter
  NumericVector time_points = data(_,0); //extract time points to run model over
  double loglike = 0.0;
  NumericVector particle_current_state(Dimension(1,init_state.length(),n_particles));
  NumericVector particle_traj(Dimension(n_iter,init_state.length(),n_particles));
  double init_weight = 1 / Rcpp::as<double>(wrap(n_particles));
  NumericVector particle_weight = NumericVector(n_particles,init_weight);
  return(List::create(Named("n_iter")=n_iter,
                      Named("time_points")=time_points,
                      Named("loglike")=loglike,
                      Named("particle_current_state")=particle_current_state,
                      Named("particle_traj")=particle_traj,
                      Named("particle_weight")=particle_weight));
}