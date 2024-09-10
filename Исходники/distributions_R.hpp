Type dbinom(Type k, Type size, Type prob, int give_log=0)
{
  Type logres = lgamma(size + 1) - lgamma(k + 1) - lgamma(size - k + 1);
  // Add 'k * log(prob)' only if k > 0
  logres += CppAD::CondExpGt(k, Type(0), k * log(prob), Type(0) );
  // Add '(size - k) * log(1 - prob)' only if size > k
  logres += CppAD::CondExpGt(size, k, (size - k) * log(1 - prob), Type(0) );
  if (!give_log) return exp(logres);
  else return logres;
}