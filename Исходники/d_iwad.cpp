void FIWadManager::ParseIWadInfo(const char *fn, const char *data, int datasize)
{
	FScanner sc;

	sc.OpenMem("IWADINFO", data, datasize);
	while (sc.GetString())
	{
		if (sc.Compare("IWAD"))
		{
			FIWADInfo *iwad = &mIWads[mIWads.Reserve(1)];
			sc.MustGetStringName("{");
			while (!sc.CheckString("}"))
			{
				sc.MustGetString();
				if (sc.Compare("Name"))
				{
					sc.MustGetStringName("=");
					sc.MustGetString();
					iwad->Name = sc.String;
				}
				else if (sc.Compare("Autoname"))
				{
					sc.MustGetStringName("=");
					sc.MustGetString();
					iwad->Autoname = sc.String;
				}
				else if (sc.Compare("Config"))
				{
					sc.MustGetStringName("=");
					sc.MustGetString();
					iwad->Configname = sc.String;
				}
				else if (sc.Compare("Game"))
				{
					sc.MustGetStringName("=");
					sc.MustGetString();
					if (sc.Compare("Doom")) iwad->gametype = GAME_Doom;
					else if (sc.Compare("Heretic")) iwad->gametype = GAME_Heretic;
					else if (sc.Compare("Hexen")) iwad->gametype = GAME_Hexen;
					else if (sc.Compare("Strife")) iwad->gametype = GAME_Strife;
					else if (sc.Compare("Chex")) iwad->gametype = GAME_Chex;
					else sc.ScriptError(NULL);
				}
				else if (sc.Compare("Mapinfo"))
				{
					sc.MustGetStringName("=");
					sc.MustGetString();
					iwad->MapInfo = sc.String;
				}
				else if (sc.Compare("Compatibility"))
				{
					sc.MustGetStringName("=");
					do
					{
						sc.MustGetString();
						if(sc.Compare("NoTextcolor")) iwad->flags |= GI_NOTEXTCOLOR;
						else if(sc.Compare("Poly1")) iwad->flags |= GI_COMPATPOLY1;
						else if(sc.Compare("Poly2")) iwad->flags |= GI_COMPATPOLY2;
						else if(sc.Compare("Shareware")) iwad->flags |= GI_SHAREWARE;
						else if(sc.Compare("Teaser2")) iwad->flags |= GI_TEASER2;
						else if(sc.Compare("Extended")) iwad->flags |= GI_MENUHACK_EXTENDED;
						else if(sc.Compare("Shorttex")) iwad->flags |= GI_COMPATSHORTTEX;
						else if(sc.Compare("Stairs")) iwad->flags |= GI_COMPATSTAIRS;
						else sc.ScriptError(NULL);
					}
					while (sc.CheckString(","));
				}
				else if (sc.Compare("MustContain"))
				{
					sc.MustGetStringName("=");
					do
					{
						sc.MustGetString();
						iwad->Lumps.Push(FString(sc.String));
					}
					while (sc.CheckString(","));
				}
				else if (sc.Compare("BannerColors"))
				{
					sc.MustGetStringName("=");
					sc.MustGetString();
					iwad->FgColor = V_GetColor(NULL, sc.String);
					sc.MustGetStringName(",");
					sc.MustGetString();
					iwad->BkColor = V_GetColor(NULL, sc.String);
				}
				else if (sc.Compare("Load"))
				{
					sc.MustGetStringName("=");
					do
					{
						sc.MustGetString();
						iwad->Load.Push(FString(sc.String));
					}
					while (sc.CheckString(","));
				}
				else if (sc.Compare("Required"))
				{
					sc.MustGetStringName("=");
					sc.MustGetString();
					iwad->Required = sc.String;
				}
				else
				{
					sc.ScriptError("Unknown keyword '%s'", sc.String);
				}
			}
		}
		else if (sc.Compare("NAMES"))
		{
			sc.MustGetStringName("{");
			mIWadNames.Push(FString());
			while (!sc.CheckString("}"))
			{
				sc.MustGetString();
				FString wadname = sc.String;
#if defined(_WIN32) || defined(__APPLE__) // Turns out Mac OS X is case insensitive.
				mIWadNames.Push(wadname);
#else
				// check for lowercase, uppercased first letter and full uppercase on Linux etc.
				wadname.ToLower();
				mIWadNames.Push(wadname);
				wadname.LockBuffer()[0] = toupper(wadname[0]);
				wadname.UnlockBuffer();
				mIWadNames.Push(wadname);
				wadname.ToUpper();
				mIWadNames.Push(wadname);
#endif
			}
		}
	}
}