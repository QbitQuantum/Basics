void TBDataParser::OnCharacters(const char *characters)
{	
	if(_currentElement != NULL && !strcmp(_currentElement->Data(),"vector")) {
		TString *string = new TString(characters);
		TObjArray *values = string->Tokenize(", ");

		for(Int_t i = 0; i < values->GetEntries(); i++) {
			TObjString *object = (TObjString *) values->At(i);
			TString value = object->GetString().ReplaceAll("\n", "").ReplaceAll("\t", "").ReplaceAll(" ", "").ReplaceAll("\0", "");
			if(value.IsFloat()) {
				_vector->Fill(value.Atof());
			}
		}

		if(_vectorsStack->GetEntries() == 1) {
			_motherVecEntries = _vector->GetEntries();
		} else if(_currentMethod != NULL && !strcmp(_currentMethod->Data(),"all")) {
			for(Int_t i = 1; i < _motherVecEntries; i++) {
				TObjString *object = (TObjString *) values->First();
				TString value = object->GetString().ReplaceAll("\n", "").ReplaceAll("\t", "").ReplaceAll(" ", "").ReplaceAll("\0", "");
				if(value.IsFloat())
					_vector->Fill(value.Atof());
			}
		} 

		values->Delete();

	}

}