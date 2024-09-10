bool FirthRegression::FitFirthModel(Matrix & X, Vector & succ, Vector& total, int nrrounds) {
  this-> Reset(X);

  G_to_Eigen(X, &this->w->X);
  G_to_Eigen(succ, &this->w->succ);
  G_to_Eigen(total, &this->w->total);

  int rounds = 0;
  // double lastDeviance, currentDeviance;
  Eigen::MatrixXf xw; // W^(1/2) * X
  // Newton-Raphson
  while (rounds < nrrounds) {
    // beta = beta + solve( t(X)%*%diag(p*(1-p)) %*%X) %*% t(X) %*% (Y-p);
    this->w->eta = this->w->X * this->w->beta;
    this->w->p = (-this->w->eta.array().exp() + 1.0).inverse();
    this->w->V = this->w->p.array() * (1.0 - this->w->p.array()) * this->w->total.array();

    xw = (this->w->V.array().sqrt().matrix().asDiagonal() * this->w->X).eval();
    this->w->D = xw.transpose() * xw; // this->w->X.transpose() * this->w->V.asDiagonal() * this->w->X; // X' V X
    this->w->covB = this->w->D.eval().llt().solve(Eigen::MatrixXf::Identity(this->w->D.rows(), this->w->D.rows()));
    // double rel = ((this->w->D * this->w->covB).array() - Eigen::MatrixXf::Identity(this->w->D.rows(), this->w->D.rows()).array()).matrix().norm() / this->w->D.rows() / this->w->D.rows();
    // if (rel > 1e-6) { // use relative accuracy to evalute convergence
    if ((this->w->D * this->w->covB - Eigen::MatrixXf::Identity(this->w->D.rows(), this->w->D.rows())).norm() > 1e-3) {
      // cannot inverse
      return false;
    }
    this->w->h = (xw.transpose() * this->w->covB * xw).diagonal();
    this->w->r = this->w->X.transpose() * (this->w->succ.array() - this->w->total.array() * this->w->p.array()
                                           + this->w->total.array() * this->w->h.array() * (0.5 - this->w->p.array())).matrix();
    this->w->delta_beta = this->w->covB * this->w->r;
    this->w->beta += this->w->delta_beta;
    if (rounds > 1 && (this->w->beta.norm() > 0 && this->w->delta_beta.norm() / this->w->beta.norm() < 1e-6)) {
      rounds = 0;
      break;
    }
    rounds ++;
  }
  if (rounds == nrrounds)
  {
    printf("Not enough iterations!");
    return false;
  }

  Eigen_to_G(this->w->beta, &B);
  Eigen_to_G(this->w->covB, &covB);
  Eigen_to_G(this->w->p, &p);
  Eigen_to_G(this->w->V, &V);

  return true;
}