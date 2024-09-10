void efficiencies( TString fin = "TMVA.root", Int_t type = 2, Bool_t useTMVAStyle = kTRUE )
{
   // argument: type = 1 --> plot efficiency(B) versus eff(S)
   //           type = 2 --> plot rejection (B) versus efficiency (S)
  
   // set style and remove existing canvas'
   TMVAGlob::Initialize( useTMVAStyle );

   // checks if file with name "fin" is already open, and if not opens one
   TFile* file = TMVAGlob::OpenFile( fin );  

   // check if multi-cut MVA or only one set of MVAs
   Bool_t multiMVA=kFALSE;
   TIter nextDir(file->GetListOfKeys());
   TKey *key;
   // loop over all directories and check if
   // one contains the key word 'multicutMVA'
   while ((key = (TKey*)nextDir())) {
      TClass *cl = gROOT->GetClass(key->GetClassName());
      if (!cl->InheritsFrom("TDirectory")) continue;    
      TDirectory *d = (TDirectory*)key->ReadObj();    
      TString path(d->GetPath());
      if (path.Contains("multicutMVA")){         
         multiMVA=kTRUE;
         plot_efficiencies( file, type, d );
      }
   }
   plot_efficiencies( file, type, gDirectory );

   return;
}