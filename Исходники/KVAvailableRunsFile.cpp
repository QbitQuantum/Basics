Bool_t KVAvailableRunsFile::ExtractDateFromFileName(const Char_t* name, KVDatime& date)
{
	// We assume that 'name' is the name of a run of the type of this available runs file.
	// We attempt several methods to try to extract a date from 'name'.
	// If successful, we return kTRUE and 'date' contains the result.
	
   //get format string for current dataset
   TString fmt =
       fDataSet->
       GetDataSetEnv(Form("DataSet.RunFileName.%s", GetDataType()));
	Int_t rubbish = fmt.Index("%*");
	if(rubbish>-1) fmt.Remove(rubbish,fmt.Length());
	Int_t run = IsRunFileName(name);
	if(!run) return kFALSE;
	TString basename;
	basename.Form(fmt.Data(), run);
	TString fullname(name);
	if(!fullname.Contains(basename)) return kFALSE;
	if(fullname.Length()==basename.Length()) return kFALSE;
	fullname.Remove(0, basename.Length()+1);
	fullname.ReplaceAll("_"," ");
	fullname.ToUpper();
	if(KVDatime::IsSQLFormat(fullname.Data())){
		date.SetSQLDate(fullname.Data());
		return kTRUE;
	}
	else 
	{
		fullname.ReplaceAll("."," ");
		if(KVDatime::IsGANACQFormat(fullname.Data())){
			date.SetGanacqDate(fullname.Data());
			return kTRUE;
		}
		else if(KVDatime::IsGANACQ2010Format(fullname.Data())){
			date.SetGanacq2010Date(fullname.Data());
			return kTRUE;
		}
	}
	return kFALSE;
}