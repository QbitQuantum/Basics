//______________________________________________________________________________
HtmlObjTable *HtmlSummary::AddTable(const char *name, Int_t nfields, 
	Bool_t exp, Option_t *option)
{
	// Add a new table in our list of tables.
	
	TString opt = option;
	opt.ToLower();
	HtmlObjTable *table = new HtmlObjTable(name, nfields, exp);
	fNTables++;
	if (opt.Contains("first"))
		fObjTables->AddFirst(table);
	else
		fObjTables->Add(table);
	return table;
}