//_____________________________________________________________________________
void ProofSimple::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
   Ssiz_t iopt = kNPOS;

   // Histos array
   if (fInput->FindObject("ProofSimple_NHist")) {
      TParameter<Long_t> *p =
         dynamic_cast<TParameter<Long_t>*>(fInput->FindObject("ProofSimple_NHist"));
      fNhist = (p) ? (Int_t) p->GetVal() : fNhist;
   } else if ((iopt = option.Index("nhist=")) != kNPOS) {
      TString s;
      Ssiz_t from = iopt + strlen("nhist=");
      if (option.Tokenize(s, from, ";") && s.IsDigit()) fNhist = s.Atoi();
   }
   if (fNhist < 1) {
      Abort("fNhist must be > 0! Hint: proof->SetParameter(\"ProofSimple_NHist\","
            " (Long_t) <nhist>)", kAbortProcess);
      return;
   }

   if (fInput->FindObject("ProofSimple_NHist3")) {
      TParameter<Long_t> *p =
         dynamic_cast<TParameter<Long_t>*>(fInput->FindObject("ProofSimple_NHist3"));
      fNhist3 = (p) ? (Int_t) p->GetVal() : fNhist3;
   } else if ((iopt = option.Index("nhist3=")) != kNPOS) {
      TString s;
      Ssiz_t from = iopt + strlen("nhist3=");
      if (option.Tokenize(s, from, ";") && s.IsDigit()) fNhist3 = s.Atoi();
   }

   // Ntuple
   TNamed *nm = dynamic_cast<TNamed *>(fInput->FindObject("ProofSimple_Ntuple"));
   if (nm) {

      // Title is in the form
      //         merge                  merge via file
      //           |<fout>                      location of the output file if merge
      //           |retrieve                    retrieve to client machine
      //         dataset                create a dataset
      //           |<dsname>                    dataset name (default: dataset_ntuple)
      //         |plot                  for a final plot
      //         <empty> or other       keep in memory

      fHasNtuple = 1;
      
      TString ontp(nm->GetTitle());
      if (ontp.Contains("|plot") || ontp == "plot") {
         fPlotNtuple = kTRUE;
         ontp.ReplaceAll("|plot", "");
         if (ontp == "plot") ontp = "";
      }
      if (ontp.BeginsWith("dataset")) fHasNtuple = 2;
   }
}