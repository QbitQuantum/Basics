void bcut::parseWeight(TString wgt){
  cutTypes_.push_back(kFloat);
  fWeights_.push_back(NULL);
  fvWeights_.push_back(NULL);
  indWeights_.push_back(-1);
  constWeights_.push_back(1.);

  if(wgt=="weight")		fWeights_.back() = &baby_base::weight;
  else if(wgt=="w_lumi")	fWeights_.back() = &baby_base::w_lumi;
  else if(wgt=="w_pu")	fWeights_.back() = &baby_base::w_pu;
  else if(wgt=="w_lep")	fWeights_.back() = &baby_base::w_lep;
  else if(wgt=="w_fs_lep")	fWeights_.back() = &baby_base::w_fs_lep;
  else if(wgt=="w_toppt")	fWeights_.back() = &baby_base::w_toppt;
  else if(wgt=="w_btag")	fWeights_.back() = &baby_base::w_btag;
  else if(wgt=="eff_trig")	fWeights_.back() = &baby_base::eff_trig;
  else if(wgt.Contains("[")){ // if weight is a vector element
    TString index_s(wgt);
    wgt.Remove(wgt.Index("["), wgt.Length());
    index_s.Remove(0, index_s.Index("[")+1);
    index_s.Remove(index_s.Index("]"), index_s.Length());
    indWeights_.back() = index_s.Atoi();
    cutTypes_.back() = kvFloat;
    if(wgt=="w_pdf")        fvWeights_.back() = &baby_base::w_pdf;
    else if(wgt=="sys_pdf") fvWeights_.back() = &baby_base::sys_pdf;
    else if(wgt=="sys_isr") fvWeights_.back() = &baby_base::sys_isr;
    else if(wgt=="sys_mur") fvWeights_.back() = &baby_base::sys_mur;
    else if(wgt=="sys_muf") fvWeights_.back() = &baby_base::sys_muf;
    else if(wgt=="sys_murf") fvWeights_.back() = &baby_base::sys_murf;
    else if(wgt=="sys_trig") fvWeights_.back() = &baby_base::sys_trig;
    else if(wgt=="sys_lep") fvWeights_.back() = &baby_base::sys_lep;
    else if(wgt=="sys_fs_lep") fvWeights_.back() = &baby_base::sys_fs_lep;
    else if(wgt=="sys_bctag") fvWeights_.back() = &baby_base::sys_bctag;
    else if(wgt=="sys_fs_bctag") fvWeights_.back() = &baby_base::sys_fs_bctag;
    else if(wgt=="sys_udsgtag") fvWeights_.back() = &baby_base::sys_udsgtag;
    else if(wgt=="sys_fs_udsgtag") fvWeights_.back() = &baby_base::sys_fs_udsgtag;
    else {
      cout<<"Weight \""<<wgt<<" not defined. Add it to bcut::parseWeight in bcut.cpp"<<endl;
      exit(0);
    }
  }else if(wgt.Atof()>0) {
    constWeights_.back() = wgt.Atof();
    cutTypes_.back() = kConst;
  } else {
    cout<<"Weight \""<<wgt<<" not defined. Add it to bcut::parseWeight  in bcut.cpp"<<endl;
    exit(0);
  }   
}