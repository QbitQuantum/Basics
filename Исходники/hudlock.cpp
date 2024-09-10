// hud_calculate_lock_position()  will determine where on the screen to draw the lock 
// indicator, and will determine when a lock has occurred.  If the lock indicator is not
// on the screen yet, hud_calculate_lock_start_pos() is called to pick a starting location
void hud_calculate_lock_position(float frametime)
{
	ship_weapon *swp;
	weapon_info	*wip;

	static float pixels_moved_while_locking;
	static float pixels_moved_while_degrading;
	static int Need_new_start_pos = 0;

	static double accumulated_x_pixels, accumulated_y_pixels;
	double int_portion;

	static float last_dist_to_target;
	
	static int catching_up;

	static int maintain_lock_count = 0;

	static float catch_up_distance = 0.0f;

	double hypotenuse, delta_x, delta_y;

	swp = &Player_ship->weapons;
	wip = &Weapon_info[swp->secondary_bank_weapons[swp->current_secondary_bank]];

	if (Player->target_in_lock_cone) {
		if (!Players[Player_num].lock_indicator_visible) {
			hud_calculate_lock_start_pos();
			last_dist_to_target = 0.0f;

			Players[Player_num].lock_indicator_x = Players[Player_num].lock_indicator_start_x;
			Players[Player_num].lock_indicator_y = Players[Player_num].lock_indicator_start_y;
			Players[Player_num].lock_indicator_visible = 1;

			Players[Player_num].lock_time_to_target = i2fl(wip->min_lock_time);
			catching_up = 0;
		}

		Need_new_start_pos = 1;

		if (Player_ai->current_target_is_locked) {
			Players[Player_num].lock_indicator_x = Player->current_target_sx;
			Players[Player_num].lock_indicator_y = Player->current_target_sy;
			return;
		}

		delta_x = Players[Player_num].lock_indicator_x - Player->current_target_sx;
		delta_y = Players[Player_num].lock_indicator_y - Player->current_target_sy;

		if (!delta_y && !delta_x) {
			hypotenuse = 0;
		}
		else {
			hypotenuse = _hypot(delta_y, delta_x);
		}

		Players[Player_num].lock_dist_to_target = (float)hypotenuse;

		if (last_dist_to_target == 0) {
			last_dist_to_target = Players[Player_num].lock_dist_to_target;
		}

		//nprintf(("Alan","dist to target: %.2f\n",Players[Player_num].lock_dist_to_target));
		//nprintf(("Alan","last to target: %.2f\n\n",last_dist_to_target));

		if (catching_up) {
			//nprintf(("Alan","IN CATCH UP MODE  catch_up_dist is %.2f\n",catch_up_distance));	
			if ( Players[Player_num].lock_dist_to_target < catch_up_distance )
				catching_up = 0;
		}
		else {
			//nprintf(("Alan","IN NORMAL MODE\n"));
			if ( (Players[Player_num].lock_dist_to_target - last_dist_to_target) > 2.0f ) {
				catching_up = 1;
				catch_up_distance = last_dist_to_target + wip->catchup_pixel_penalty;
			}
		}

		last_dist_to_target = Players[Player_num].lock_dist_to_target;

		if (!catching_up) {
			Players[Player_num].lock_time_to_target -= frametime;
			if (Players[Player_num].lock_time_to_target < 0.0f)
				Players[Player_num].lock_time_to_target = 0.0f;
		}

		float lock_pixels_per_sec;
		if (Players[Player_num].lock_time_to_target > 0) {
			lock_pixels_per_sec = Players[Player_num].lock_dist_to_target / Players[Player_num].lock_time_to_target;
		} else {
			lock_pixels_per_sec = i2fl(wip->lock_pixels_per_sec);
		}

		if (lock_pixels_per_sec > wip->lock_pixels_per_sec) {
			lock_pixels_per_sec = i2fl(wip->lock_pixels_per_sec);
		}
		
		if (catching_up) {
			pixels_moved_while_locking = wip->catchup_pixels_per_sec * frametime;
		} else {
			pixels_moved_while_locking = lock_pixels_per_sec * frametime;
		}
		
		if ((delta_x != 0) && (hypotenuse != 0)) {
			accumulated_x_pixels += pixels_moved_while_locking * delta_x/hypotenuse; 
		}

		if ((delta_y != 0) && (hypotenuse != 0)) {
			accumulated_y_pixels += pixels_moved_while_locking * delta_y/hypotenuse; 
		}

		if (fl_abs((float)accumulated_x_pixels) > 1.0f) {
			modf(accumulated_x_pixels, &int_portion);

			Players[Player_num].lock_indicator_x -= (int)int_portion;

			if ( fl_abs((float)Players[Player_num].lock_indicator_x - (float)Player->current_target_sx) < fl_abs((float)int_portion) )
				Players[Player_num].lock_indicator_x = Player->current_target_sx;

			accumulated_x_pixels -= int_portion;
		}

		if (fl_abs((float)accumulated_y_pixels) > 1.0f) {
			modf(accumulated_y_pixels, &int_portion);

			Players[Player_num].lock_indicator_y -= (int)int_portion;

			if ( fl_abs((float)Players[Player_num].lock_indicator_y - (float)Player->current_target_sy) < fl_abs((float)int_portion) )
				Players[Player_num].lock_indicator_y = Player->current_target_sy;

			accumulated_y_pixels -= int_portion;
		}

		if ( Missile_track_loop == -1 ) {
			if (wip->hud_tracking_snd >= 0)
			{
				Missile_track_loop = snd_play_looping( &Snds[wip->hud_tracking_snd], 0.0f , -1, -1);
			}
			else
			{
				Missile_track_loop = snd_play_looping( &Snds[ship_get_sound(Player_obj, SND_MISSILE_TRACKING)], 0.0f , -1, -1);
			}
		}

		if (!Players[Player_num].lock_time_to_target) {
			if ( (Players[Player_num].lock_indicator_x == Player->current_target_sx) && (Players[Player_num].lock_indicator_y == Player->current_target_sy) ) {
				if (maintain_lock_count++ > 1) {
					Player_ai->current_target_is_locked = 1;
				}
			} else {
				maintain_lock_count = 0;
			}
		}

	} else {

		if ( Missile_track_loop > -1 )	{
			snd_stop(Missile_track_loop);
			Missile_track_loop = -1;
		}

		Player_ai->current_target_is_locked = 0;

		if (!Players[Player_num].lock_indicator_visible) {
			return;
		}

		catching_up = 0;
		last_dist_to_target = 0.0f;

		if (Need_new_start_pos) {
			hud_calculate_lock_start_pos();
			Need_new_start_pos = 0;
			accumulated_x_pixels = 0.0f;
			accumulated_y_pixels = 0.0f;
		}

		delta_x = Players[Player_num].lock_indicator_x - Players[Player_num].lock_indicator_start_x;
		delta_y = Players[Player_num].lock_indicator_y - Players[Player_num].lock_indicator_start_y;

		if (!delta_y && !delta_x) {
			hypotenuse = 0;
		}
		else {
			hypotenuse = _hypot(delta_y, delta_x);
		}

		Players[Player_num].lock_time_to_target += frametime;

		if (Players[Player_num].lock_time_to_target > wip->min_lock_time)
			Players[Player_num].lock_time_to_target = i2fl(wip->min_lock_time);

		pixels_moved_while_degrading = 2.0f * wip->lock_pixels_per_sec * frametime;

		if ((delta_x != 0) && (hypotenuse != 0))
			accumulated_x_pixels += pixels_moved_while_degrading * delta_x/hypotenuse; 

		if ((delta_y != 0) && (hypotenuse != 0))
			accumulated_y_pixels += pixels_moved_while_degrading * delta_y/hypotenuse; 

		if (fl_abs((float)accumulated_x_pixels) > 1.0f) {
			modf(accumulated_x_pixels, &int_portion);

			Players[Player_num].lock_indicator_x -= (int)int_portion;

			if ( fl_abs((float)Players[Player_num].lock_indicator_x - (float)Players[Player_num].lock_indicator_start_x) < fl_abs((float)int_portion) )
				Players[Player_num].lock_indicator_x = Players[Player_num].lock_indicator_start_x;

			accumulated_x_pixels -= int_portion;
		}

		if (fl_abs((float)accumulated_y_pixels) > 1.0f) {
			modf(accumulated_y_pixels, &int_portion);

			Players[Player_num].lock_indicator_y -= (int)int_portion;

			if ( fl_abs((float)Players[Player_num].lock_indicator_y - (float)Players[Player_num].lock_indicator_start_y) < fl_abs((float)int_portion) )
				Players[Player_num].lock_indicator_y = Players[Player_num].lock_indicator_start_y;

			accumulated_y_pixels -= int_portion;
		}

		if ( (Players[Player_num].lock_indicator_x == Players[Player_num].lock_indicator_start_x) && (Players[Player_num].lock_indicator_y == Players[Player_num].lock_indicator_start_y) ) {
			Players[Player_num].lock_indicator_visible = 0;
		}
	}
}