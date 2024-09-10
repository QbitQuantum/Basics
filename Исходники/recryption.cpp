// bootstrap a ciphertext to reduce noise
void FHEPubKey::reCrypt(Ctxt &ctxt)
{
  FHE_TIMER_START;

  // Some sanity checks for dummy ciphertext
  long ptxtSpace = ctxt.getPtxtSpace();
  if (ctxt.isEmpty()) return;
  if (ctxt.parts.size()==1 && ctxt.parts[0].skHandle.isOne()) {
    // Dummy encryption, just ensure that it is reduced mod p
    ZZX poly = to_ZZX(ctxt.parts[0]);
    for (long i=0; i<poly.rep.length(); i++)
      poly[i] = to_ZZ( rem(poly[i],ptxtSpace) );
    poly.normalize();
    ctxt.DummyEncrypt(poly);
    return;
  }

  assert(recryptKeyID>=0); // check that we have bootstrapping data

  long p = getContext().zMStar.getP();
  long r = getContext().alMod.getR();
  long p2r = getContext().alMod.getPPowR();

  // the bootstrapping key is encrypted relative to plaintext space p^{e-e'+r}.
  long e = getContext().rcData.e;
  long ePrime = getContext().rcData.ePrime;
  long p2ePrime = power_long(p,ePrime);
  long q = power_long(p,e)+1;
  assert(e>=r);

#ifdef DEBUG_PRINTOUT
  cerr << "reCrypt: p="<<p<<", r="<<r<<", e="<<e<<" ePrime="<<ePrime
       << ", q="<<q<<endl;
#endif

  // can only bootstrap ciphertext with plaintext-space dividing p^r
  assert(p2r % ptxtSpace == 0);

  FHE_NTIMER_START(preProcess);

  // Make sure that this ciphertxt is in canonical form
  if (!ctxt.inCanonicalForm()) ctxt.reLinearize();

  // Mod-switch down if needed
  IndexSet s = ctxt.getPrimeSet() / getContext().specialPrimes; // set minus
  if (s.card()>2) { // leave only bottom two primes
    long frst = s.first();
    long scnd = s.next(frst);
    IndexSet s2(frst,scnd);
    s.retain(s2); // retain only first two primes
  }
  ctxt.modDownToSet(s);

  // key-switch to the bootstrapping key
  ctxt.reLinearize(recryptKeyID);

  // "raw mod-switch" to the bootstrapping mosulus q=p^e+1.
  vector<ZZX> zzParts; // the mod-switched parts, in ZZX format
  double noise = ctxt.rawModSwitch(zzParts, q);
  noise = sqrt(noise);

  // Add multiples of p2r and q to make the zzParts divisible by p^{e'}
  long maxU=0;
  for (long i=0; i<(long)zzParts.size(); i++) {
    // make divisible by p^{e'}
    long newMax = makeDivisible(zzParts[i].rep, p2ePrime, p2r, q,
				getContext().rcData.alpha);
    zzParts[i].normalize();   // normalize after working directly on the rep
    if (maxU < newMax)  maxU = newMax;
  }

  // Check that the estimated noise is still low
  if (noise + maxU*p2r*(skHwts[recryptKeyID]+1) > q/2) 
    cerr << " * noise/q after makeDivisible = "
	 << ((noise + maxU*p2r*(skHwts[recryptKeyID]+1))/q) << endl;

  for (long i=0; i<(long)zzParts.size(); i++)
    zzParts[i] /= p2ePrime;   // divide by p^{e'}

  // Multiply the post-processed cipehrtext by the encrypted sKey
#ifdef DEBUG_PRINTOUT
  cerr << "+ Before recryption ";
  decryptAndPrint(cerr, recryptEkey, *dbgKey, *dbgEa, printFlag);
#endif

  double p0size = to_double(coeffsL2Norm(zzParts[0]));
  double p1size = to_double(coeffsL2Norm(zzParts[1]));
  ctxt = recryptEkey;
  ctxt.multByConstant(zzParts[1], p1size*p1size);
  ctxt.addConstant(zzParts[0], p0size*p0size);

#ifdef DEBUG_PRINTOUT
  cerr << "+ Before linearTrans1 ";
  decryptAndPrint(cerr, ctxt, *dbgKey, *dbgEa, printFlag);
#endif
  FHE_NTIMER_STOP(preProcess);

  // Move the powerful-basis coefficients to the plaintext slots
  FHE_NTIMER_START(LinearTransform1);
  ctxt.getContext().rcData.firstMap->apply(ctxt);
  FHE_NTIMER_STOP(LinearTransform1);

#ifdef DEBUG_PRINTOUT
  cerr << "+ After linearTrans1 ";
  decryptAndPrint(cerr, ctxt, *dbgKey, *dbgEa, printFlag);
#endif

  // Extract the digits e-e'+r-1,...,e-e' (from fully packed slots)
  extractDigitsPacked(ctxt, e-ePrime, r, ePrime,
		      context.rcData.unpackSlotEncoding);

#ifdef DEBUG_PRINTOUT
  cerr << "+ Before linearTrans2 ";
  decryptAndPrint(cerr, ctxt, *dbgKey, *dbgEa, printFlag);
#endif

  // Move the slots back to powerful-basis coefficients
  FHE_NTIMER_START(LinearTransform2);
  ctxt.getContext().rcData.secondMap->apply(ctxt);
  FHE_NTIMER_STOP(LinearTransform2);
}