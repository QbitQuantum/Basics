//_____________________________________________________________________________
void ProofSimpleFile::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   // Number of histograms (needed in terminate)
   Ssiz_t iopt = kNPOS;
   if (fInput->FindObject("ProofSimpleFile_NHist")) {
      TParameter<Long_t> *p =
         dynamic_cast<TParameter<Long_t>*>(fInput->FindObject("ProofSimpleFile_NHist"));
      fNhist = (p) ? (Int_t) p->GetVal() : fNhist;
   } else if ((iopt = option.Index("nhist=")) != kNPOS) {
      TString s;
      Ssiz_t from = iopt + strlen("nhist=");
      if (option.Tokenize(s, from, ";") && s.IsDigit()) fNhist = s.Atoi();
   }

   // The file for merging
   fProofFile = new TProofOutputFile("SimpleFile.root", "M");
   TNamed *out = (TNamed *) fInput->FindObject("PROOF_OUTPUTFILE");
   if (out) fProofFile->SetOutputFileName(out->GetTitle());
   TDirectory *savedir = gDirectory;
   fFile = fProofFile->OpenFile("RECREATE");
   if (fFile && fFile->IsZombie()) SafeDelete(fFile);
   savedir->cd();

   // Cannot continue
   if (!fFile) {
      TString amsg = TString::Format("ProofSimpleFile::SlaveBegin: could not create '%s':"
                                     " instance is invalid!", fProofFile->GetName());
      Abort(amsg, kAbortProcess);
      return;
   }

   // Histos arrays
   if (CreateHistoArrays() != 0) {
      Abort("ProofSimpleFile::SlaveBegin: could not create histograms", kAbortProcess);
      return;
   }

   // Create directory
   if (!(fFileDir = fFile->mkdir("blue"))) {
      Abort("ProofSimpleFile::SlaveBegin: could not create directory 'blue' in file!",
            kAbortProcess);
      return;
   }

   // Create the histograms
   for (Int_t i=0; i < fNhist; i++) {
      fHistTop[i] = new TH1F(Form("ht%d",i), Form("ht%d",i), 100, -3., 3.);
      fHistTop[i]->SetFillColor(kRed);
      fHistTop[i]->SetDirectory(fFile);
      fHistDir[i] = new TH1F(Form("hd%d",i), Form("hd%d",i), 100, -3., 3.);
      fHistDir[i]->SetFillColor(kBlue);
      fHistDir[i]->SetDirectory(fFileDir);
   }

   // Set random seed
   fRandom = new TRandom3(0);
}