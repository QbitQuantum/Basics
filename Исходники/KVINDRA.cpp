void KVINDRA::LinkToCodeurs()
{

   // Link detectors with electronic modules
   // for the moment only QDC for Si and ChIo are implemented
   // This information is accessible via KVINDRADetector::GetNumeroCodeur()
   // To be active one has to put in the dataset directory
   // a file name Codeurs.dat containing the name of the file for the concerned type
   // of electronic module
   // for example see INDRA_e613 dataset
   // [dataset name].INDRADB.Codeurs:    ...


   KVFileReader flist;
   TString fp;
   if (!KVBase::SearchKVFile(gDataSet->GetDataSetEnv("INDRADB.Codeurs", ""), fp, gDataSet->GetName())) {
      Warning("LinkToCodeurs", "Fichier %s, inconnu au bataillon", gDataSet->GetDataSetEnv("INDRADB.Codeurs", ""));
      return;
   }

   if (!flist.OpenFileToRead(fp.Data())) {
      //Error("ReadGainList","Error opening file named %s",fp.Data());
      return;
   }
   Info("LinkToCodeurs()", "Reading correspondance Codeur-Detecteur ...");

   TEnv* env = 0;
   KVINDRADetector* idet = 0;
   while (flist.IsOK()) {
      flist.ReadLine(NULL);
      KVString file = flist.GetCurrentLine();
      if (file != "") {
         if (KVBase::SearchKVFile(file.Data(), fp, gDataSet->GetName())) {
            env = new TEnv();
            env->ReadFile(fp.Data(), kEnvAll);
            TEnvRec* rec = 0;
            TObjArray* toks = 0;
            TIter it(env->GetTable());
            while ((rec = (TEnvRec*)it.Next())) {
               if (!strcmp(rec->GetName(), "type")) {
                  Info("LinkToCodeurs", "Module type %s", rec->GetValue());
               }
               else {
                  toks = TString(rec->GetValue()).Tokenize(",");
                  for (Int_t ii = 0; ii < toks->GetEntries(); ii += 1) {
                     idet = (KVINDRADetector*)gIndra->GetDetector(((TObjString*)toks->At(ii))->GetString().Data());
                     if (idet)
                        idet->SetNumeroCodeur(TString(rec->GetName()).Atoi());
                  }
                  delete toks;
               }
            }
            delete env;
         }
      }
   }

   flist.CloseFile();


}