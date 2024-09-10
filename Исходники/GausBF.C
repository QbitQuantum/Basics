void GausBF::Print(Option_t *option) const
{
  TString sopt = option; sopt.ToLower();
  if (sopt == "dump") {
    for (Int_t i = 0; i < Ns1*Ns9*Np; i++) {
      cout << Form(" %10.3e,", _par[i]);
      if (i%6 == 5) cout << endl;
    }
    cout << endl;
  }
  if (sopt.BeginsWith("p")) {
    TString ss = sopt(1, 2);
    if (ss.IsDigit()) {
      Int_t ip = ss.Atoi();
      if (0 <= ip && ip < Np)
	for (Int_t i = 0; i < Ns1; i++) {
	  for (Int_t j = 0; j < Ns9; j++) {
	    AMSPoint p1 = GetP1(i);
	    AMSPoint p9 = GetP9(j);
	    cout << Form("%3d %3d %6.2f %6.2f %7.2f %7.2f %10.3e",
			 i, j, p1.x(), p1.y(),
			       p9.x(), p9.y(), _par[(i*Ns9+j)*Np+ip]) << endl;
	  }
	}
    }
  }
}