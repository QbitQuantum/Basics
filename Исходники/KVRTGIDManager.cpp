Int_t KVRTGIDManager::WriteAsciiFile ( const Char_t * filename, const TCollection *selection, Bool_t update )
{
   	// Write identification functions  in file 'filename'.
   	// If selection=0 (default), write all grids.
   	// If update=true, call UpdateListFromIDGridManager() before writing
   	// If selection!=0, write only grids in list.
   	// Returns number of functions written in file.

	if( update ) UpdateListFromIDGridManager();
	if( !fIDGlobalList ){
		Warning("KVRTGIDManager::WriteAsciiFile","No listed identification functions to write");
 	   	return 0;
	}

   	ofstream tgidfile ( filename );
   	if( !tgidfile.is_open() ){
	   	Error("KVRTGIDManager::WriteAsciiFile","No write permission for file %s", filename);
	   	return 0;
   	} 

   	const TCollection *list_tgid = ( selection ? selection : fIDGlobalList );
   	TIter next ( list_tgid );
   	KVTGID *tgid    = NULL;
   	Int_t   n_saved = 0;

   	while ( ( tgid = (KVTGID *)next() ) ) {

		// Not write a KVTGID copy
		TString tmp = tgid->GetTitle();
		if(tmp.Contains("COPY")){
			tmp.Remove(0, tmp.Index("0x"));	
			KVTGID *tmp_tgid = reinterpret_cast<KVTGID *>((Int_t)tmp.Atof());
			Warning("KVRTGIDManager::WriteAsciiFile","The function %s (%s, %p) is not written because it is a copy of %s (%s, %p)"
					, tgid->GetName(), tgid->ClassName(), tgid
					, tmp_tgid->GetName(), tmp_tgid->ClassName(), tmp_tgid);
			continue;
		}
      	tgid->WriteToAsciiFile ( tgidfile );
      	Info( "KVRTGIDManager::WriteAsciiFile", "%s (%s, %p) saved", tgid->GetName(), tgid->ClassName(), tgid );
      	n_saved++;
   	}

   	tgidfile.close();
        return n_saved;
}