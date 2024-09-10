float
log_combination_k_r_f (unsigned int k, float r)
{
  if (!k) return 0;
  float val = lgammaf (k + r) - lgammaf (r) - log_factorial_f (k);
  return val;
}