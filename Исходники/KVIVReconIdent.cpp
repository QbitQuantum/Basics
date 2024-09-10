void KVIVReconIdent::InitAnalysis(void)
{

   TString dt;
   dt = gDataSet->GetDataSetEnv("KVIVReconIdent.DataToAnalyse", "INDRA VAMOS");
   dt.ToLower();
   Info("InitAnalysis", "Analysing data of %s", dt.Data());
   if (dt.Contains("indra")) SetBit(kINDRAdata);
   if (dt.Contains("vamos")) SetBit(kVAMOSdata);

   if (TestBit(kINDRAdata)) cout << "INDRA" << endl;
   if (TestBit(kVAMOSdata)) cout << "VAMOS" << endl;
}