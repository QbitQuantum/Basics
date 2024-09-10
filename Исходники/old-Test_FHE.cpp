void checkCiphertext(const Ctxt& ctxt, const ZZX& ptxt, const FHESecKey& sk)
{
  const FHEcontext& context = ctxt.getContext();
  /*
  IndexSet base = baseSetOf(ctxt);
  double addedNoise = log(ctxt.modSwitchAddedNoiseVar());
  Ctxt tmp = ctxt;
  tmp.modDownToSet(base);
  double totalNoise = log(tmp.getNoiseVar());
  cout << "   @@@ log(added-noise)="<<addedNoise
       << ", log(total-noise)="<<totalNoise<<endl;
  */
  cout << " ln(q)="<< context.logOfProduct(ctxt.getPrimeSet())
       << ", ln(nVar)/2="<< log(ctxt.getNoiseVar())/2;
  //       << ", ln(nMag)="<< log(ctxt.getNoiseMag());

  ZZX res;
  //  sk.Decrypt(res, ctxt);
  ZZX f;
  sk.Decrypt(res, ctxt, f);
  cout << ", ln(mxPtxtCoef)=" << log(largestCoeff(f));

  // ensure we reduce the same way on both
  PolyRed((ZZX&)res,res,ctxt.getPtxtSpace(),true);
  PolyRed((ZZX&)ptxt,ptxt,ctxt.getPtxtSpace(),true);
  if (res != ptxt) {
    cout << ", failed\n";
    for (long i=0; i<=deg(ptxt); i++) if (coeff(res,i)!=coeff(ptxt,i)) {
	cout << "first mismatch in coeff "<<i<<": "
	     << coeff(res,i)<<"!="<<coeff(ptxt,i)<<"\n";
	break;
      }

    cout << "Timing information:\n";
    printAllTimers();
    cout << "\n";
    exit(0);
  }
  else cout << ", succeeded\n";
}