double ObjectiveMLSSparse::eval(const VectorXd& x) const
{
  VectorXd vals = -x.transpose() * (*A_);
  double obj = 0.0;
  for(int i = 0; i < vals.rows(); ++i)
    obj -= logsig(vals(i) - (*b_)(i));
  
  obj /= (double)A_->cols();
  return obj;
}