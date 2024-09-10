void readContextBinary(istream& str, FHEcontext& context)
{
  assert(readEyeCatcher(str, BINIO_EYE_CONTEXT_BEGIN)==0);

  // Get the standard deviation
  context.stdev = read_raw_xdouble(str);

  long sizeOfS = read_raw_int(str);

  IndexSet s;
  for(long tmp, i=0; i<sizeOfS; i++){
    tmp = read_raw_int(str);
    s.insert(tmp);
  }

  context.moduli.clear();
  context.specialPrimes.clear();
  context.ctxtPrimes.clear();

  long nPrimes = read_raw_int(str);

  for (long p,i=0; i<nPrimes; i++) {
    p = read_raw_int(str);

    context.moduli.push_back(Cmodulus(context.zMStar,p,0));

    if (s.contains(i))
      context.specialPrimes.insert(i); // special prime
    else
      context.ctxtPrimes.insert(i);    // ciphertext prime
  }
  
  long nDigits = read_raw_int(str);

  context.digits.resize(nDigits);
  for(long i=0; i<(long)context.digits.size(); i++){
    sizeOfS = read_raw_int(str);

    for(long tmp, n=0; n<sizeOfS; n++){
      tmp = read_raw_int(str);
      context.digits[i].insert(tmp);
    }
  }

  // Read in the partition of m into co-prime factors (if bootstrappable)
  Vec<long> mv;
  read_ntl_vec_long(str, mv);

  long t = read_raw_int(str);
  bool consFlag = read_raw_int(str);  

  if (mv.length()>0) {
    context.makeBootstrappable(mv, t, consFlag);
  }

  assert(readEyeCatcher(str, BINIO_EYE_CONTEXT_END)==0);
}