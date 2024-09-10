UIMainWindow::UIMainWindow (IFrontend *frontend) :
		UIWindow(UI_WINDOW_MAIN, frontend, WINDOW_FLAG_ROOT)
{
	add(new UINodeMainBackground(frontend, false));
	const float padding = 10.0f / static_cast<float>(_frontend->getHeight());
	UINode *panel = new UINode(_frontend, "panelMain");
	UIVBoxLayout *layout = new UIVBoxLayout(padding, true);
	panel->setLayout(layout);
	panel->setAlignment(NODE_ALIGN_MIDDLE | NODE_ALIGN_CENTER);
	panel->setPadding(padding);

	UINodeMainButton *campaign = new UINodeMainButton(_frontend, tr("Start"));
	campaign->addListener(UINodeListenerPtr(new OpenWindowListener(UI_WINDOW_CAMPAIGN)));
	panel->add(campaign);

#ifndef NONETWORK
	if (Config.isNetwork()) {
		UINodeMainButton *multiplayer = new UINodeMainButton(_frontend, tr("Multiplayer"));
		multiplayer->addListener(UINodeListenerPtr(new OpenWindowListener(UI_WINDOW_MULTIPLAYER)));
		panel->add(multiplayer);
	}
#endif

	UINodeMainButton *settings = new UINodeMainButton(_frontend, tr("Settings"));
	settings->addListener(UINodeListenerPtr(new OpenWindowListener(UI_WINDOW_SETTINGS)));
	panel->add(settings);

#if 0
	UINodeMainButton *gesture = new UINodeMainButton(_frontend, tr("Gesture"));
	gesture->addListener(UINodeListenerPtr(new OpenWindowListener("gesture")));
	panel->add(gesture);
#endif

	if (System.supportPayment()) {
		UINodeMainButton *payment = new UINodeMainButton(_frontend, tr("Extras"));
		payment->addListener(UINodeListenerPtr(new OpenWindowListener(UI_WINDOW_PAYMENT)));
		panel->add(payment);
	}

	if (System.supportGooglePlay()) {
		UINodeButtonImage *googlePlay = new UINodeGooglePlayButton(_frontend);
		googlePlay->setPadding(padding);
		add(googlePlay);
	}

	UINodeMainButton *twitter = new UINodeMainButton(_frontend, tr("Twitter"));
	twitter->addListener(UINodeListenerPtr(new OpenURLListener(_frontend, "https://twitter.com/MartinGerhardy")));
	panel->add(twitter);

	UINodeMainButton *homepage = new UINodeMainButton(_frontend, tr("Homepage"));
	homepage->addListener(UINodeListenerPtr(new OpenURLListener(_frontend, "http://caveproductions.org/")));
	panel->add(homepage);

#if 0
#ifdef __EMSCRIPTEN__
	UINodeMainButton *fullscreen = new UINodeMainButton(_frontend, tr("Fullscreen"));
	fullscreen->addListener(UINodeListenerPtr(new EmscriptenFullscreenListener()));
	panel->add(fullscreen);
#endif
#endif

	UINodeMainButton *quit = new UINodeMainButton(_frontend, tr("Quit"));
#ifdef __EMSCRIPTEN__
	quit->addListener(UINodeListenerPtr(new OpenURLListener(_frontend, "http://caveproductions.org/", false)));
#else
	quit->addListener(UINodeListenerPtr(new QuitListener()));
#endif
	panel->add(quit);

	add(panel);
}