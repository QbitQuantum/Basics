void radar_plot_object_std( object *objp )	
{
	vec3d	pos, tempv;
	float		dist, rscale, zdist, max_radar_dist;
	int		xpos, ypos;
	vec3d	*world_pos = &objp->pos;	
	float		awacs_level;

	// don't process anything here.  Somehow, a jumpnode object caused this function
	// to get entered on server side.
	if( Game_mode & GM_STANDALONE_SERVER ){
		return;
	}

	// multiplayer clients ingame joining should skip this function
	if ( MULTIPLAYER_CLIENT && (Net_player->flags & NETINFO_FLAG_INGAME_JOIN) ){
		return;
	}

	// get team-wide awacs level for the object if not ship
	int ship_is_visible = 0;
	if (objp->type == OBJ_SHIP) {
		if (Player_ship != NULL) {
			if (ship_is_visible_by_team(objp, Player_ship)) {
				ship_is_visible = 1;
			}
		}
	}

	// only check awacs level if ship is not visible by team
	awacs_level = 1.5f;
	if (Player_ship != NULL && !ship_is_visible) {
		awacs_level = awacs_get_level(objp, Player_ship);
	}

	// if the awacs level is unviewable - bail
	if(awacs_level < 0.0f && !See_all){
		return;
	}

	// Apply object type filters	
	switch (objp->type)
	{
		case OBJ_SHIP:
			// Place to cull ships, such as NavBuoys		
			break;
		
		case OBJ_JUMP_NODE:
		{
			// don't plot hidden jump nodes
			if ( objp->jnp->is_hidden() )
				return;

			// filter jump nodes here if required
			break;
		}

		case OBJ_WEAPON:
		{
			// if not a bomb, return
			if ( !(Weapon_info[Weapons[objp->instance].weapon_info_index].wi_flags & WIF_BOMB) )
				return;

			// if we don't attack the bomb, return
			if ( !iff_x_attacks_y(Player_ship->team, obj_team(objp)) )
				return;

			// if a local ssm is in subspace, return
			if (Weapons[objp->instance].lssm_stage == 3)
				return;

			break;
		}

		// if any other kind of object, don't show it on radar
		default:
			return;
	}

	
	// JAS -- new way of getting the rotated point that doesn't require this to be
	// in a g3_start_frame/end_frame block.
	vm_vec_sub(&tempv, world_pos, &Player_obj->pos);
	vm_vec_rotate(&pos, &tempv, &Player_obj->orient);

	// Apply range filter
	dist = vm_vec_dist(world_pos, &Player_obj->pos);
	max_radar_dist = Radar_ranges[HUD_config.rp_dist];
	if (dist > max_radar_dist) {
		return;
	}

	if (dist < pos.xyz.z) {
		rscale = 0.0f;
	} else {
		rscale = (float) acos(pos.xyz.z / dist) / 3.14159f;		//2.0f;	 
	}

	zdist = fl_sqrt((pos.xyz.x * pos.xyz.x) + (pos.xyz.y * pos.xyz.y));

	float new_x_dist, clipped_x_dist;
	float new_y_dist, clipped_y_dist;

	if (zdist < 0.01f)
	{
		new_x_dist = 0.0f;
		new_y_dist = 0.0f;
	}
	else
	{
		new_x_dist = (pos.xyz.x / zdist) * rscale * radx;
		new_y_dist = (pos.xyz.y / zdist) * rscale * rady;

		// force new_x_dist and new_y_dist to be inside the radar

		float hypotenuse;
		float max_radius;

		hypotenuse = (float) _hypot(new_x_dist, new_y_dist);
		max_radius = i2fl(Current_radar_global->Radar_radius[gr_screen.res][0] - 5);

		if (hypotenuse >= max_radius)
		{
			clipped_x_dist = max_radius * (new_x_dist / hypotenuse);
			clipped_y_dist = max_radius * (new_y_dist / hypotenuse);
			new_x_dist = clipped_x_dist;
			new_y_dist = clipped_y_dist;
		}
	}

	xpos = fl2i(Current_radar_global->Radar_center[gr_screen.res][0] + new_x_dist);
	ypos = fl2i(Current_radar_global->Radar_center[gr_screen.res][1] - new_y_dist);


	// determine the range within which the radar blip is bright
	if (timestamp_elapsed(Radar_calc_bright_dist_timer))
	{
		Radar_calc_bright_dist_timer = timestamp(1000);
		Radar_bright_range = player_farthest_weapon_range();
		if (Radar_bright_range <= 0)
			Radar_bright_range = 1500.0f;
	}

	blip *b;
	int blip_bright = 0;
	int blip_type = 0;

	if (N_blips >= MAX_BLIPS)
	{
		// out of blips, don't plot
		//Gahhh, this is bloody annoying -WMC
		//Int3();
		return;
	}

	b = &Blips[N_blips];
	b->flags = 0;

	// bright if within range
	blip_bright = (dist <= Radar_bright_range);

	// flag the blip as a current target if it is
	if (OBJ_INDEX(objp) == Player_ai->target_objnum)
	{
		b->flags |= BLIP_CURRENT_TARGET;
		blip_bright = 1;
	}

	radar_stuff_blip_info_std(objp, blip_bright, &b->blip_color, &blip_type);

	if (blip_bright)
		list_append(&Blip_bright_list[blip_type], b);
	else
		list_append(&Blip_dim_list[blip_type], b);

	b->x = xpos;
	b->y = ypos;

	// see if blip should be drawn distorted
	if (objp->type == OBJ_SHIP)
	{
		// ships specifically hidden from sensors
		if (Ships[objp->instance].flags & SF_HIDDEN_FROM_SENSORS)
			b->flags |= BLIP_DRAW_DISTORTED;

		// determine if its AWACS distorted
		if (awacs_level < 1.0f)
			b->flags |= BLIP_DRAW_DISTORTED;
	}				

	// don't distort the sensor blips if the player has primitive sensors and the nebula effect
	// is not active
	if (Player_ship->flags2 & SF2_PRIMITIVE_SENSORS)
	{
		if (!(The_mission.flags & MISSION_FLAG_FULLNEB))
			b->flags &= ~BLIP_DRAW_DISTORTED;
	}

	N_blips++;
}