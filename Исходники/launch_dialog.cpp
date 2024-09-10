	void initDialog( HWND hwnd )
	{
		addComboItems( GetDlgItem( hwnd, IDC_COMBOLANGUAGE ), manager.getOptionNames( "Language" ), manager.getTheOneInUse( "Language" ) );
		addComboItems( GetDlgItem( hwnd, IDC_COMBORESOLUTION ), manager.getOptionNames( "Resolution" ), manager.getTheOneInUse( "Resolution" ) );
		addComboItems( GetDlgItem( hwnd, IDC_COMBOGFXDETAIL ), manager.getOptionNames( "GraphicsDetail" ), manager.getTheOneInUse( "GraphicsDetail" ) );
		addComboItems( GetDlgItem( hwnd, IDC_COMBOSPEAKERTYPE ), manager.getOptionNames( "SpeakerType" ), manager.getTheOneInUse( "SpeakerType" ) );
		addComboItems( GetDlgItem( hwnd, IDC_COMBOMIXINGRATE ), manager.getOptionNames( "MixingRate" ), manager.getTheOneInUse( "MixingRate" ) );
		addComboItems( GetDlgItem( hwnd, IDC_COMBOPHYSICSDETAIL ),	manager.getOptionNames( "Physics Quality" ),	manager.getTheOneInUse( "Physics Quality" ) );
		addComboItems( GetDlgItem( hwnd, IDC_COMBOCONTROLTYPE ),	manager.getOptionNames( "ClawControlType" ),	manager.getTheOneInUse( "ClawControlType" ) );
	   // IDC_COMBOCONTROLTYPE	
		setCheckBox( hwnd, IDC_CHECKSOUND, manager.getTheOneInUse( "Sounds" ) );
		setCheckBox( hwnd, IDC_CHECKHARDWARE3D, manager.getTheOneInUse( "Hardware3D" ) );
		setCheckBox( hwnd, IDC_CHECKENABLEMENUVIDEO, manager.getTheOneInUse( "EnableMenuVideo" ) );
		setCheckBox( hwnd, IDC_CHECKENABLEMENUVSYNC, manager.getTheOneInUse( "VSync" ) );
		setCheckBox( hwnd, IDC_CHECKEAX, manager.getTheOneInUse( "Eax" ) );

		//SendMessage( hwnd, CB_ADDSTRING, 0, ( LPARAM ) game::getLocaleGuiString( items[ i ].c_str() ) );
		//SendMessage( hwnd, CB_SELECTSTRING, -1, ( LPARAM )game::getLocaleGuiString( select.c_str() ) );

		// Mod stuff
		setDescriptionText( GetDlgItem( hwnd, IDC_MOD_HELP ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_LAUNCHER_MOD_SELECTION ) );
		{
			SendMessage( GetDlgItem( hwnd, IDC_COMBOMODSELECTION ), CB_RESETCONTENT, 0, 0);

#ifdef FB_RU_HAX
			std::wstring nomod = ::game::DHLocaleManager::getInstance()->getWideString(::game::DHLocaleManager::BANK_GUI, "launcher_no_mod");
			SendMessageW( GetDlgItem( hwnd, IDC_COMBOMODSELECTION ), CB_ADDSTRING, (WPARAM)0, (LPARAM) nomod.c_str() );

#else
			std::string nomod = game::getLocaleGuiString("launcher_no_mod");
			SendMessage( GetDlgItem( hwnd, IDC_COMBOMODSELECTION ), CB_ADDSTRING, 0, ( LPARAM ) nomod.c_str());
#endif

			for(int i = 0; i < modSelector.getModAmount(); ++i)
			{
				const std::string &desc = modSelector.getDescription(i);
				SendMessage( GetDlgItem( hwnd, IDC_COMBOMODSELECTION ), CB_ADDSTRING, 0, ( LPARAM ) desc.c_str());
			}

			int selection = modSelector.getActiveIndex();
			SendMessage( GetDlgItem( hwnd, IDC_COMBOMODSELECTION ), CB_SETCURSEL, selection + 1, 0);
			/*
			if(selection >= 0)
				SendMessage( GetDlgItem( hwnd, IDC_COMBOMODSELECTION ), CB_SETCURSEL, selection + 1, 0);
			else
				SendMessage( GetDlgItem( hwnd, IDC_COMBOMODSELECTION ), CB_SETCURSEL, 0, 0);
			*/

			/*
			const std::string root = "Mods";

			filesystem::StandardPackage files;
			filesystem::FileList fileList;
			files.findFiles(root, "*.zip", fileList);

			modList.clear();
			modStringList.clear();

			for(int i = 0; i < fileList.getFileAmount(root); ++i)
			{
				const std::string &zipFullName = fileList.getFileName(root, i);
				std::string zipName;
				int index = zipFullName.find_first_of("/\\");
				if(index != zipFullName.npos)
					zipName = zipFullName.substr(index + 1, zipFullName.size() - index - 1);

				filesystem::ZipPackage zip(zipFullName);
				filesystem::InputStream stream = zip.getFile("description.txt");
				if(stream.isEof())
					continue;

				editor::Parser parser;
				stream >> parser;

				const editor::ParserGroup &group = parser.getGlobals();
				if(group.getLineCount() < 1)
					continue;

				std::string name = group.getLine(0);
				if(name.size() < 4)
					continue;

				modList[name] = zipName;
				modStringList.push_back(name);
			}

			std::sort(modStringList.begin(), modStringList.end());

			// FIXME -- get key from locales
			SendMessage( GetDlgItem( hwnd, IDC_COMBOMODSELECTION ), CB_ADDSTRING, 0, ( LPARAM ) "Nothing. Zip. Nada");
			for(unsigned int i = 0; i < modStringList.size(); ++i)
				SendMessage( GetDlgItem( hwnd, IDC_COMBOMODSELECTION ), CB_ADDSTRING, 0, ( LPARAM ) modStringList[i].c_str());
			
			//if no mod selected
				SendMessage( GetDlgItem( hwnd, IDC_COMBOMODSELECTION ), CB_SETCURSEL, 0, 0);
			*/
		}

		// Editor things
		setDescriptionText( GetDlgItem( hwnd, IDC_EDITOR_HELP ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_LAUNCHER_EDITOR ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_EDITOR_MANUAL ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_EDITOR_LAUNCH ) );


		// buttons
		setDescriptionText( GetDlgItem( hwnd, IDOK ) );
		setDescriptionText( GetDlgItem( hwnd, IDCANCEL ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_BUTTONADVANCED ) );
		setDescriptionText( GetDlgItem( hwnd, IDCHECKUPDATES ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_ACTIVATEMOD ) );

		// language
		setDescriptionText( GetDlgItem( hwnd, IDC_CAPTION1 ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_CAPTION6 ) );
		
		// graphics detail
		setDescriptionText( GetDlgItem( hwnd, IDC_STATICGRAPHICSLEVEL ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_CAPTION2 ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_CAPTION3 ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_CHECKENABLEMENUVIDEO ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_CHECKENABLEMENUVSYNC ) );

		// physics
		setDescriptionText( GetDlgItem( hwnd, IDC_STATICPHYSICSLEVEL ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_AGEIAPROPAGANDA ) );


		// sounds
		setDescriptionText( GetDlgItem( hwnd, IDC_STATICSOUNDS ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_CHECKSOUND ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_CHECKHARDWARE3D ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_CAPTION4 ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_CAPTION5 ) );
		setDescriptionText( GetDlgItem( hwnd, IDC_CHECKEAX ) );

		
	}