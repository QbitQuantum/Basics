void UnitTestAliTPCcalibAlignStreamer(const char *fname="/hera/alice/local/benchmark/vAN-20140518/000128503/cpass1/CalibObjects.root"){
  //
  // test streamer of the AliTPCcalibAlign::Streamer
  //   0.) Read old data part
  //   1.) Fill part 
  //   2.) Write part
  //   3.) Read back - consistency check
  //   4.) Destructor check
  //   5.) Memory usage print
  //
  AliLog::SetClassDebugLevel("AliTPCcalibAlign",1);
  AliTPCcalibAlign * align=0;
  Int_t nPoints=1000000;
  //
  //  0.) Read old data part
  //
  TFile *fin= TFile::Open(fname);
  if (fin){
    AliSysInfo::AddStamp("LoadFile");
    align = (AliTPCcalibAlign * )fin->Get("TPCAlign/alignTPC");
    AliSysInfo::AddStamp("LoadAlign");
    fin->Close();
    delete fin;
    if (align->GetClusterDelta(0)==NULL){
      ::Error("UnitTestAliTPCcalibAlignStreamer","Not back compatible class- GetClusterDelta");
      align->MakeResidualHistos();    
    }
    if (align->GetTrackletDelta(0)==NULL){
      ::Error("UnitTestAliTPCcalibAlignStreamer","Not back compatible class- GetTrackletDelta");
      align->MakeResidualHistosTracklet();
    }
  }else{
  }


  //
  // 1.) Fill part test
  //
  for (Int_t ipoint=0; ipoint<nPoints; ipoint++){
    Double_t xxx[10]={0};
    for (Int_t ihis=0; ihis<2; ihis++){
      THn* his = align->GetClusterDelta(ihis);
      for (Int_t iaxis=0; iaxis<his->GetNdimensions(); iaxis++) {
	xxx[iaxis]=his->GetAxis(iaxis)->GetXmin()+gRandom->Rndm()*(his->GetAxis(iaxis)->GetXmax()-his->GetAxis(iaxis)->GetXmin());
      }
      his->Fill(xxx);
    }
    for (Int_t ihis=0; ihis<4; ihis++){
      THnSparse* his = align->GetTrackletDelta(ihis);
      for (Int_t iaxis=0; iaxis<his->GetNdimensions(); iaxis++) {
	xxx[iaxis]=his->GetAxis(iaxis)->GetXmin()+gRandom->Rndm()*(his->GetAxis(iaxis)->GetXmax()-his->GetAxis(iaxis)->GetXmin());
      }
      his->Fill(xxx);
    }
  } 
  AliSysInfo::AddStamp("FillTrees");
  //
  // 2.) Write part
  //
  TFile * fout=new TFile("testAliTPCcalibAlignStreamer.root","recreate");
  AliSysInfo::AddStamp("WriteAlignStart");
  align->Write("alignTPC"); 
  AliSysInfo::AddStamp("WriteAlignEnd");
  fout->ls();
  fout->Close();
  delete fout;
  //
  // 3.) Read back - consistency check
  //
  fin=new TFile("testAliTPCcalibAlignStreamer.root");
  AliTPCcalibAlign * align2 = (AliTPCcalibAlign *)fin->Get("alignTPC");  
  AliSysInfo::AddStamp("ReadAlign2");
  if (align2==NULL){
    ::Fatal("UnitTestAliTPCcalibAlignStreamer","Alignemnt not read");
  }else{
    ::Info("UnitTestAliTPCcalibAlignStreamer","Alignemnt read-OK");
  }
  if (align2->GetClusterDelta(0)==NULL){
    ::Fatal("UnitTestAliTPCcalibAlignStreamer","histogram GetClusterDelta(0) not read");
  }else{
    ::Info("UnitTestAliTPCcalibAlignStreamer","histogram read GetClusterDelta(0) -OK");
  }
  if (align2->GetTrackletDelta(0)==NULL){
    ::Fatal("UnitTestAliTPCcalibAlignStreamer","histogram GetTrackletDelta(0)not read");
  }else{
    ::Info("UnitTestAliTPCcalibAlignStreamer","histogram read GetTrackletDelta(0) -OK");
  }

  if (align2->GetClusterDelta(0)->GetEntries()!=align->GetClusterDelta(0)->GetEntries()){
    ::Fatal("UnitTestAliTPCcalibAlignStreamer","histogram with different entries");
  }else{
    ::Info("UnitTestAliTPCcalibAlignStreamer","histogram cont. GettrackletDelta(0) -OK");
  }
  if (align2->GetTrackletDelta(0)->GetEntries()!=align->GetTrackletDelta(0)->GetEntries()){
    ::Fatal("UnitTestAliTPCcalibAlignStreamer","histogram with different entries");
  }
  //
  // 4.) Destructor check
  //
  delete align2;
  AliSysInfo::AddStamp("deleteAlign2");
  delete align;
  AliSysInfo::AddStamp("deleteAlign");
  //
  // 5.) Memory usage print
  //
  TTree * treeSys =AliSysInfo::MakeTree("syswatch.log");
  treeSys->Scan("sname:deltaVM:VM:pI.fMemResident","","colsize=30:15:15:20");

}