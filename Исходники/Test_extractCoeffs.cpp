int main(int argc, char *argv[]) 
{
  ArgMapping amap;

  long m=53;
  amap.arg("m", m, "use specified value as modulus");

  long p=17;
  amap.arg("p", p, "plaintext base");

  long r=1;
  amap.arg("r", r,  "lifting");

  long levels=5;
  amap.arg("L", levels,  "levels");

  long nb_coeffs=5;
  amap.arg("n", nb_coeffs,  "nb coefficients to extract");

  amap.parse(argc, argv);

  cout << "\n\n******** generate parameters"
       << " m=" << m 
       << ", p=" << p
       << ", r=" << r
       << ", n=" << nb_coeffs
       << endl;

  setTimersOn();

  FHEcontext context(m, p, r);
  buildModChain(context, /*L=*/levels);
  // cout << context << endl;
  // context.zMStar.printout();
  // cout << endl;

  cout << "Generating keys and key-switching matrices... " << std::flush;
  FHESecKey secretKey(context);
  secretKey.GenSecKey(/*w=*/64);// A Hamming-weight-w secret key
  addFrbMatrices(secretKey); // compute key-switching matrices that we need
  add1DMatrices(secretKey); // compute key-switching matrices that we need
  const FHEPubKey& publicKey = secretKey;
  cout << "done\n";

  resetAllTimers();

  EncryptedArray ea = *(context.ea);
  ea.buildLinPolyMat(false);

  Ctxt ctxt(publicKey);
  NewPlaintextArray ptxt(ea);
  random(ea, ptxt);
  // ea.encrypt(ctxt, publicKey, ptxt);
  ea.skEncrypt(ctxt, secretKey, ptxt);


  cout << "Extracting " << nb_coeffs << " coefficients...";
  vector<Ctxt> coeffs;
  extractCoeffs(ea, coeffs, ctxt, nb_coeffs);
  cout << "done\n";

  vector<ZZX> ptxtDec;
  ea.decrypt(ctxt, secretKey, ptxtDec);

  for (long i=0; i<(long)coeffs.size(); i++) {
    if (!coeffs[i].isCorrect()) {
      cerr << " potential decryption error for "<<i<<"th coeffs " << endl;
      CheckCtxt(coeffs[i], "");
      exit(0);
    }
    vector<ZZX> pCoeffs;
    ea.decrypt(coeffs[i], secretKey, pCoeffs);

    assert(pCoeffs.size() == ptxtDec.size());

    for (int j = 0; j < pCoeffs.size(); ++j) {
      if (coeff(pCoeffs[j], 0) != coeff(ptxtDec[j], i)) {
        cerr << "error: extracted coefficient " << i << " from " 
          "slot " << j << " is " << coeff(pCoeffs[j], 0) << " instead of " << 
          coeff(ptxtDec[j], i) << endl;
        exit(0);
      }
    }

  }  
  cerr << "Extracted coefficient successfully verified!\n";
}