  TCollection* GetEtaBin(TObject* o, Double_t& etaMin, Double_t& etaMax)
  {
    const char* re = "[pm][0-9]*d[0-9]*_[pm][0-9]*d[0-9]*";
    TRegexp     check(re);

    if (!o->IsA()->InheritsFrom(TCollection::Class())) {
      // Warning("GetEtaBin", "Don't know how to deal with %s - a %s",
      //         o->GetName(), o->ClassName());
      return 0;
    }
    TString oN(o->GetName());
    if (oN.Index(check) == kNPOS) { 
      // Warning("GetEtaBin", "Collection %s does not match %s",
      //         oN.Data(), re);
      return 0;
    }
    Int_t    ul     = oN.Index("_");
    TString  sMin   = oN(0, ul);
    TString  sMax   = oN(ul+1, oN.Length()-ul-1);
    sMin.ReplaceAll("p", "+");
    sMin.ReplaceAll("m", "-");
    sMin.ReplaceAll("d", ".");
    sMax.ReplaceAll("p", "+");
    sMax.ReplaceAll("m", "-");
    sMax.ReplaceAll("d", ".");
    etaMin = sMin.Atof();
    etaMax = sMax.Atof();

    return static_cast<TCollection*>(o);
  }