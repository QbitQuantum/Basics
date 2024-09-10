double Hypermet::eval_step_tail(double x) {
  if (width_.val == 0)
    return 0;

  double xc = x - center_.val;

  double step = step_amplitude.val * erfc( xc/width_.val );

  double tail = 0;
  double lexp = exp(pow(0.5*width_.val/tail_slope.val, 2) + xc/tail_slope.val);
  if ((tail_slope.val != 0) && !isinf(lexp))
    tail = tail_amplitude.val * lexp * erfc( 0.5*width_.val/tail_slope.val + xc/width_.val);

  return height_.val * 0.5 * (step + tail);
}