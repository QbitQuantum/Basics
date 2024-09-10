dlgSearchObject::dlgSearchObject(frmMain *p, pgDatabase *db)
{
	parent = p;
	header = wxT("");
	currentdb = db;

	wxWindowBase::SetFont(settings->GetSystemFont());
	LoadResource(p, wxT("dlgSearchObject"));

	// Icon
	appearanceFactory->SetIcons(this);
	RestorePosition();

	btnSearch->Disable();

	lcResults->InsertColumn(0, _("Type"));
	lcResults->InsertColumn(1, _("Name"));
	lcResults->InsertColumn(2, _("Path"));

	// Mapping table between local language and english,
	// because in SQL we're using only english and translate it later
	// to the local language.

	aMap[_("All types")] = wxT("All types");
	aMap[_("Schemas")] = wxT("Schemas");
	aMap[_("Tables")] = wxT("Tables");
	aMap[_("Columns")] = wxT("Columns");
	aMap[_("Triggers")] = wxT("Triggers");
	aMap[_("Views")] = wxT("Views");
	aMap[_("Rules")] = wxT("Rules");
	aMap[_("Indexes")] = wxT("Indexes");
	aMap[_("Functions")] = wxT("Functions");
	aMap[_("Aggregates")] = wxT("Aggregates");
	aMap[_("Trigger Functions")] = wxT("Trigger Functions");
	aMap[_("Constraints")] = wxT("Constraints");
	aMap[_("Sequences")] = wxT("Sequences");
	aMap[_("Types")] = wxT("Types");
	aMap[_("Domains")] = wxT("Domains");
	aMap[_("Languages")] = wxT("Languages");
	aMap[_("Conversions")] = wxT("Conversions");
	aMap[_("Casts")] = wxT("Casts");
	aMap[_("Login Roles")] = wxT("Login Roles");
	aMap[_("Group Roles")] = wxT("Group Roles");
	aMap[_("FTS Configurations")] = wxT("FTS Configurations");
	aMap[_("FTS Dictionaries")] = wxT("FTS Dictionaries");
	aMap[_("FTS Parsers")] = wxT("FTS Parsers");
	aMap[_("FTS Templates")] = wxT("FTS Templates");
	aMap[_("Foreign Data Wrappers")] = wxT("Foreign Data Wrappers");
	aMap[_("Foreign Servers")] = wxT("Foreign Servers");
	aMap[_("Foreign Tables")] = wxT("Foreign Tables");
	aMap[_("User Mappings")] = wxT("User Mappings");
	aMap[_("Operators")] = wxT("Operators");
	aMap[_("Operator Classes")] = wxT("Operator Classes");
	aMap[_("Operator Families")] = wxT("Operator Families");
	aMap[_("Extensions")] = wxT("Extensions");
	aMap[_("Collations")] = wxT("Collations");

	cbType->Clear();
	cbType->Append(_("All types"));
	cbType->Append(_("Schemas"));
	cbType->Append(_("Tables"));
	cbType->Append(_("Columns"));
	cbType->Append(_("Triggers"));
	cbType->Append(_("Views"));
	cbType->Append(_("Rules"));
	cbType->Append(_("Indexes"));
	cbType->Append(_("Functions"));
	cbType->Append(_("Aggregates"));
	cbType->Append(_("Trigger Functions"));
	cbType->Append(_("Constraints"));
	cbType->Append(_("Sequences"));
	cbType->Append(_("Types"));
	cbType->Append(_("Languages"));
	cbType->Append(_("Domains"));
	cbType->Append(_("Conversions"));
	cbType->Append(_("Casts"));
	cbType->Append(_("Login Roles"));
	cbType->Append(_("Group Roles"));
	cbType->Append(_("FTS Configurations"));
	cbType->Append(_("FTS Dictionaries"));
	cbType->Append(_("FTS Parsers"));
	cbType->Append(_("FTS Templates"));
	if(currentdb->BackendMinimumVersion(8, 4))
	{
		cbType->Append(_("Foreign Data Wrappers"));
		cbType->Append(_("Foreign Servers"));
		cbType->Append(_("User Mappings"));
	}
	if(currentdb->BackendMinimumVersion(9, 1))
	{
		cbType->Append(_("Foreign Tables"));
	}
	cbType->Append(_("Operators"));
	cbType->Append(_("Operator Classes"));
	cbType->Append(_("Operator Families"));

	if(currentdb->BackendMinimumVersion(9, 1))
	{
		cbType->Append(_("Extensions"));
		cbType->Append(_("Collations"));
	}
	cbType->SetSelection(0);

	txtPattern->SetFocus();
}