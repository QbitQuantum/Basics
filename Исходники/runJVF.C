void runJVF(){

  cout<<"RUN rmJVFPlots.sh FIRST!"<<endl;

  cout<<endl;
  cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
  cout<<"In runJVF.C"<<endl;
  cout<<"Running over "<<nSkims<<" skims"<<endl;
  cout<<endl;

  TChain *jvfSkimChain;
  TChain *nojvfSkimChain;
  string file_jvf;
  string file_nojvf;
  for(int s=0;s<nSkims;s++){

    jvfSkimChain=new TChain("analysisTree");

    nojvfSkimChain=new TChain("analysisTree");
    
    string cur_jvf_skim = "../files/skims_jvf/"+skim_list[s];
    cur_jvf_skim+=".skim.root";
    cout<<"jvfSkimChain->Add("<<cur_jvf_skim.c_str()<<")"<<endl;;
    jvfSkimChain->Add(cur_jvf_skim.c_str());
    
    //tmp
    string cur_nojvf_skim = "../files/skims_nojvf/"+skim_list[s];
    //string cur_nojvf_skim = "../files/skims_jvf/"+skim_list[s];
    cur_nojvf_skim+=".skim.root";
    cout<<"nojvfSkimChain->Add("<<cur_nojvf_skim.c_str()<<")"<<endl;;
    nojvfSkimChain->Add(cur_nojvf_skim.c_str());

    //with jvf cut
    file_jvf=skim_list[s]+",jvf";
    jvfSkimChain->Process("../src/jvf.C+",file_jvf.c_str());

    //without jvf cut
    file_nojvf=skim_list[s]+",nojvf";
    nojvfSkimChain->Process("../src/jvf.C+",file_nojvf.c_str());
    
	
    
  }
  
  delete jvfSkimChain;
  delete nojvfSkimChain;
  cout<<"Histogram files written to ../plots"<<endl;
  cout<<"Don't forget to merge histograms!"<<endl;
  cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
  gROOT->ProcessLine(".q");
  return;
}