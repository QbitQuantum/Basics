void cWebAdmin::HandleWebadminRequest(cHTTPConnection & a_Connection, cHTTPRequest & a_Request)
{
	if (!a_Request.HasAuth())
	{
		a_Connection.SendNeedAuth("MCServer WebAdmin");
		return;
	}

	// Check auth:
	AString UserPassword = m_IniFile.GetValue("User:"******"Password", "");
	if ((UserPassword == "") || (a_Request.GetAuthPassword() != UserPassword))
	{
		a_Connection.SendNeedAuth("MCServer WebAdmin - bad username or password");
		return;
	}

	// Check if the contents should be wrapped in the template:
	AString URL = a_Request.GetBareURL();
	ASSERT(URL.length() > 0);
	bool ShouldWrapInTemplate = ((URL.length() > 1) && (URL[1] != '~'));

	// Retrieve the request data:
	cWebadminRequestData * Data = (cWebadminRequestData *)(a_Request.GetUserData());
	if (Data == NULL)
	{
		a_Connection.SendStatusAndReason(500, "Bad UserData");
		return;
	}

	// Wrap it all up for the Lua call:
	AString Template;
	HTTPTemplateRequest TemplateRequest;
	TemplateRequest.Request.Username = a_Request.GetAuthUsername();
	TemplateRequest.Request.Method = a_Request.GetMethod();
	TemplateRequest.Request.Path = URL.substr(1);

	if (Data->m_Form.Finish())
	{
		for (cHTTPFormParser::const_iterator itr = Data->m_Form.begin(), end = Data->m_Form.end(); itr != end; ++itr)
		{
			HTTPFormData HTTPfd;
			HTTPfd.Value = itr->second;
			HTTPfd.Type = "";
			HTTPfd.Name = itr->first;
			TemplateRequest.Request.FormData[itr->first] = HTTPfd;
			TemplateRequest.Request.PostParams[itr->first] = itr->second;
		}  // for itr - Data->m_Form[]

		// Parse the URL into individual params:
		size_t idxQM = a_Request.GetURL().find('?');
		if (idxQM != AString::npos)
		{
			cHTTPFormParser URLParams(cHTTPFormParser::fpkURL, a_Request.GetURL().c_str() + idxQM + 1, a_Request.GetURL().length() - idxQM - 1, *Data);
			URLParams.Finish();
			for (cHTTPFormParser::const_iterator itr = URLParams.begin(), end = URLParams.end(); itr != end; ++itr)
			{
				TemplateRequest.Request.Params[itr->first] = itr->second;
			}  // for itr - URLParams[]
		}
	}

	// Try to get the template from the Lua template script
	if (ShouldWrapInTemplate)
	{
		if (m_TemplateScript.Call("ShowPage", this, &TemplateRequest, cLuaState::Return, Template))
		{
			cHTTPResponse Resp;
			Resp.SetContentType("text/html");
			a_Connection.Send(Resp);
			a_Connection.Send(Template.c_str(), Template.length());
			return;
		}
		a_Connection.SendStatusAndReason(500, "m_TemplateScript failed");
		return;
	}

	AString BaseURL = GetBaseURL(URL);
	AString Menu;
	Template = "{CONTENT}";
	AString FoundPlugin;

	for (PluginList::iterator itr = m_Plugins.begin(); itr != m_Plugins.end(); ++itr)
	{
		cWebPlugin * WebPlugin = *itr;
		std::list< std::pair<AString, AString> > NameList = WebPlugin->GetTabNames();
		for (std::list< std::pair<AString, AString> >::iterator Names = NameList.begin(); Names != NameList.end(); ++Names)
		{
			Menu += "<li><a href='" + BaseURL + WebPlugin->GetWebTitle().c_str() + "/" + (*Names).second + "'>" + (*Names).first + "</a></li>";
		}
	}

	sWebAdminPage Page = GetPage(TemplateRequest.Request);
	AString Content = Page.Content;
	FoundPlugin = Page.PluginName;
	if (!Page.TabName.empty())
	{
		FoundPlugin += " - " + Page.TabName;
	}

	if (FoundPlugin.empty())  // Default page
	{
		Content = GetDefaultPage();
	}

	if (ShouldWrapInTemplate && (URL.size() > 1))
	{
		Content += "\n<p><a href='" + BaseURL + "'>Go back</a></p>";
	}

	int MemUsageKiB = cRoot::GetPhysicalRAMUsage();
	if (MemUsageKiB > 0)
	{
		ReplaceString(Template, "{MEM}",       Printf("%.02f", (double)MemUsageKiB / 1024));
		ReplaceString(Template, "{MEMKIB}",    Printf("%d", MemUsageKiB));
	}
	else
	{
		ReplaceString(Template, "{MEM}",       "unknown");
		ReplaceString(Template, "{MEMKIB}",    "unknown");
	}
	ReplaceString(Template, "{USERNAME}",    a_Request.GetAuthUsername());
	ReplaceString(Template, "{MENU}",        Menu);
	ReplaceString(Template, "{PLUGIN_NAME}", FoundPlugin);
	ReplaceString(Template, "{CONTENT}",     Content);
	ReplaceString(Template, "{TITLE}",       "MCServer");

	AString NumChunks;
	Printf(NumChunks, "%d", cRoot::Get()->GetTotalChunkCount());
	ReplaceString(Template, "{NUMCHUNKS}", NumChunks);

	cHTTPResponse Resp;
	Resp.SetContentType("text/html");
	a_Connection.Send(Resp);
	a_Connection.Send(Template.c_str(), Template.length());
}