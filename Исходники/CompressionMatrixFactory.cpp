void CompressionMatrixFactory::createCompressionMatrix(Eigen::MatrixXd& cm)
{
  if(cm.rows() < paramDim || cm.cols() < inputDim)
    cm.resize(paramDim, inputDim);
  if(compress)
  {
    cm.setZero();
    fillCompressionMatrix(cm);
  }
  else
    cm = Eigen::MatrixXd::Identity(cm.rows(), cm.cols());
}