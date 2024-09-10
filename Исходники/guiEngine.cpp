GUIEngine::GUIEngine(	irr::IrrlichtDevice* dev,
						gui::IGUIElement* parent,
						IMenuManager *menumgr,
						scene::ISceneManager* smgr,
						MainMenuData* data,
						bool& kill) :
	m_device(dev),
	m_parent(parent),
	m_menumanager(menumgr),
	m_smgr(smgr),
	m_data(data),
	m_texture_source(NULL),
	m_sound_manager(NULL),
	m_formspecgui(0),
	m_buttonhandler(0),
	m_menu(0),
	m_kill(kill),
	m_startgame(false),
	m_script(0),
	m_scriptdir(""),
	m_irr_toplefttext(0),
	m_clouds_enabled(true),
	m_cloud()
{
	//initialize texture pointers
	for (unsigned int i = 0; i < TEX_LAYER_MAX; i++) {
		m_textures[i].texture = NULL;
	}
	// is deleted by guiformspec!
	m_buttonhandler = new TextDestGuiEngine(this);

	//create texture source
	m_texture_source = new MenuTextureSource(m_device->getVideoDriver());

	//create soundmanager
	MenuMusicFetcher soundfetcher;
#if USE_SOUND
	m_sound_manager = createOpenALSoundManager(&soundfetcher);
#endif
	if(!m_sound_manager)
		m_sound_manager = &dummySoundManager;

	//create topleft header
	std::wstring t = utf8_to_wide(std::string(PROJECT_NAME_C " ") +
			g_version_hash);

	core::rect<s32> rect(0, 0, g_fontengine->getTextWidth(t), g_fontengine->getTextHeight());
	rect += v2s32(4, 0);

	m_irr_toplefttext =
		m_device->getGUIEnvironment()->addStaticText(t.c_str(),
		rect,false,true,0,-1);

	//create formspecsource
	m_formspecgui = new FormspecFormSource("");

	/* Create menu */
	m_menu = new GUIFormSpecMenu(m_device,
			m_parent,
			-1,
			m_menumanager,
			NULL /* &client */,
			NULL /* gamedef */,
			m_texture_source,
			m_formspecgui,
			m_buttonhandler,
			NULL,
			false);

	m_menu->allowClose(false);
	m_menu->lockSize(true,v2u32(800,600));

	// Initialize scripting

	infostream << "GUIEngine: Initializing Lua" << std::endl;

	m_script = new MainMenuScripting(this);

	try {
		if (m_data->errormessage != "") {
			m_script->setMainMenuErrorMessage(m_data->errormessage);
			m_data->errormessage = "";
		}

		if (!loadMainMenuScript()) {
			errorstream << "No future without mainmenu" << std::endl;
			abort();
		}

		run();
	}
	catch(LuaError &e) {
		errorstream << "MAINMENU ERROR: " << e.what() << std::endl;
		m_data->errormessage = e.what();
	}

	m_menu->quitMenu();
	m_menu->drop();
	m_menu = NULL;
}