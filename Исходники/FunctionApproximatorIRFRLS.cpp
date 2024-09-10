void FunctionApproximatorIRFRLS::train(const MatrixXd& inputs, const MatrixXd& targets)
{
  if (isTrained())  
  {
    cerr << "WARNING: You may not call FunctionApproximatorIRFRLS::train more than once. Doing nothing." << endl;
    cerr << "   (if you really want to retrain, call reTrain function instead)" << endl;
    return;
  }
  
  assert(inputs.rows() == targets.rows()); // Must have same number of examples
  assert(inputs.cols()==getExpectedInputDim());
  
  const MetaParametersIRFRLS* meta_parameters_irfrls = 
    static_cast<const MetaParametersIRFRLS*>(getMetaParameters());

  int nb_cos = meta_parameters_irfrls->number_of_basis_functions_;

  // Init random generator.
  boost::mt19937 rng(getpid() + time(0));

  // Draw periodes
  boost::normal_distribution<> twoGamma(0, sqrt(2 * meta_parameters_irfrls->gamma_));
  boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > genPeriods(rng, twoGamma);
  MatrixXd cosines_periodes(nb_cos, inputs.cols());
  for (int r = 0; r < nb_cos; r++)
    for (int c = 0; c < inputs.cols(); c++)
      cosines_periodes(r, c) = genPeriods();

  // Draw phase
  boost::uniform_real<> twoPi(0, 2 * boost::math::constants::pi<double>());
  boost::variate_generator<boost::mt19937&, boost::uniform_real<> > genPhases(rng, twoPi);
  VectorXd cosines_phase(nb_cos);
  for (int r = 0; r < nb_cos; r++)
      cosines_phase(r) = genPhases();

  MatrixXd proj_inputs;
  proj(inputs, cosines_periodes, cosines_phase, proj_inputs);

  // Compute linear model analatically
  double lambda = meta_parameters_irfrls->lambda_;
  MatrixXd toInverse = lambda * MatrixXd::Identity(nb_cos, nb_cos) + proj_inputs.transpose() * proj_inputs;
  VectorXd linear_model = toInverse.inverse() *
    (proj_inputs.transpose() * targets);

  setModelParameters(new ModelParametersIRFRLS(linear_model, cosines_periodes, cosines_phase));
}