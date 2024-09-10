// Computes the parameter <m> of the algorithm, given the parameter
// <k> and the desired success probability <successProbability>. Only
// meaningful when functions <g> are interdependent (pairs of
// functions <u>, where the <m> functions <u> are each k/2-tuples of
// independent LSH functions).    //g函数是相关时，有用！ 为了减少计算时间
IntT computeMForULSH(IntT k, RealT successProbability){
  ASSERT((k & 1) == 0); // k should be even in order to use ULSH.
  RealT mu = 1 - POW(computeFunctionP(PARAMETER_W_DEFAULT, 1), k / 2);    //1-p1^(k/2)   ，为1 说明c=1
  RealT P = successProbability;
  RealT d = (1-mu)/(1-P)*1/LOG(1/mu) * POW(mu, -1/(1-mu));     //(p1^k/2)/delta*log(1/(p1^k/2))*((1-p1^k/2)^(-1/(p1^(k/2)))) 
  RealT y = LOG(d);
  IntT m = CEIL(1 - y/LOG(mu) - 1/(1-mu));
  while (POW(mu, m-1) * (1 + m * (1-mu)) > 1 - P){      //13
    m++;
  }
  return m;
}