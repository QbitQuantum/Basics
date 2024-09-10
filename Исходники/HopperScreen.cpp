    /** HopperScreen, OnInit:
     *  Detailed description.
     *  @param argc TODO
     * @param argv TODO
     * @return TODO
     */
    bool HopperScreen::OnInit( int argc, char* argv[] ){
        // Master()->GetMainCanvas();
        CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
        // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
        m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
        //m_pArialfont =
        // TTF_OpenFont("E:/Projects/C++/Humbug/projects/Humbug/Resources/Fonts/ARIAL.TTF", 24);
        mcol = CColor::White();
        SDL_Surface* tmpfsurf = ( m_Loader.FL_LOADIMG("Intro/HopperScreenBg.png") );

        //SDL_SetColorKey(tmpfsurf, SDL_TRUE, 0xff00ff);
        //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_TRUE, 0xff00ff);
        //SDL_SetSurfaceAlphaMod(tmpfsurf, 0);
        //SDL_SetSurfaceAlphaMod(m_pMainCanvas->GetSurface(), 128);
        m_pBackground.reset( new CCanvas( tmpfsurf ) );

        //CCanvas tmpCanvas( tmpfsurf );
        m_Loader.FreeLast();

        //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
        //m_pBackground->Blit(m_pBackground->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
        m_pMainCanvas->AddUpdateRect( m_pBackground->GetDimension() );

        //"\r\n"
        CColor m_colText = CColor::White();
        std::ostringstream outstring;
        outstring << "Jedzia";
        outstring << " .................... ";
        outstring << "328.123.847";

        CText* text = new CText(m_pArialfont, outstring.str(), m_colText);

        //const boost::function<void(CCanvas*, int)> textMo = mtextfloat;
        //text->AddAnimator(boost::ref( mtextfloat ));
        text->AddAnimator( WavyTextFloat(64) );
        m_pScrollText.reset(text);

        // ### Sprites ###
        m_pSprEye = new CSprite(m_Loader, "Sprites/male_sprites.png", m_pMainCanvas, CPoint(64, 0),
                CRectangle(0, 0, 64, 64) );
        m_pSprMgr->AddSprite(m_pSprEye, "mytag", hspriv::EyeMover(160, 8));
        //m_pSprMgr->AddSprite(m_pSprEye, boost::ref( pimpl_->eyemover ) );
        //m_pSprMgr->AddSprite(m_pSprEye);
        CSprite* m_pSprWormler = new CSprite(m_Loader, "Sprites/wormtiles.png", m_pMainCanvas, CPoint(0, 64),
                CRectangle(0, 0, 256, 64) );
        m_pSprWormler->SetColorAndAlpha(0xff00ff, 128);
        m_pSprMgr->AddSprite(m_pSprWormler, "mytag", hspriv::EyeMover(260, 40));

        //_CrtSetBreakAlloc(pimpl_->allocReqNum+4);
        //_crtBreakAlloc = pimpl_->allocReqNum+4;

        shost::ScriptHost shost;
        //shost.RunScript2(m_Loader.FL_LOADASSTRING("Lua/hello.lua"));
        // shost.RunScript(m_Loader.FL_LOADASSTRING("Lua/funcret.lua"));
        //shost.RunScript4(m_Loader.FL_LOADASSTRING("Lua/iowrite.lua"));
        //shost.RunScript(m_Loader.FL_LOADASSTRING("Lua/globalclass.lua"));
        //shost.RunScript6( m_Loader.FL_LOADASSTRING("Lua/globalclass.lua") );
		//shost.RunScript7( m_Loader.FL_LOADASSTRING("Lua/--FREE--.lua") );

		typedef shost::LuaScript<int, double, double> ScriptType;
		ScriptType::Script s = shost.generate<int, double, double>( m_Loader.FL_LOADASSTRING(
			"Lua/sprite1.lua"), "Ticks", "X", "Y" );
		pimpl_->script = s;

        world.FPS = CApplication::FramesCap();
        CRectangle screenRect = m_pMainCanvas->GetDimension();
        world.ScreenX = screenRect.GetW();
        world.ScreenY = screenRect.GetH();

		// Todo maybe an functor to initialize more global stuff
		(*s->AddStatic(world))("World")
			.def("greet", &greetHopper)
			.def_readonly("FPS", &World::FPS)
			.def_readonly("ScreenX", &World::ScreenX)
			.def_readonly("ScreenY", &World::ScreenY);



		ScriptType::Script sprInit = shost.generate<int, double, double>( m_Loader.FL_LOADASSTRING(
			"Sprites/male_sprites.spr"), "Ticks", "X", "Y" );
		//ScriptType::Script sprInit = shost.generate<int, double, double>( m_Loader.FL_LOADASSTRING(
		//	"Sprites/male_sprites.spr"), "Ticks", "X", "Y" );

		TestClass st(12,99);

		(*sprInit->AddStatic(st))("TestClass", "tc")
			.def(luabind::constructor<std::vector<int> >())
			.def(luabind::constructor<int, int>())
			.def("get", &TestClass::get);

		//boost::shared_ptr<shost::LuaScript::register_binder<SpriteFrame >>& bla=
		int xyz = 55;

		typedef shost::LuaVarCapsule<luabind::class_<SpriteFrame>> SprCapsule;
		SprCapsule maleSpriteCap = shost::makeFarm(sprInit,
		(*sprInit->Register<SpriteFrame>())("SpriteFrame")
			.def(luabind::constructor<int, int>())
			.def("X", &SpriteFrame::X)
			.def("Y", &SpriteFrame::Y));

		(*sprInit->Register<SpriteMovieOld>())("SpriteMovieOld")
			.def(luabind::constructor<std::string, SpriteFrame>())
			.def("X", &SpriteMovieOld::X)
			.def("Y", &SpriteMovieOld::Y);

		(*sprInit->Register<SpriteMovie>())("SpriteMovie")
			.def(luabind::constructor<std::string, std::vector<SpriteFrame>>())
			.def("X", &SpriteMovie::X)
			.def("Y", &SpriteMovie::Y);

		//luabind::class_<SpriteFrame>& xasd = maleSpriteCap.Value();
		//SprCapsule::ObjType mmy(1,2);
		//mmy.X();

		/*luabind::module(sprInit->L())
			[
				luabind::class_<TestClass>("TestClass_")
				.def(luabind::constructor<std::vector<int> >())
				.def(luabind::constructor<int, int>())
				.def("get", &TestClass::get)
			];*/


		int success = sprInit->run_script(99);

		luabind::object o3(luabind::globals(sprInit->L())["tcx"]);
		if (o3)
		{
			// is_valid
			// ...

			int luatype = luabind::type(o3);
			if (luabind::type(o3) == LUA_TUSERDATA)
			{
				TestClass otherValue = luabind::object_cast<TestClass>(o3);
				int abc = 4;
				abc++;
			}
		}

		SpriteFrame otherValue2(0,0);
		bool success3 = maleSpriteCap.GetLuaValue("spf", otherValue2);
		SpriteFrame otherValuex = maleSpriteCap.GetLuaValue("spf");

		SpriteFrame otherValue3(0,0);
		bool fsuccess = sprInit->GetLuaValue<SpriteFrame>("spf", otherValue3);

		luabind::object o4(luabind::globals(sprInit->L())["spf"]);
		if (o4)
		{
			// is_valid
			// ...

			int luatype = luabind::type(o4);
			if (luabind::type(o4) == LUA_TUSERDATA)
			{
				SpriteFrame otherValue = luabind::object_cast<SpriteFrame>(o4);
				int abc = 4;
				abc++;
			}
		}




		//SpriteMovie otherValue3(0,0);
		//fsuccess = sprInit->GetLuaValue<SpriteMovie>("spMovie", otherValue3);
		SpriteMovieOld smovieOld = sprInit->GetLuaValue<SpriteMovieOld>("spMovieOld");
		SpriteMovie smovie = sprInit->GetLuaValue<SpriteMovie>("spMovie");

		//int *x = new int(666);

        return Screen::OnInit(argc, argv);
    } // OnInit