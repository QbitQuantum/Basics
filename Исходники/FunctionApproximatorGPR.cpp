void FunctionApproximatorGPR::train(const MatrixXd& inputs, const MatrixXd& targets)
{
  if (isTrained())  
  {
    cerr << "WARNING: You may not call FunctionApproximatorGPR::train more than once. Doing nothing." << endl;
    cerr << "   (if you really want to retrain, call reTrain function instead)" << endl;
    return;
  }
  
  assert(inputs.rows() == targets.rows());
  assert(inputs.cols()==getExpectedInputDim());

  const MetaParametersGPR* meta_parameters_gpr = 
    dynamic_cast<const MetaParametersGPR*>(getMetaParameters());
  
  double max_covar = meta_parameters_gpr->maximum_covariance();
  VectorXd sigmas = meta_parameters_gpr->sigmas();
  
  
  // Compute the gram matrix
  // In a gram matrix, every input point is itself a center
  MatrixXd centers = inputs;
  // Replicate sigmas, because they are the same for each data point/center
  MatrixXd widths = sigmas.transpose().colwise().replicate(centers.rows()); 

  MatrixXd gram(inputs.rows(),inputs.rows());
  bool normalize_activations = false;
  bool asymmetric_kernels = false;
  BasisFunction::Gaussian::activations(centers,widths,inputs,gram,normalize_activations,asymmetric_kernels);
  
  gram *= max_covar;

  setModelParameters(new ModelParametersGPR(inputs,targets,gram,max_covar,sigmas));
  
}