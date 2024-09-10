/*
===============
idPlayerIcon::Draw
===============
*/
void idPlayerIcon::Draw( idPlayer *player, const idVec3 &origin ) {
	idPlayer *localPlayer = gameLocal.GetLocalPlayer();
	if( !localPlayer || !localPlayer->GetRenderView() ) {
		FreeIcon();
		return;
	}
	idMat3 axis = localPlayer->GetRenderView()->viewaxis;
	if( player->isLagged ) {
		// create the icon if necessary, or update if already created
		if( !CreateIcon( player, ICON_LAG, origin, axis ) ) {
			UpdateIcon( player, origin, axis );
		}
	} else if( player->isChatting ) {
		if( !CreateIcon( player, ICON_CHAT, origin, axis ) ) {
			UpdateIcon( player, origin, axis );
		}
	} else {
		FreeIcon();
	}
}