void AbstractView::setPose(const TooN::SE3<>& T_wc )
{
  T_cw_ = T_wc.inverse();
}