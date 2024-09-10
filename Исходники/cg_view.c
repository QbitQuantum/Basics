/*
==============
CG_DrawSkyBoxPortal
==============
*/
void CG_DrawSkyBoxPortal( void ) {
	static float lastfov = 90;      // for transitions back from zoomed in modes
	refdef_t backuprefdef;
	float fov_x;
	float fov_y;
	float x;
	char *cstr;
	char *token;
	float zoomFov;
	float f;
	static qboolean foginited = qfalse; // only set the portal fog values once

	if ( !( cstr = (char *)CG_ConfigString( CS_SKYBOXORG ) ) || !strlen( cstr ) ) {
		// no skybox in this map
		return;
	}

	// if they are waiting at the mission stats screen, show the stats
	if ( cg_gameType.integer == GT_SINGLE_PLAYER ) {
		if ( strlen( cg_missionStats.string ) > 1 ) {
			return;
		}
	}

	backuprefdef = cg.refdef;

	if ( cg_skybox.integer ) {
		token = COM_ParseExt( &cstr, qfalse );
		if ( !token || !token[0] ) {
			CG_Error( "CG_DrawSkyBoxPortal: error parsing skybox configstring\n" );
		}
		cg.refdef.vieworg[0] = atof( token );

		token = COM_ParseExt( &cstr, qfalse );
		if ( !token || !token[0] ) {
			CG_Error( "CG_DrawSkyBoxPortal: error parsing skybox configstring\n" );
		}
		cg.refdef.vieworg[1] = atof( token );

		token = COM_ParseExt( &cstr, qfalse );
		if ( !token || !token[0] ) {
			CG_Error( "CG_DrawSkyBoxPortal: error parsing skybox configstring\n" );
		}
		cg.refdef.vieworg[2] = atof( token );

		token = COM_ParseExt( &cstr, qfalse );
		if ( !token || !token[0] ) {
			CG_Error( "CG_DrawSkyBoxPortal: error parsing skybox configstring\n" );
		}
		fov_x = atoi( token );

		if ( !fov_x ) {
			fov_x = 90;
		}


		// setup fog the first time, ignore this part of the configstring after that
		token = COM_ParseExt( &cstr, qfalse );
		if ( !token || !token[0] ) {
			CG_Error( "CG_DrawSkyBoxPortal: error parsing skybox configstring.  No fog state\n" );
		} else {
			vec4_t fogColor;
			int fogStart, fogEnd;

			if ( atoi( token ) ) {   // this camera has fog
				//			if(!foginited) {
				if ( 1 ) {
					token = COM_ParseExt( &cstr, qfalse );
					if ( !token || !token[0] ) {
						CG_Error( "CG_DrawSkyBoxPortal: error parsing skybox configstring.  No fog[0]\n" );
					}
					fogColor[0] = atof( token );

					token = COM_ParseExt( &cstr, qfalse );
					if ( !token || !token[0] ) {
						CG_Error( "CG_DrawSkyBoxPortal: error parsing skybox configstring.  No fog[1]\n" );
					}
					fogColor[1] = atof( token );

					token = COM_ParseExt( &cstr, qfalse );
					if ( !token || !token[0] ) {
						CG_Error( "CG_DrawSkyBoxPortal: error parsing skybox configstring.  No fog[2]\n" );
					}
					fogColor[2] = atof( token );

					token = COM_ParseExt( &cstr, qfalse );
					if ( !token || !token[0] ) {
						fogStart = 0;
					} else {
						fogStart = atoi( token );
					}

					token = COM_ParseExt( &cstr, qfalse );
					if ( !token || !token[0] ) {
						fogEnd = 0;
					} else {
						fogEnd = atoi( token );
					}

					trap_R_SetFog( FOG_PORTALVIEW, fogStart, fogEnd, fogColor[0], fogColor[1], fogColor[2], 1.1 );
					foginited = qtrue;
				}
			} else {
				if ( !foginited ) {
					trap_R_SetFog( FOG_PORTALVIEW, 0,0,0,0,0,0 ); // init to null
					foginited = qtrue;
				}
			}
		}

		//----(SA)	end


		if ( cg.predictedPlayerState.pm_type == PM_INTERMISSION ) {
			// if in intermission, use a fixed value
			fov_x = 90;
		} else {
			// user selectable
			if ( cgs.dmflags & DF_FIXED_FOV ) {
				// dmflag to prevent wide fov for all clients
				fov_x = 90;
			} else {
				fov_x = cg_fov.value;
				if ( fov_x < 1 ) {
					fov_x = 1;
				} else if ( fov_x > 160 ) {
					fov_x = 160;
				}
			}

			// account for zooms
			if ( cg.zoomval ) {
				zoomFov = cg.zoomval;   // (SA) use user scrolled amount

				if ( zoomFov < 1 ) {
					zoomFov = 1;
				} else if ( zoomFov > 160 ) {
					zoomFov = 160;
				}
			} else {
				zoomFov = lastfov;
			}

			// do smooth transitions for the binocs
			if ( cg.zoomedBinoc ) {        // binoc zooming in
				f = ( cg.time - cg.zoomTime ) / (float)ZOOM_TIME;
				if ( f > 1.0 ) {
					fov_x = zoomFov;
				} else {
					fov_x = fov_x + f * ( zoomFov - fov_x );
				}
				lastfov = fov_x;
			} else if ( cg.zoomval ) {    // zoomed by sniper/snooper
				fov_x = cg.zoomval;
				lastfov = fov_x;
			} else {                    // binoc zooming out
				f = ( cg.time - cg.zoomTime ) / (float)ZOOM_TIME;
				if ( f > 1.0 ) {
					fov_x = fov_x;
				} else {
					fov_x = zoomFov + f * ( fov_x - zoomFov );
				}
			}
		}

		if ( cg.weaponSelect == WP_SNOOPERSCOPE ) {
			cg.refdef.rdflags |= RDF_SNOOPERVIEW;
		} else {
			cg.refdef.rdflags &= ~RDF_SNOOPERVIEW;
		}

		if ( cg.snap->ps.persistant[PERS_HWEAPON_USE] ) {
			fov_x = 55;
		}

		x = cg.refdef.width / tan( fov_x / 360 * M_PI );
		fov_y = atan2( cg.refdef.height, x );
		fov_y = fov_y * 360 / M_PI;

		cg.refdef.fov_x = fov_x;
		cg.refdef.fov_y = fov_y;

		cg.refdef.rdflags |= RDF_SKYBOXPORTAL;
		cg.refdef.rdflags |= RDF_DRAWSKYBOX;

	} else {    // end if(cg_skybox.integer)

		cg.refdef.rdflags |= RDF_SKYBOXPORTAL;
		cg.refdef.rdflags &= ~RDF_DRAWSKYBOX;
	}


	cg.refdef.time = cg.time;

	// draw the skybox
	trap_R_RenderScene( &cg.refdef );

	cg.refdef = backuprefdef;
}