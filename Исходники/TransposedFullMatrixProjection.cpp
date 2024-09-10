void TransposedFullMatrixProjection::forward() {
  REGISTER_TIMER_INFO("FwMulTimer", getName().c_str());
  out_->value->mul(in_->value, weight_->getW()->getTranspose(), 1, 1);
}