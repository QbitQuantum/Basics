bool Materials::loadExtensions(FileName directoryName, wxString& error, wxArrayString& warnings)
{
	directoryName.Mkdir(0755, wxPATH_MKDIR_FULL); // Create if it doesn't exist

	wxDir ext_dir(directoryName.GetPath());
	if(ext_dir.IsOpened() == false)
	{
		error = wxT("Could not open extensions directory.");
		return false;
	}

	wxString filename;
	if(!ext_dir.GetFirst(&filename))
	{
		// No extensions found
		return true;
	}

	do
	{
		FileName fn;
		fn.SetPath(directoryName.GetPath());
		fn.SetFullName(filename);
		if(fn.GetExt() != wxT("xml"))
			continue;

		xmlDocPtr doc = xmlParseFile(fn.GetFullPath().mb_str());

		if(doc)
		{
			xmlNodePtr root = xmlDocGetRootElement(doc);
			
			if(xmlStrcmp(root->name,(const xmlChar*)"materialsextension") != 0){
				xmlFreeDoc(doc);
				warnings.push_back(filename + wxT(": Invalid rootheader."));
				continue;
			}
			std::string ext_name, ext_url, ext_author, ext_author_link, ext_desc, ext_client_str;
			StringVector clientVersions;
			if(
				!readXMLValue(root, "name", ext_name) ||
				!readXMLValue(root, "author", ext_author) ||
				!readXMLValue(root, "description", ext_desc))
			{
				warnings.push_back(filename + wxT(": Couldn't read extension attributes (name, author, description)."));
				continue;
			}


			readXMLValue(root, "url", ext_url);
			ext_url.erase(std::remove(ext_url.begin(), ext_url.end(), '\''), ext_url.end());
			readXMLValue(root, "authorurl", ext_author_link);
			ext_author_link.erase(std::remove(ext_author_link.begin(), ext_author_link.end(), '\''), ext_author_link.end());

			MaterialsExtension* me = newd MaterialsExtension(ext_name, ext_author, ext_desc);
			me->url = ext_url;
			me->author_url = ext_author_link;

			if(readXMLValue(root, "client", ext_client_str))
			{
				size_t last_pos = std::numeric_limits<size_t>::max();
				size_t pos;
				do
				{
					size_t to_pos = (last_pos == std::numeric_limits<size_t>::max()? 0 : last_pos+1);
					pos = ext_client_str.find(';', to_pos);
					if(size_t(pos) != std::string::npos)
					{
						clientVersions.push_back(ext_client_str.substr(to_pos, pos-(to_pos)));
						last_pos = pos;
					}
					else
					{
						clientVersions.push_back(ext_client_str.substr(to_pos));
						break;
					}
				} while(true);

				for(StringVector::iterator iter = clientVersions.begin();
						iter != clientVersions.end();
						++iter)
				{
					me->addVersion(*iter);
				}

				std::sort(me->version_list.begin(), me->version_list.end(), VersionComparisonPredicate);
				me->version_list.erase(std::unique(me->version_list.begin(), me->version_list.end()), me->version_list.end());
			}
			else
			{
				warnings.push_back(filename + wxT(": Extension is not available for any version."));
			}
			extensions.push_back(me);
			
			if(me->isForVersion(gui.GetCurrentVersionID()))
			{
				unserializeMaterials(filename, root, error, warnings);
			}
		}
		else
		{
			warnings.push_back(wxT("Could not open ") + filename + wxT(" (file not found or syntax error)"));
			continue;
		}
	} while(ext_dir.GetNext(&filename));

	return true;
}