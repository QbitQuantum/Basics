void KVINDRAUpDater::SetChVoltParameters(KVDBRun* kvrun)
{


   KVRList* param_list = kvrun->GetLinks("Channel-Volt");
   if (!param_list)
      return;
   if (!param_list->GetSize())
      return;

   KVDetector* kvd;
   KVDBParameterSet* kvps;
   KVCalibrator* kvc;
   TIter next_ps(param_list);


   TString str;

   // Setting Channel-Volts calibration parameters
   while ((kvps = (KVDBParameterSet*) next_ps())) {     // boucle sur les parametres
      str = kvps->GetName();
      str.Remove(str.Sizeof() - 4, 3);  //Removing 3 last letters (ex : "_PG")
      kvd = fArray->GetDetector(str.Data());
      if (!kvd)
         Warning("SetChVoltParameters(UInt_t)", "Dectector %s not found !",
                 str.Data());
      else {                    // detector found
         kvc = kvd->GetCalibrator(kvps->GetName(), kvps->GetTitle());
         if (!kvc)
            Warning("SetChVoltParameters(UInt_t)",
                    "Calibrator %s %s not found !", kvps->GetName(),
                    kvps->GetTitle());
         else {                 //calibrator found
            for (Int_t i = 0; i < kvc->GetNumberParams(); i++) {
               kvc->SetParameter(i, kvps->GetParameter(i));
            }
            kvc->SetStatus(kTRUE);   // calibrator ready
         }                      //calibrator found
      }                         //detector found
   }                            //boucle sur les parameters
}