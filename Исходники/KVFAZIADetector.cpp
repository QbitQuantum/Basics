//________________________________________________________________
Bool_t KVFAZIADetector::SetProperties()
{
	// detector name are assumed to be defined as
   // SI2-T2-Q2-B001
	//	CSI-T2-Q2-B001
	// SI1-T1-Q1-B001
	//
   
   KVString tmp;
   KVString sname(GetName());
   sname.Begin("-");
   SetLabel(sname.Next());
	gFazia->AddDetectorLabel(GetLabel());
   
	tmp = sname.Next(); tmp.ReplaceAll("T",""); fTelescope = tmp.Atoi();
	tmp = sname.Next(); tmp.ReplaceAll("Q",""); fQuartet = tmp.Atoi();
	tmp = sname.Next(); tmp.ReplaceAll("B",""); fBlock = tmp.Atoi();
	KVSignal* sig=0;
   //"QH1", "I1", "QL1", "Q2", "I2", "Q3
	if (fSignals)
   	delete fSignals;
   fSignals = new KVList(kTRUE);
	KVString lsignals="";
   if ( !strcmp(GetLabel(),"SI1") ) {	lsignals="QH1,I1,QL1";	}
   else if ( !strcmp(GetLabel(),"SI2" ) ) {	lsignals="Q2,I2";	}
	else if ( !strcmp(GetLabel(),"CSI" ) ) {	lsignals="Q3";	}
   else{
   	Warning("SetProperties","Unknown label \"%s\" for this detector : %s\n",GetLabel(),GetName());
		lsignals="";
	}
   
	lsignals.Begin(",");
	while ( !lsignals.End() )
	{
		KVString ssig = lsignals.Next();
		if (ssig.BeginsWith("Q")){
			sig = new KVChargeSignal(ssig.Data());
		}
		else if (ssig.BeginsWith("I")){
			sig = new KVCurrentSignal(ssig.Data());
		}
		else{
			Warning("unknown format signal detectorlabel=%s, signal=%s\n",GetLabel(),ssig.Data());
			sig = new KVSignal(ssig.Data(),"unknown");
		}
		
		sig->LoadPSAParameters(GetLabel());
		sig->SetDetectorName(GetName());
		fSignals->Add(sig);
	}
	
	return kTRUE;
}