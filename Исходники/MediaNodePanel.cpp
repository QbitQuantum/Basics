status_t MediaNodePanel::exportState(
	BMessage*									archive) const {

	BPoint iconPos, miniIconPos;
	
	MediaRoutingView* v = dynamic_cast<MediaRoutingView*>(view());
	ASSERT(v);
	MediaRoutingView::layout_t layoutMode = v->getLayout();
	switch(layoutMode) {
		case MediaRoutingView::M_ICON_VIEW:
			iconPos = Frame().LeftTop();
			miniIconPos = m_alternatePosition;
			break;

		case MediaRoutingView::M_MINI_ICON_VIEW:
			miniIconPos = Frame().LeftTop();
			iconPos = m_alternatePosition;
			break;
	}

	if(iconPos != s_invalidPosition)
		archive->AddPoint("iconPos", iconPos);
	if(miniIconPos != s_invalidPosition)
		archive->AddPoint("miniIconPos", miniIconPos);
		
	// determine if I'm a 'system' node
	port_info portInfo;
	app_info appInfo;

	if ((get_port_info(ref->node().port, &portInfo) == B_OK)
		&& (be_roster->GetRunningAppInfo(portInfo.team, &appInfo) == B_OK)) {
		BEntry appEntry(&appInfo.ref);
		char appName[B_FILE_NAME_LENGTH];
		if(
			appEntry.InitCheck() == B_OK &&
			appEntry.GetName(appName) == B_OK &&
			(!strcmp(appName, "media_addon_server") ||
			 !strcmp(appName, "audio_server"))) {
		
			archive->AddBool("sysOwned", true);	 
		}
	}
	
	return B_OK;	
}