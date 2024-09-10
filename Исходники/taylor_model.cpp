TaylorModel& TaylorModel::operator *= (const TaylorModel& other)
{
  assert(other.time_interval_ == time_interval_);
  register FCL_REAL c0, c1, c2, c3;
  register FCL_REAL c0b = other.coeffs_[0], c1b = other.coeffs_[1], c2b = other.coeffs_[2], c3b = other.coeffs_[3];

  const Interval& rb = other.r_;

  c0 = coeffs_[0] * c0b;
  c1 = coeffs_[0] * c1b + coeffs_[1] * c0b;
  c2 = coeffs_[0] * c2b + coeffs_[1] * c1b + coeffs_[2] * c0b;
  c3 = coeffs_[0] * c3b + coeffs_[1] * c2b + coeffs_[2] * c1b + coeffs_[3] * c0b;

  Interval remainder(r_ * rb);
  register FCL_REAL tempVal = coeffs_[1] * c3b + coeffs_[2] * c2b + coeffs_[3] * c1b;
  remainder += time_interval_->t4_ * tempVal;

  tempVal = coeffs_[2] * c3b + coeffs_[3] * c2b;
  remainder += time_interval_->t5_ * tempVal;

  tempVal = coeffs_[3] * c3b;
  remainder += time_interval_->t6_ * tempVal;

  remainder += ((Interval(coeffs_[0]) + time_interval_->t_ * coeffs_[1] + time_interval_->t2_ * coeffs_[2] + time_interval_->t3_ * coeffs_[3]) * rb +
                (Interval(c0b) + time_interval_->t_ * c1b + time_interval_->t2_ * c2b + time_interval_->t3_ * c3b) * r_);

  coeffs_[0] = c0;
  coeffs_[1] = c1;
  coeffs_[2] = c2;
  coeffs_[3] = c3;

  r_ = remainder;

  return *this;
}