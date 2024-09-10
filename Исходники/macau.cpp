void Macau::init() {
  unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
  if (priors.size() != 2) {
    throw std::runtime_error("Only 2 priors are supported.");
  }
  init_bmrng(seed1);
  MatrixXd* U = new MatrixXd(num_latent, Y.rows());
  MatrixXd* V = new MatrixXd(num_latent, Y.cols());
  U->setZero();
  V->setZero();
  samples.push_back( std::move(std::unique_ptr<MatrixXd>(U)) );
  samples.push_back( std::move(std::unique_ptr<MatrixXd>(V)) );
  noise->init(Y, mean_rating);
}