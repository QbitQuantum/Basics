dlgHbaConfig::dlgHbaConfig(pgFrame *parent, pgHbaConfigLine *_line, pgConn *_conn) :
	DialogWithHelp((frmMain *)parent)
{
	wxWindowBase::SetFont(settings->GetSystemFont());
	LoadResource((wxWindow *)parent, wxT("dlgHbaConfig"));

	conn = _conn;

	userAdding = databaseAdding = false;

	// Icon
	SetIcon(*property_png_ico);
	RestorePosition();

	line = _line;

	cbType->Append(wxT("local"));
	cbType->Append(wxT("host"));
	cbType->Append(wxT("hostssl"));
	cbType->Append(wxT("hostnossl"));

	cbDatabase->Append(wxT("all"));
	cbDatabase->Append(wxT("sameuser"));
	cbDatabase->Append(wxT("@<filename>"));
	if (conn)
	{
		// role is supported from 8.1
		if (conn->BackendMinimumVersion(8, 1))
			cbDatabase->Append(wxT("samerole"));
		else
			cbDatabase->Append(wxT("samegroup"));

		// replication is supported from 9.0
		if (conn->BackendMinimumVersion(9, 0))
			cbDatabase->Append(wxT("replication"));
	}
	else
	{
		cbDatabase->Append(wxT("samegroup"));
		cbDatabase->Append(wxT("samerole"));
		cbDatabase->Append(wxT("replication"));
	}

	cbUser->Append(wxT("all"));

	cbMethod->Append(wxT("trust"));
	cbMethod->Append(wxT("reject"));
	cbMethod->Append(wxT("md5"));
	cbMethod->Append(wxT("password"));
	cbMethod->Append(wxT("krb4"));
	cbMethod->Append(wxT("krb5"));
	cbMethod->Append(wxT("ident"));
	cbMethod->Append(wxT("pam"));

	if (conn)
	{
		// LDAP is supported from 8.2
		if (conn->BackendMinimumVersion(8, 2))
			cbMethod->Append(wxT("ldap"));

		// GSS/SSPI are supported from 8.3
		if (conn->BackendMinimumVersion(8, 3))
		{
			cbMethod->Append(wxT("gss"));
			cbMethod->Append(wxT("sspi"));
		}

		// CERT is supported from 8.4
		// but crypt is no longer supported in 8.4
		if (conn->BackendMinimumVersion(8, 4))
		{
			cbMethod->Append(wxT("cert"));
		}
		else
		{
			cbMethod->Append(wxT("crypt"));
		}

		// Radius is supported from 9.0
		if (conn->BackendMinimumVersion(9, 0))
		{
			cbMethod->Append(wxT("radius"));
		}

		// Peer is supported from 9.1
		if (conn->BackendMinimumVersion(9, 1))
		{
			cbMethod->Append(wxT("peer"));
		}
	}
	else
	{
		// Add all version-dependent methods if we don't know what version we have.
		cbMethod->Append(wxT("ldap"));
		cbMethod->Append(wxT("gss"));
		cbMethod->Append(wxT("sspi"));
		cbMethod->Append(wxT("cert"));
		cbMethod->Append(wxT("crypt"));
		cbMethod->Append(wxT("radius"));
		cbMethod->Append(wxT("peer"));
	}

	if (conn)
	{
		pgSet *set = conn->ExecuteSet(wxT("SELECT datname FROM pg_database"));
		if (set)
		{
			while (!set->Eof())
			{
				cbDatabase->Append(set->GetVal(0));
				set->MoveNext();
			}
			delete set;
		}

		wxString sql = wxT("SELECT usename FROM pg_user\n")
		               wxT("UNION\n")
		               wxT("SELECT 'group ' || groname FROM pg_group");
		set = conn->ExecuteSet(sql);
		if (set)
		{
			while (!set->Eof())
			{
				cbUser->Append(set->GetVal(0));
				set->MoveNext();
			}
			delete set;
		}
	}

	// Setup the default values

	chkEnabled->SetValue(!line->isComment);
	if(line->connectType != pgHbaConfigLine::PGC_INVALIDCONF)
	{
		database = line->database;
		user = line->user;

		cbType->SetSelection(line->connectType);
		cbMethod->SetSelection(line->method);
		cbDatabase->SetValue(database);
		cbUser->SetValue(user);
		txtIPaddress->SetValue(line->ipaddress);
		txtOption->SetValue(line->option);
	}
	wxCommandEvent noEvent;
	OnChange(noEvent);
}