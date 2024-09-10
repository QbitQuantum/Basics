// Add the weapon, and flash for the player's view
void CG_AddViewWeapon( playerState_t *ps ) {
	// no gun if in third person view or a camera is active
	if ( ps->persistant[PERS_TEAM] == TEAM_SPECTATOR || ps->pm_type == PM_INTERMISSION || cg.renderingThirdPerson ) {
		return;
	}

	const int weap = cg_fakeGun.integer ? cg_fakeGun.integer : ps->weapon;
	float desiredFov = 0.0f;
	if ( !cg.renderingThirdPerson
		&& (cg_trueGuns.integer || weap == WP_SABER || weap == WP_MELEE)
		&& cg_trueFOV.value
		&& cg.predictedPlayerState.pm_type != PM_SPECTATOR
		&& cg.predictedPlayerState.pm_type != PM_INTERMISSION )
	{
		desiredFov = cg_fovViewmodel.integer ? cg_fovViewmodel.value : cg_trueFOV.value;
	}
	else {
		desiredFov = cg_fovViewmodel.integer ? cg_fovViewmodel.value : cg_fov.value;
	}

	desiredFov = Q_clampi( 1, desiredFov, 180 );

	// allow the gun to be completely removed
	if ( !cg_fakeGun.integer && (!cg_drawGun.integer || cg.predictedPlayerState.zoomMode || cg_trueGuns.integer
		|| weap == WP_SABER || weap == WP_MELEE) ) {
		return;
	}

	// don't draw if testing a gun model
	if ( cg.testGun ) {
		return;
	}

	centity_t *cent = &cg_entities[cg.predictedPlayerState.clientNum];
	CG_RegisterWeapon( weap );

	refEntity_t hand;
	memset( &hand, 0, sizeof(hand) );

	// set up gun position
	vector3 angles;
	CG_CalculateWeaponPosition( &hand.origin, &angles );

	refdef_t *refdef = CG_GetRefdef();
	VectorMA( &hand.origin, cg.gunAlign.x, &refdef->viewaxis[0], &hand.origin );
	VectorMA( &hand.origin, cg.gunAlign.y, &refdef->viewaxis[1], &hand.origin );
	VectorMA( &hand.origin, cg.gunAlign.z, &refdef->viewaxis[2], &hand.origin );

	AnglesToAxis( &angles, hand.axis );

	if ( cg_fovViewmodel.integer ) {
		float fracDistFOV, fracWeapFOV;
		float fov = desiredFov;
		if ( cg_fovAspectAdjust.integer ) {
			// Based on LordHavoc's code for Darkplaces
			// http://www.quakeworld.nu/forum/topic/53/what-does-your-qw-look-like/page/30
			const float baseAspect = 0.75f; // 3/4
			const float aspect = (float)cgs.glconfig.vidWidth / (float)cgs.glconfig.vidHeight;

			fov = atanf( tanf( desiredFov*M_PI / 360.0f ) * baseAspect*aspect )*360.0f / M_PI;
		}
		fracDistFOV = tanf( refdef->fov_x * M_PI / 360.0f );
		fracWeapFOV = (1.0f / fracDistFOV) * tanf( fov * M_PI / 360.0f );
		VectorScale( &hand.axis[0], fracWeapFOV, &hand.axis[0] );
	}

	// map torso animations to weapon animations
	if ( cg_debugGunFrame.integer ) {
		// development tool
		hand.frame = hand.oldframe = cg_debugGunFrame.integer;
		hand.backlerp = 0;
	}
	else {
		float currentFrame;

		// get clientinfo for animation map
		clientInfo_t *ci = nullptr;
		if ( cent->currentState.eType == ET_NPC ) {
			if ( !cent->npcClient ) {
				return;
			}
			ci = cent->npcClient;
		}
		else {
			ci = &cgs.clientinfo[cent->currentState.clientNum];
		}

		// smoother first-person anims by eezstreet http://jkhub.org/topic/1499-/
		//		actually ported from SP
#if 1
		// Sil's fix
		trap->G2API_GetBoneFrame( cent->ghoul2, "lower_lumbar", cg.time, &currentFrame, cgs.gameModels, 0 );
		hand.frame = CG_MapTorsoToWeaponFrame( ci, ceilf( currentFrame ), cent->currentState.torsoAnim );
		hand.oldframe = CG_MapTorsoToWeaponFrame( ci, floorf( currentFrame ), cent->currentState.torsoAnim );
		hand.backlerp = 1.0f - (currentFrame - floorf( currentFrame ));
#else
		// basejka style
		hand.frame = CG_MapTorsoToWeaponFrame( ci, cent->pe.torso.frame, cent->currentState.torsoAnim );
		hand.oldframe = CG_MapTorsoToWeaponFrame( ci, cent->pe.torso.oldFrame, cent->currentState.torsoAnim );
		hand.backlerp = cent->pe.torso.backlerp;
#endif

		// Handle the fringe situation where oldframe is invalid
		if ( hand.frame == -1 ) {
			hand.frame = 0;
			hand.oldframe = 0;
			hand.backlerp = 0;
		}
		else if ( hand.oldframe == -1 ) {
			hand.oldframe = hand.frame;
			hand.backlerp = 0;
		}
	}

	weaponInfo_t *wi = &cg_weapons[weap];
	hand.hModel = wi->handsModel;
	hand.renderfx = RF_DEPTHHACK | RF_FIRST_PERSON;

	// add everything onto the hand
	CG_AddPlayerWeapon( &hand, ps, &cg_entities[cg.predictedPlayerState.clientNum], ps->persistant[PERS_TEAM], &angles, qfalse );
}