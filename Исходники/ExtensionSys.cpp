void CExtensionManager::OnRootConsoleCommand(const char *cmdname, const CCommand &command)
{
	int argcount = smcore.Argc(command);
	if (argcount >= 3)
	{
		const char *cmd = smcore.Arg(command, 2);
		if (strcmp(cmd, "list") == 0)
		{
			List<CExtension *>::iterator iter;
			CExtension *pExt;
			unsigned int num = 1;
			switch (m_Libs.size())
			{
			case 1:
				{
					rootmenu->ConsolePrint("[SM] Displaying 1 extension:");
					break;
				}
			case 0:
				{
					rootmenu->ConsolePrint("[SM] No extensions are loaded.");
					break;
				}
			default:
				{
					rootmenu->ConsolePrint("[SM] Displaying %d extensions:", m_Libs.size());
					break;
				}
			}
			for (iter=m_Libs.begin(); iter!=m_Libs.end(); iter++,num++)
			{
				pExt = (*iter);
				if (pExt->IsLoaded())
				{
					char error[255];
					if (!pExt->IsRunning(error, sizeof(error)))
					{
						rootmenu->ConsolePrint("[%02d] <FAILED> file \"%s\": %s", num, pExt->GetFilename(), error);
					}
					else
					{
						IExtensionInterface *pAPI = pExt->GetAPI();
						const char *name = pAPI->GetExtensionName();
						const char *version = pAPI->GetExtensionVerString();
						const char *descr = pAPI->GetExtensionDescription();
						rootmenu->ConsolePrint("[%02d] %s (%s): %s", num, name, version, descr);
					}
				} else {
					rootmenu->ConsolePrint("[%02d] <FAILED> file \"%s\": %s", num, pExt->GetFilename(), pExt->m_Error.c_str());
				}
			}
			return;
		}
		else if (strcmp(cmd, "load") == 0)
		{
			if (argcount < 4)
			{
				rootmenu->ConsolePrint("[SM] Usage: sm exts load <file>");
				return;
			}

			const char *filename = smcore.Arg(command, 3);
			char path[PLATFORM_MAX_PATH];
			char error[256];

			smcore.Format(path, sizeof(path), "%s%s%s", filename, !strstr(filename, ".ext") ? ".ext" : "",
				!strstr(filename, "." PLATFORM_LIB_EXT) ? "." PLATFORM_LIB_EXT : "");
			
			if (FindExtensionByFile(path) != NULL)
			{
				rootmenu->ConsolePrint("[SM] Extension %s is already loaded.", path);
				return;
			}
			
			if (LoadExtension(path, error, sizeof(error)))
			{
				rootmenu->ConsolePrint("[SM] Loaded extension %s successfully.", path);
			} else
			{
				rootmenu->ConsolePrint("[SM] Extension %s failed to load: %s", path, error);
			}
			
			return;
		}
		else if (strcmp(cmd, "info") == 0)
		{
			if (argcount < 4)
			{
				rootmenu->ConsolePrint("[SM] Usage: sm exts info <#>");
				return;
			}

			const char *sId = smcore.Arg(command, 3);
			unsigned int id = atoi(sId);
			if (id <= 0)
			{
				rootmenu->ConsolePrint("[SM] Usage: sm exts info <#>");
				return;
			}

			if (m_Libs.size() == 0)
			{
				rootmenu->ConsolePrint("[SM] No extensions are loaded.");
				return;
			}

			if (id > m_Libs.size())
			{
				rootmenu->ConsolePrint("[SM] No extension was found with id %d.", id);
				return;
			}

			List<CExtension *>::iterator iter = m_Libs.begin();
			CExtension *pExt = NULL;
			while (iter != m_Libs.end())
			{
				if (--id == 0)
				{
					pExt = (*iter);
					break;
				}
				iter++;
			}
			/* This should never happen */
			if (!pExt)
			{
				rootmenu->ConsolePrint("[SM] No extension was found with id %d.", id);
				return;
			}

			if (!pExt->IsLoaded())
			{
				rootmenu->ConsolePrint(" File: %s", pExt->GetFilename());
				rootmenu->ConsolePrint(" Loaded: No (%s)", pExt->m_Error.c_str());
			}
			else
			{
				char error[255];
				if (!pExt->IsRunning(error, sizeof(error)))
				{
					rootmenu->ConsolePrint(" File: %s", pExt->GetFilename());
					rootmenu->ConsolePrint(" Loaded: Yes");
					rootmenu->ConsolePrint(" Running: No (%s)", error);
				}
				else
				{
					IExtensionInterface *pAPI = pExt->GetAPI();
					rootmenu->ConsolePrint(" File: %s", pExt->GetFilename());
					rootmenu->ConsolePrint(" Loaded: Yes (version %s)", pAPI->GetExtensionVerString());
					rootmenu->ConsolePrint(" Name: %s (%s)", pAPI->GetExtensionName(), pAPI->GetExtensionDescription());
					rootmenu->ConsolePrint(" Author: %s (%s)", pAPI->GetExtensionAuthor(), pAPI->GetExtensionURL());
					rootmenu->ConsolePrint(" Binary info: API version %d (compiled %s)", pAPI->GetExtensionVersion(), pAPI->GetExtensionDateString());

					if (pExt->IsExternal())
					{
						rootmenu->ConsolePrint(" Method: Loaded by Metamod:Source, attached to SourceMod");
					}
					else if (pAPI->IsMetamodExtension())
					{
						rootmenu->ConsolePrint(" Method: Loaded by SourceMod, attached to Metamod:Source");
					}
					else
					{
						rootmenu->ConsolePrint(" Method: Loaded by SourceMod");
					}
				}
			}
			return;
		}
		else if (strcmp(cmd, "unload") == 0)
		{
			if (argcount < 4)
			{
				rootmenu->ConsolePrint("[SM] Usage: sm exts unload <#> [code]");
				return;
			}

			const char *arg = smcore.Arg(command, 3);
			unsigned int num = atoi(arg);
			CExtension *pExt = FindByOrder(num);

			if (!pExt)
			{
				rootmenu->ConsolePrint("[SM] Extension number %d was not found.", num);
				return;
			}

			if (argcount > 4 && pExt->unload_code)
			{
				const char *unload = smcore.Arg(command, 4);
				if (pExt->unload_code == (unsigned)atoi(unload))
				{
					char filename[PLATFORM_MAX_PATH];
					snprintf(filename, PLATFORM_MAX_PATH, "%s", pExt->GetFilename());
					UnloadExtension(pExt);
					rootmenu->ConsolePrint("[SM] Extension %s is now unloaded.", filename);
				}
				else
				{
					rootmenu->ConsolePrint("[SM] Please try again, the correct unload code is \"%d\"", pExt->unload_code);
				}
				return;
			}

			if (!pExt->IsLoaded() 
				|| (!pExt->m_ChildDeps.size() && !pExt->m_Dependents.size()))
			{
				char filename[PLATFORM_MAX_PATH];
				snprintf(filename, PLATFORM_MAX_PATH, "%s", pExt->GetFilename());
				UnloadExtension(pExt);
				rootmenu->ConsolePrint("[SM] Extension %s is now unloaded.", filename);
				return;
			}
			else
			{
				List<CPlugin *> plugins;
				if (pExt->m_ChildDeps.size())
				{
					rootmenu->ConsolePrint("[SM] Unloading %s will unload the following extensions: ", pExt->GetFilename());
					List<CExtension *>::iterator iter;
					CExtension *pOther;
					/* Get list of all extensions */
					for (iter=m_Libs.begin(); iter!=m_Libs.end(); iter++)
					{
						List<IfaceInfo>::iterator i_iter;
						pOther = (*iter);
						if (!pOther->IsLoaded() || pOther == pExt)
						{
							continue;
						}
						/* Get their dependencies */
						for (i_iter=pOther->m_Deps.begin();
							 i_iter!=pOther->m_Deps.end();
							 i_iter++)
						{
							/* Is this dependency to us? */
							if ((*i_iter).owner != pExt)
							{
								continue;
							}
							/* Will our dependent care? */
							if (!pExt->GetAPI()->QueryInterfaceDrop((*i_iter).iface))
							{
								rootmenu->ConsolePrint(" -> %s", pExt->GetFilename());
								/* Add to plugin unload list */
								List<CPlugin *>::iterator p_iter;
								for (p_iter=pOther->m_Dependents.begin();
									 p_iter!=pOther->m_Dependents.end();
									 p_iter++)
								{
									if (plugins.find((*p_iter)) == plugins.end())
									{
										plugins.push_back((*p_iter));
									}
								}
							}
						}
					}
				}
				if (pExt->m_Dependents.size())
				{
					rootmenu->ConsolePrint("[SM] Unloading %s will unload the following plugins: ", pExt->GetFilename());
					List<CPlugin *>::iterator iter;
					CPlugin *pPlugin;
					for (iter = pExt->m_Dependents.begin(); iter != pExt->m_Dependents.end(); iter++)
					{
						pPlugin = (*iter);
						if (plugins.find(pPlugin) == plugins.end())
						{
							plugins.push_back(pPlugin);
						}
					}
					for (iter = plugins.begin(); iter != plugins.end(); iter++)
					{
						pPlugin = (*iter);
						rootmenu->ConsolePrint(" -> %s", pPlugin->GetFilename());
					}
				}
				srand(static_cast<int>(time(NULL)));
				pExt->unload_code = (rand() % 877) + 123;	//123 to 999
				rootmenu->ConsolePrint("[SM] To verify unloading %s, please use the following: ", pExt->GetFilename());
				rootmenu->ConsolePrint("[SM] sm exts unload %d %d", num, pExt->unload_code);

				return;
			}
		}
		else if (strcmp(cmd, "reload") == 0)
		{
			if (argcount < 4)
			{
				rootmenu->ConsolePrint("[SM] Usage: sm exts reload <#>");
				return;
			}
			
			const char *arg = smcore.Arg(command, 3);
			unsigned int num = atoi(arg);
			CExtension *pExt = FindByOrder(num);

			if (!pExt)
			{
				rootmenu->ConsolePrint("[SM] Extension number %d was not found.", num);
				return;
			}
			
			if (pExt->IsLoaded())
			{
				char filename[PLATFORM_MAX_PATH];
				char error[255];
				
				snprintf(filename, PLATFORM_MAX_PATH, "%s", pExt->GetFilename());
				
				if (pExt->Reload(error, sizeof(error)))
				{
					rootmenu->ConsolePrint("[SM] Extension %s is now reloaded.", filename);
				}
				else
				{
					rootmenu->ConsolePrint("[SM] Extension %s failed to reload: %s", filename, error);
				}
					
				return;
			} 
			else
			{
				rootmenu->ConsolePrint("[SM] Extension %s is not loaded.", pExt->GetFilename());
				
				return;
			}
			
		}
	}

	rootmenu->ConsolePrint("SourceMod Extensions Menu:");
	rootmenu->DrawGenericOption("info", "Extra extension information");
	rootmenu->DrawGenericOption("list", "List extensions");
	rootmenu->DrawGenericOption("load", "Load an extension");
	rootmenu->DrawGenericOption("reload", "Reload an extension");
	rootmenu->DrawGenericOption("unload", "Unload an extension");
}