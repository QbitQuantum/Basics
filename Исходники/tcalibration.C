void tcalibration(TString inFile= "../../data/cj.hld.root", TString outFile= "outFileC.root", TString cFile= "calib.root", TString tFile= "calibOffsets.root", Int_t trigger=2560,  Int_t sEvent =0, Int_t eEvent=0, Int_t build = 0){ //1920
  if(build==1) return;
  ginFile = inFile;
  goutFile = outFile;
  gcFile = cFile; // fine time calibration
  gtFile = tFile; // pilas offsets + walk corrections
  gTrigger = trigger;
  if(gtFile=="") gMode = 0;
  else  gMode = 1;

  TChain* ch = new TChain("T");
  ch->Add(ginFile);
  
  Int_t entries = ch->GetEntries();
  TTSelector *selector = new TTSelector();
  TString option = Form("%d %d",gTrigger,gMode);
  
  if(eEvent==0){
    std::cout<<"Entries in chain:  "<< entries<<std::endl;
    ch->Process(selector,option,entries);
  }else{
    ch->Process(selector,option,eEvent-sEvent,sEvent); 
  }
}