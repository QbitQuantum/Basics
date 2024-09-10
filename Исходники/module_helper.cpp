int module_helper::_load_current_plugins_cfg(const char* cfg_file)
{
	fsys::path p(cfg_file);

	pugi::xml_document doc;
	pugi::xml_parse_result pugi_res = doc.load_file(p.filename().c_str());

	if (pugi_res.status == pugi::xml_parse_status::status_ok)
	{
		for (auto& x : doc.child("plugin_list"))
		{
			string proxy_name = x.attribute("name").as_string();
			string dir = x.attribute("dir").as_string();
			string prefix = x.attribute("prefix").as_string();
			string filename = "";
			string workpath = "";
			boost_error_code ec;
			if (proxy_name != ""  && prefix != "")
			{
				fsys::path p = fsys::current_path() / dir;
				fsys::directory_iterator search_dir(p, ec);
				if (!ec)
				{
					for (auto f : search_dir)
					{
						auto fn = f.path();
						if (!fsys::is_directory(fn, ec) && fn.filename().string().find(prefix) != string::npos && fn.extension().string() == ".dll")
						{
							filename = fn.string();
							workpath = fn.parent_path().string();
							break;
						}
					}
				}
				if (filename == "")
				{
					fsys::path win_dir = string(getenv("windir"));
					fsys::path root_dir(win_dir.root_directory());
					fsys::path media_api_dir = (root_dir / "ProgramData" / "Vistek" / "MediaClientPack");
					if (fsys::exists(media_api_dir, ec) && fsys::is_directory(media_api_dir, ec))
					{
						fsys::directory_iterator search_dir(p, ec);
						if (!ec)
						{
							for (auto f : search_dir)
							{
								auto fn = f.path();
								if (!fsys::is_directory(fn, ec) && fn.filename().string().find(prefix) != string::npos && fn.extension().string() == ".dll")
								{
									filename = fn.string();
									workpath = fn.parent_path().string();
									break;
								}
							}
						}

					}
				}
				bool bLoaded = false;
				if (filename != "")
				{
#ifdef _DEBUG
					
#endif
					/*TCHAR cur_path[1024] = { 0 };
					GetCurrentDirectory(1024, cur_path);
					fsys::path p(filename);
					string curr_path = p.parent_path().string();
					SetCurrentDirectoryA(curr_path.c_str());
					*/
					try
					{
						HMODULE tmp = LoadLibraryA(filename.c_str());
						if (!tmp)
						{
							cout << GetLastError();
							tmp = LoadLibraryExA(filename.c_str(), 0, LOAD_WITH_ALTERED_SEARCH_PATH);
						}
						if (tmp)
						{
							m_plugins_map.insert(proxy_name, tmp);
							bLoaded = true;
						}
					}
					catch (exception *exp)
					{
						cout << "exception" << exp->what() << endl;
					}
					//SetCurrentDirectoryA((char*)cur_path);
#ifdef _DEBUG
					//auto a = GetProcAddress(tmp, "register_device");
#endif
				}
				if (bLoaded)
				{
					cout << "plugin: " << proxy_name << " load ok; filename: " << filename << endl;
				}
				else
				{
					cout << "plugin: " << proxy_name << " load fail; filename: " << filename << endl;
				}
			}
		}
		return v_OK;
	}
	return v_ERR_Bad_XML;
}