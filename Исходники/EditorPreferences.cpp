void CCustomPreferences::Save(CInifile* I)
{
    I->w_u32	("editor_prefs","device_flags",		psDeviceFlags.flags	);
    I->w_u32	("editor_prefs","sound_flags",		psSoundFlags.flags	);

    I->w_u32	("editor_prefs","tools_settings",	Tools->m_Settings.flags	);

    I->w_float	("editor_prefs","view_np",			view_np			);
    I->w_float	("editor_prefs","view_fp",			view_fp			);
    I->w_float	("editor_prefs","view_fov",			view_fov		);

    I->w_u32	("editor_prefs","fog_color",		fog_color		);
    I->w_float	("editor_prefs","fog_fogness",		fog_fogness		);

    I->w_float	("editor_prefs","cam_fly_speed",	cam_fly_speed	);
    I->w_float	("editor_prefs","cam_fly_alt",		cam_fly_alt		);
    I->w_float	("editor_prefs","cam_sens_rot",		cam_sens_rot	);
    I->w_float	("editor_prefs","cam_sens_move",	cam_sens_move	);

    I->w_float	("editor_prefs","tools_sens_rot",	tools_sens_rot	);
    I->w_float	("editor_prefs","tools_sens_move",	tools_sens_move	);
    I->w_float	("editor_prefs","tools_sens_scale",	tools_sens_scale);

    I->w_bool	("editor_prefs","bp_lim_depth",		bp_lim_depth	);
    I->w_bool	("editor_prefs","bp_lim_depth",		bp_cull			);
    I->w_float	("editor_prefs","bp_depth_tolerance",bp_depth_tolerance	);

    I->w_float	("editor_prefs","snap_angle",		snap_angle		);
    I->w_float	("editor_prefs","snap_move",		snap_move		);
    I->w_float	("editor_prefs","snap_moveto",		snap_moveto		);

    I->w_float	("editor_prefs","grid_cell_size",	grid_cell_size	);
    I->w_u32	("editor_prefs","grid_cell_count",	grid_cell_count	);

    I->w_u32	("editor_prefs","scene_undo_level",		scene_undo_level	);
    I->w_u32	("editor_prefs","scene_recent_count",	scene_recent_count	);
    I->w_u32	("editor_prefs","scene_clear_color",	scene_clear_color 	);

    I->w_u32	("editor_prefs","object_flags",		object_flags.flags);

    for (AStringIt it=scene_recent_list.begin(); it!=scene_recent_list.end(); it++){
    	AnsiString L; L.sprintf("recent_files_%d",it-scene_recent_list.begin());
    	AnsiString V; V.sprintf("\"%s\"",it->c_str());
		I->w_string("editor_prefs",L.c_str(),V.c_str());
    }
    I->w_string("editor_prefs","weather",   sWeather.c_str() );
    // load shortcuts
    SaveShortcuts		(I);
    UI->SaveSettings	(I);
}