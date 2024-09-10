void PrimeSieve::doSmallPrime(const SmallPrime& sp)
{
  if (sp.firstPrime >= start_ && sp.lastPrime <= stop_)
  {
    // callback prime numbers
    if (sp.index == 0)
    {
      if (isFlag(CALLBACK_PRIMES_OBJ))
        cb_->callback(sp.firstPrime);
      if (isFlag(CALLBACK_PRIMES_OBJ_TN))
        cb_tn_->callback(sp.firstPrime, threadNum_);
      if (isFlag(CALLBACK_PRIMES))
        callback_(sp.firstPrime);
      if (isFlag(CALLBACK_PRIMES_TN))
        callback_tn_(sp.firstPrime, threadNum_);
      if (isFlag(CALLBACK_PRIMES_C))
        reinterpret_cast<callback_c_t>(callback_)(sp.firstPrime);
      if (isFlag(CALLBACK_PRIMES_C_TN))
        reinterpret_cast<callback_c_tn_t>(callback_tn_)(sp.firstPrime, threadNum_);
    }
    if (isCount(sp.index))
      counts_[sp.index]++;
    if (isPrint(sp.index))
      std::cout << sp.str << '\n';
  }
}