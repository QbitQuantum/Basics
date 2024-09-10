/*
=================
UI_PlayerSetup_Init
=================
*/
static void UI_PlayerSetup_Init( void )
{
	bool game_hlRally = FALSE;
	int addFlags = 0;

	memset( &uiPlayerSetup, 0, sizeof( uiPlayerSetup_t ));

	// disable playermodel preview for HLRally to prevent crash
	if( !stricmp( gMenu.m_gameinfo.gamefolder, "hlrally" ))
		game_hlRally = TRUE;

	//if( gMenu.m_gameinfo.flags & GFL_NOMODELS )
	//	addFlags |= QMF_INACTIVE;

	uiPlayerSetup.menu.vidInitFunc = UI_PlayerSetup_Init;

	uiPlayerSetup.background.generic.id = ID_BACKGROUND;
	uiPlayerSetup.background.generic.type = QMTYPE_BITMAP;
	uiPlayerSetup.background.generic.flags = QMF_INACTIVE;
	uiPlayerSetup.background.generic.x = 0;
	uiPlayerSetup.background.generic.y = 0;
	uiPlayerSetup.background.generic.width = uiStatic.width;
	uiPlayerSetup.background.generic.height = 768;
	uiPlayerSetup.background.pic = ART_BACKGROUND;

	uiPlayerSetup.banner.generic.id = ID_BANNER;
	uiPlayerSetup.banner.generic.type = QMTYPE_BITMAP;
	uiPlayerSetup.banner.generic.flags = QMF_INACTIVE|QMF_DRAW_ADDITIVE;
	uiPlayerSetup.banner.generic.x = UI_BANNER_POSX;
	uiPlayerSetup.banner.generic.y = UI_BANNER_POSY;
	uiPlayerSetup.banner.generic.width = UI_BANNER_WIDTH;
	uiPlayerSetup.banner.generic.height = UI_BANNER_HEIGHT;
	uiPlayerSetup.banner.pic = ART_BANNER;

	uiPlayerSetup.done.generic.id = ID_DONE;
	uiPlayerSetup.done.generic.type = QMTYPE_BM_BUTTON;
	uiPlayerSetup.done.generic.flags = QMF_HIGHLIGHTIFFOCUS|QMF_DROPSHADOW;
	uiPlayerSetup.done.generic.x = 72;
	uiPlayerSetup.done.generic.y = 230;
	uiPlayerSetup.done.generic.name = "Done";
	uiPlayerSetup.done.generic.statusText = "Go back to the Multiplayer Menu";
	uiPlayerSetup.done.generic.callback = UI_PlayerSetup_Callback;

	UI_UtilSetupPicButton( &uiPlayerSetup.done, PC_DONE );

	uiPlayerSetup.AdvOptions.generic.id = ID_ADVOPTIONS;
	uiPlayerSetup.AdvOptions.generic.type = QMTYPE_BM_BUTTON;
	uiPlayerSetup.AdvOptions.generic.flags = QMF_HIGHLIGHTIFFOCUS|QMF_DROPSHADOW;
	uiPlayerSetup.AdvOptions.generic.x = 72;
	uiPlayerSetup.AdvOptions.generic.y = 280;
	uiPlayerSetup.AdvOptions.generic.name = "Adv. Options";
	uiPlayerSetup.AdvOptions.generic.statusText = "Configure handness, fov and other advanced options";
	uiPlayerSetup.AdvOptions.generic.callback = UI_PlayerSetup_Callback;

	UI_UtilSetupPicButton( &uiPlayerSetup.AdvOptions, PC_ADV_OPT );

	uiPlayerSetup.view.generic.id = ID_VIEW;
	uiPlayerSetup.view.generic.type = QMTYPE_BITMAP;
	uiPlayerSetup.view.generic.flags = QMF_INACTIVE;
	uiPlayerSetup.view.generic.x = 660;
	uiPlayerSetup.view.generic.y = 260;
	uiPlayerSetup.view.generic.width = 260;
	uiPlayerSetup.view.generic.height = 320;
	uiPlayerSetup.view.generic.ownerdraw = UI_PlayerSetup_Ownerdraw;

	uiPlayerSetup.name.generic.id = ID_NAME;
	uiPlayerSetup.name.generic.type = QMTYPE_FIELD;
	uiPlayerSetup.name.generic.flags = QMF_CENTER_JUSTIFY|QMF_HIGHLIGHTIFFOCUS|QMF_DROPSHADOW;
	uiPlayerSetup.name.generic.x = 320;
	uiPlayerSetup.name.generic.y = 260;
	uiPlayerSetup.name.generic.width = 256;
	uiPlayerSetup.name.generic.height = 36;
	uiPlayerSetup.name.generic.callback = UI_PlayerSetup_Callback;
	uiPlayerSetup.name.generic.statusText = "Enter your multiplayer display name";
	uiPlayerSetup.name.maxLength = 32;

	uiPlayerSetup.model.generic.id = ID_MODEL;
	uiPlayerSetup.model.generic.type = QMTYPE_SPINCONTROL;
	uiPlayerSetup.model.generic.flags = QMF_CENTER_JUSTIFY|QMF_HIGHLIGHTIFFOCUS|QMF_DROPSHADOW|addFlags;
	uiPlayerSetup.model.generic.x = game_hlRally ? 320 : 702;
	uiPlayerSetup.model.generic.y = game_hlRally ? 320 : 590;
	uiPlayerSetup.model.generic.width = game_hlRally ? 256 : 176;
	uiPlayerSetup.model.generic.height = game_hlRally ? 36 : 32;
	uiPlayerSetup.model.generic.callback = UI_PlayerSetup_Callback;
	uiPlayerSetup.model.generic.statusText = "Select a model for representation in multiplayer";
	uiPlayerSetup.model.minValue = 0;
	uiPlayerSetup.model.maxValue = 1;
	uiPlayerSetup.model.range  = 1;

	uiPlayerSetup.topColor.generic.id = ID_TOPCOLOR;
	uiPlayerSetup.topColor.generic.type = QMTYPE_SLIDER;
	uiPlayerSetup.topColor.generic.flags = QMF_PULSEIFFOCUS|QMF_DROPSHADOW|addFlags;
	uiPlayerSetup.topColor.generic.name = "Top color";
	uiPlayerSetup.topColor.generic.x = 250;
	uiPlayerSetup.topColor.generic.y = 550;
	uiPlayerSetup.topColor.generic.width = 300;
	uiPlayerSetup.topColor.generic.callback = UI_PlayerSetup_Callback;
	uiPlayerSetup.topColor.generic.statusText = "Set a player model top color";
	uiPlayerSetup.topColor.minValue = 0.0;
	uiPlayerSetup.topColor.maxValue = 1.0;
	uiPlayerSetup.topColor.range = 0.05f;

	uiPlayerSetup.bottomColor.generic.id = ID_BOTTOMCOLOR;
	uiPlayerSetup.bottomColor.generic.type = QMTYPE_SLIDER;
	uiPlayerSetup.bottomColor.generic.flags = QMF_PULSEIFFOCUS|QMF_DROPSHADOW|addFlags;
	uiPlayerSetup.bottomColor.generic.name = "Bottom color";
	uiPlayerSetup.bottomColor.generic.x = 250;
	uiPlayerSetup.bottomColor.generic.y = 620;
	uiPlayerSetup.bottomColor.generic.width = 300;
	uiPlayerSetup.bottomColor.generic.callback = UI_PlayerSetup_Callback;
	uiPlayerSetup.bottomColor.generic.statusText = "Set a player model bottom color";
	uiPlayerSetup.bottomColor.minValue = 0.0;
	uiPlayerSetup.bottomColor.maxValue = 1.0;
	uiPlayerSetup.bottomColor.range = 0.05f;

	uiPlayerSetup.showModels.generic.id = ID_SHOWMODELS;
	uiPlayerSetup.showModels.generic.type = QMTYPE_CHECKBOX;
	uiPlayerSetup.showModels.generic.flags = QMF_HIGHLIGHTIFFOCUS|QMF_ACT_ONRELEASE|QMF_MOUSEONLY|QMF_DROPSHADOW|addFlags;
	uiPlayerSetup.showModels.generic.name = "Show 3D Preview";
	uiPlayerSetup.showModels.generic.x = 72;
	uiPlayerSetup.showModels.generic.y = 380;
	uiPlayerSetup.showModels.generic.callback = UI_PlayerSetup_Callback;
	uiPlayerSetup.showModels.generic.statusText = "show 3D player models instead of preview thumbnails";

	uiPlayerSetup.hiModels.generic.id = ID_HIMODELS;
	uiPlayerSetup.hiModels.generic.type = QMTYPE_CHECKBOX;
	uiPlayerSetup.hiModels.generic.flags = QMF_HIGHLIGHTIFFOCUS|QMF_ACT_ONRELEASE|QMF_MOUSEONLY|QMF_DROPSHADOW|addFlags;
	uiPlayerSetup.hiModels.generic.name = "High quality models";
	uiPlayerSetup.hiModels.generic.x = 72;
	uiPlayerSetup.hiModels.generic.y = 430;
	uiPlayerSetup.hiModels.generic.callback = UI_PlayerSetup_Callback;
	uiPlayerSetup.hiModels.generic.statusText = "show hi-res models in multiplayer";

	UI_PlayerSetup_GetConfig();

	UI_AddItem( &uiPlayerSetup.menu, (void *)&uiPlayerSetup.background );
	UI_AddItem( &uiPlayerSetup.menu, (void *)&uiPlayerSetup.banner );
	UI_AddItem( &uiPlayerSetup.menu, (void *)&uiPlayerSetup.done );
	UI_AddItem( &uiPlayerSetup.menu, (void *)&uiPlayerSetup.AdvOptions );
	// disable playermodel preview for HLRally to prevent crash
	if( game_hlRally == FALSE )
		UI_AddItem( &uiPlayerSetup.menu, (void *)&uiPlayerSetup.view );
	UI_AddItem( &uiPlayerSetup.menu, (void *)&uiPlayerSetup.name );

	//if( !gMenu.m_gameinfo.flags & GFL_NOMODELS )
	//{
		UI_AddItem( &uiPlayerSetup.menu, (void *)&uiPlayerSetup.model );
		UI_AddItem( &uiPlayerSetup.menu, (void *)&uiPlayerSetup.topColor );
		UI_AddItem( &uiPlayerSetup.menu, (void *)&uiPlayerSetup.bottomColor );
		UI_AddItem( &uiPlayerSetup.menu, (void *)&uiPlayerSetup.showModels );
		UI_AddItem( &uiPlayerSetup.menu, (void *)&uiPlayerSetup.hiModels );
	//}
	// setup render and actor
	uiPlayerSetup.refdef.fov_x = 40;

	// NOTE: must be called after UI_AddItem whan we sure what UI_ScaleCoords is done
	uiPlayerSetup.refdef.viewport[0] = uiPlayerSetup.view.generic.x;
	uiPlayerSetup.refdef.viewport[1] = uiPlayerSetup.view.generic.y;
	uiPlayerSetup.refdef.viewport[2] = uiPlayerSetup.view.generic.width;
	uiPlayerSetup.refdef.viewport[3] = uiPlayerSetup.view.generic.height;

	UI_PlayerSetup_CalcFov( &uiPlayerSetup.refdef );
	uiPlayerSetup.ent = GET_MENU_EDICT ();

	if( !uiPlayerSetup.ent )
		return;

	// adjust entity params
	uiPlayerSetup.ent->curstate.number = 1;	// IMPORTANT: always set playerindex to 1
	uiPlayerSetup.ent->curstate.animtime = gpGlobals->time;	// start animation
	uiPlayerSetup.ent->curstate.sequence = 1;
	uiPlayerSetup.ent->curstate.scale = 1.0f;
	uiPlayerSetup.ent->curstate.frame = 0.0f;
	uiPlayerSetup.ent->curstate.framerate = 1.0f;
	uiPlayerSetup.ent->curstate.effects |= EF_LIGHT;
	uiPlayerSetup.ent->curstate.controller[0] = 127;
	uiPlayerSetup.ent->curstate.controller[1] = 127;
	uiPlayerSetup.ent->curstate.controller[2] = 127;
	uiPlayerSetup.ent->curstate.controller[3] = 127;
	uiPlayerSetup.ent->latched.prevcontroller[0] = 127;
	uiPlayerSetup.ent->latched.prevcontroller[1] = 127;
	uiPlayerSetup.ent->latched.prevcontroller[2] = 127;
	uiPlayerSetup.ent->latched.prevcontroller[3] = 127;
	uiPlayerSetup.ent->origin[0] = uiPlayerSetup.ent->curstate.origin[0] = 45.0f / tan( DEG2RAD( uiPlayerSetup.refdef.fov_y / 2.0f ));
	uiPlayerSetup.ent->origin[2] = uiPlayerSetup.ent->curstate.origin[2] = 2.0f;
	uiPlayerSetup.ent->angles[1] = uiPlayerSetup.ent->curstate.angles[1] = 180.0f;
	uiPlayerSetup.ent->player = true; // yes, draw me as playermodel
}