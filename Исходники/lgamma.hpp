inline Type dnbinom(const Type &x, const Type &size, const Type &prob,
		    int give_log=0)
{
  Type n=size;
  Type p=prob;
  Type logres = lgamma(x+n)-lgamma(n)-lgamma(x+Type(1))+
    n*log(p)+x*log(Type(1)-p);
  if (give_log) return logres; else return exp(logres);
}