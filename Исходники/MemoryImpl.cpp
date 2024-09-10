void MemoryImpl::LoadSymbolTable( wxFileDirPickerEvent& event )
{
	// Open the file parse as :
	// "Label",": equ ","value"
	// And create an hashmap from that

	// Also fill in the label selector
	wxTextFile f(event.GetPath());
	f.Open();

	ChoiceLabels->Clear();

	for (unsigned int i = 0; i < f.GetLineCount(); i++)
	{
		// Parse each line and insert it in the hashmap
		wxString label = f[i].BeforeFirst(':');

		unsigned long adr;
		f[i].AfterLast(' ').ToULong(&adr, 0);

		if (adr) // filter out all these stupid labels that point to 0
		{
			lhm[label]=adr;
			ChoiceLabels->Append(label);
		}
	}
}