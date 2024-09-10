void MenuScreen::render() {
	UIShader_Prepare();
	UIBegin(UIShader_Get());
	DrawBackground(1.0f);

	double xoff = 150 - frames_ * frames_ * 0.4f;
	if (xoff < -20)
		xoff = -20;
	if (frames_ > 200)  // seems the above goes nuts after a while...
		xoff = -20;

	int w = LARGE_BUTTON_WIDTH + 60;

	ui_draw2d.DrawTextShadow(UBUNTU48, "PPSSPP", dp_xres + xoff - w/2, 75, 0xFFFFFFFF, ALIGN_HCENTER | ALIGN_BOTTOM);
	ui_draw2d.SetFontScale(0.7f, 0.7f);
	ui_draw2d.DrawTextShadow(UBUNTU24, PPSSPP_GIT_VERSION, dp_xres + xoff, 85, 0xFFFFFFFF, ALIGN_RIGHT | ALIGN_BOTTOM);
	ui_draw2d.SetFontScale(1.0f, 1.0f);
	VLinear vlinear(dp_xres + xoff, 100, 20);

	I18NCategory *m = GetI18NCategory("MainMenu");

	if (UIButton(GEN_ID, vlinear, w, 0, m->T("Load", "Load..."), ALIGN_RIGHT)) {
#if defined(USING_QT_UI) && !defined(MEEGO_EDITION_HARMATTAN)
		QString fileName = QFileDialog::getOpenFileName(NULL, "Load ROM", g_Config.currentDirectory.c_str(), "PSP ROMs (*.iso *.cso *.pbp *.elf)");
		if (QFile::exists(fileName)) {
			QDir newPath;
			g_Config.currentDirectory = newPath.filePath(fileName).toStdString();
			g_Config.Save();
			screenManager()->switchScreen(new EmuScreen(fileName.toStdString()));
		}
#elif _WIN32
		MainWindow::BrowseAndBoot("");
#else
		FileSelectScreenOptions options;
		options.allowChooseDirectory = true;
		options.filter = "iso:cso:pbp:elf:prx:";
		options.folderIcon = I_ICON_FOLDER;
		options.iconMapping["iso"] = I_ICON_UMD;
		options.iconMapping["cso"] = I_ICON_UMD;
		options.iconMapping["pbp"] = I_ICON_EXE;
		options.iconMapping["elf"] = I_ICON_EXE;
		screenManager()->switchScreen(new FileSelectScreen(options));
#endif
		UIReset();
	}

	if (UIButton(GEN_ID, vlinear, w, 0, m->T("Settings"), ALIGN_RIGHT)) {
		screenManager()->push(new SettingsScreen(), 0);
		UIReset();
	}

	if (UIButton(GEN_ID, vlinear, w, 0, m->T("Credits"), ALIGN_RIGHT)) {
		screenManager()->switchScreen(new CreditsScreen());
		UIReset();
	}

	if (UIButton(GEN_ID, vlinear, w, 0, m->T("Exit"), ALIGN_RIGHT)) {
		// TODO: Save when setting changes, rather than when we quit
		NativeShutdown();
		// TODO: Need a more elegant way to quit
#ifdef _WIN32
		ExitProcess(0);
#else
		exit(0);
#endif
	}

	if (UIButton(GEN_ID, vlinear, w, 0, "www.ppsspp.org", ALIGN_RIGHT)) {
		LaunchBrowser("http://www.ppsspp.org/");
	}

	int recentW = 350;
	if (g_Config.recentIsos.size()) {
		ui_draw2d.DrawText(UBUNTU24, m->T("Recent"), -xoff, 80, 0xFFFFFFFF, ALIGN_BOTTOMLEFT);
	}

	int spacing = 15;

	float textureButtonWidth = 144;
	float textureButtonHeight = 80;

	if (dp_yres < 480)
		spacing = 8;
	// On small screens, we can't fit four vertically.
	if (100 + spacing * 6 + textureButtonHeight * 4 > dp_yres) {
		textureButtonHeight = (dp_yres - 100 - spacing * 6) / 4;
		textureButtonWidth = (textureButtonHeight / 80) * 144;
	}

	VGrid vgrid_recent(-xoff, 100, std::min(dp_yres-spacing*2, 480), spacing, spacing);

	for (size_t i = 0; i < g_Config.recentIsos.size(); i++) {
		std::string filename;
		std::string rec = g_Config.recentIsos[i];
		for (size_t j = 0; j < rec.size(); j++)
			if (rec[j] == '\\') rec[j] = '/';
		SplitPath(rec, nullptr, &filename, nullptr);

		UIContext *ctx = screenManager()->getUIContext();
		// This might create a texture so we must flush first.
		UIFlush();
		GameInfo *ginfo = g_gameInfoCache.GetInfo(g_Config.recentIsos[i], false);
		if (ginfo && ginfo->fileType != FILETYPE_PSP_ELF) {
			u32 color;
			if (ginfo->iconTexture == 0) {
				color = 0;
			} else {
				color = whiteAlpha(ease((time_now_d() - ginfo->timeIconWasLoaded) * 2));
			}
			if (UITextureButton(ctx, (int)GEN_ID_LOOP(i), vgrid_recent, textureButtonWidth, textureButtonHeight, ginfo->iconTexture, ALIGN_LEFT, color, I_DROP_SHADOW)) {
				UIEnd();
				screenManager()->switchScreen(new EmuScreen(g_Config.recentIsos[i]));
				return;
			}
		} else {
			if (UIButton((int)GEN_ID_LOOP(i), vgrid_recent, textureButtonWidth, textureButtonHeight, filename.c_str(), ALIGN_LEFT)) {
				UIEnd();
				screenManager()->switchScreen(new EmuScreen(g_Config.recentIsos[i]));
				return;
			}
		}
	}

#if defined(_DEBUG) & defined(_WIN32)
	// Print the current dp_xres/yres in the corner. For UI scaling testing - just
	// resize to 800x480 to get an idea of what it will look like on a Nexus S.
	ui_draw2d.SetFontScale(0.4, 0.4);
	char temptext[64];
	sprintf(temptext, "%ix%i", dp_xres, dp_yres);
	ui_draw2d.DrawTextShadow(UBUNTU24, temptext, 5, dp_yres-5, 0xFFFFFFFF, ALIGN_BOTTOMLEFT);
	ui_draw2d.SetFontScale(1.0, 1.0);
#endif

	DrawWatermark();

	UIEnd();
}