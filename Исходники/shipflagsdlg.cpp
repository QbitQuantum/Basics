BOOL ship_flags_dlg::OnInitDialog() 
{
	int j, first;
	int protect_ship = 0, beam_protect_ship = 0, flak_protect_ship = 0, laser_protect_ship = 0, missile_protect_ship = 0;
	int ignore_count = 0, reinforcement = 0, cargo_known = 0, immobile = 0;
	int destroy_before_mission = 0, no_arrival_music = 0, escort = 0, invulnerable = 0, targetable_as_bomb = 0;
	int hidden_from_sensors = 0, primitive_sensors = 0, no_subspace_drive = 0, affected_by_gravity = 0;
	int toggle_subsystem_scanning = 0, scannable = 0, kamikaze = 0, no_dynamic = 0, red_alert_carry = 0;
	int special_warpin = 0, disable_messages = 0, guardian = 0, vaporize = 0, stealth = 0, friendly_stealth_invisible = 0;
	int no_death_scream = 0, always_death_scream = 0, scramble_messages = 0;
	int nav_carry = 0, nav_needslink = 0, hide_ship_name = 0, set_class_dynamically = 0, no_ets = 0, cloaked = 0, no_collide = 0;

	object *objp;
	ship *shipp;
	bool ship_in_wing = false;

	first = 1;
	objp = GET_FIRST(&obj_used_list);
	while (objp != END_OF_LIST(&obj_used_list)) {
		if ((objp->type == OBJ_START) || (objp->type == OBJ_SHIP)) {
			if (objp->flags & OF_MARKED) {
				shipp = &Ships[objp->instance];

				if (first) {
					first = 0;
					scannable = (shipp->flags & SF_SCANNABLE) ? 1 : 0;
					red_alert_carry = (shipp->flags & SF_RED_ALERT_STORE_STATUS) ? 1 : 0;
					special_warpin = (objp->flags & OF_SPECIAL_WARPIN) ? 1 : 0;
					protect_ship = (objp->flags & OF_PROTECTED) ? 1 : 0;
					beam_protect_ship = (objp->flags & OF_BEAM_PROTECTED) ? 1 : 0;
					flak_protect_ship = (objp->flags & OF_FLAK_PROTECTED) ? 1 : 0;
					laser_protect_ship = (objp->flags & OF_LASER_PROTECTED) ? 1 : 0;
					missile_protect_ship = (objp->flags & OF_MISSILE_PROTECTED) ? 1 : 0;
					invulnerable = (objp->flags & OF_INVULNERABLE) ? 1 : 0;
					targetable_as_bomb = (objp->flags & OF_TARGETABLE_AS_BOMB) ? 1 : 0;
					immobile = (objp->flags & OF_IMMOBILE) ? 1 : 0;
					hidden_from_sensors = (shipp->flags & SF_HIDDEN_FROM_SENSORS) ? 1 : 0;
					primitive_sensors = (shipp->flags2 & SF2_PRIMITIVE_SENSORS) ? 1 : 0;
					no_subspace_drive = (shipp->flags2 & SF2_NO_SUBSPACE_DRIVE) ? 1 : 0;
					affected_by_gravity = (shipp->flags2 & SF2_AFFECTED_BY_GRAVITY) ? 1 : 0;
					toggle_subsystem_scanning = (shipp->flags2 & SF2_TOGGLE_SUBSYSTEM_SCANNING) ? 1 : 0;
					ignore_count = (shipp->flags & SF_IGNORE_COUNT) ? 1 : 0;
					no_arrival_music = (shipp->flags & SF_NO_ARRIVAL_MUSIC) ? 1 : 0;
					cargo_known = (shipp->flags & SF_CARGO_REVEALED) ? 1 : 0;
					no_dynamic = (Ai_info[shipp->ai_index].ai_flags & AIF_NO_DYNAMIC) ? 1 : 0;
					disable_messages = (shipp->flags2 & SF2_NO_BUILTIN_MESSAGES) ? 1 : 0;
					set_class_dynamically = (shipp->flags2 & SF2_SET_CLASS_DYNAMICALLY) ? 1 : 0;
					no_death_scream = (shipp->flags2 & SF2_NO_DEATH_SCREAM) ? 1 : 0;
					always_death_scream = (shipp->flags2 & SF2_ALWAYS_DEATH_SCREAM) ? 1 : 0;
					guardian = (shipp->ship_guardian_threshold) ? 1 : 0;
					vaporize = (shipp->flags & SF_VAPORIZE) ? 1 : 0;
					stealth = (shipp->flags2 & SF2_STEALTH) ? 1 : 0;
					friendly_stealth_invisible = (shipp->flags2 & SF2_FRIENDLY_STEALTH_INVIS) ? 1 : 0;
					nav_carry = (shipp->flags2 & SF2_NAVPOINT_CARRY) ? 1 : 0; 
					nav_needslink = (shipp->flags2 & SF2_NAVPOINT_NEEDSLINK) ? 1 : 0;
					hide_ship_name = (shipp->flags2 & SF2_HIDE_SHIP_NAME) ? 1 : 0;
					no_ets = (shipp->flags2 & SF2_NO_ETS) ? 1 : 0;
					cloaked = (shipp->flags2 & SF2_CLOAKED) ? 1 : 0;
					scramble_messages = (shipp->flags2 & SF2_SCRAMBLE_MESSAGES) ? 1 : 0;
					no_collide = (objp->flags & OF_COLLIDES) ? 0 : 1;

					destroy_before_mission = (shipp->flags & SF_KILL_BEFORE_MISSION) ? 1 : 0;
					m_destroy_value.init(shipp->final_death_time);

					kamikaze = (Ai_info[shipp->ai_index].ai_flags & AIF_KAMIKAZE) ? 1 : 0;
					m_kdamage.init( Ai_info[shipp->ai_index].kamikaze_damage );

					escort = (shipp->flags & SF_ESCORT) ? 1 : 0;
					m_escort_value.init(shipp->escort_priority);
					
					if(The_mission.game_type & MISSION_TYPE_MULTI) {
						m_respawn_priority.init(shipp->respawn_priority);
					}

					for (j=0; j<Num_reinforcements; j++) {
						if (!stricmp(Reinforcements[j].name, shipp->ship_name)) {
							break;
						}
					}

					reinforcement = (j < Num_reinforcements) ? 1 : 0;

					// check if ship in wing
					ship_in_wing = (shipp->wingnum != -1);;
				} else {

					scannable = tristate_set( shipp->flags & SF_SCANNABLE, scannable );
					red_alert_carry = tristate_set( shipp->flags & SF_RED_ALERT_STORE_STATUS, red_alert_carry );
					special_warpin = tristate_set( objp->flags & OF_SPECIAL_WARPIN, special_warpin );
					protect_ship = tristate_set(objp->flags & OF_PROTECTED, protect_ship);
					beam_protect_ship = tristate_set(objp->flags & OF_BEAM_PROTECTED, beam_protect_ship);
					flak_protect_ship = tristate_set(objp->flags & OF_FLAK_PROTECTED, flak_protect_ship);
					laser_protect_ship = tristate_set(objp->flags & OF_LASER_PROTECTED, laser_protect_ship);
					missile_protect_ship = tristate_set(objp->flags & OF_MISSILE_PROTECTED, missile_protect_ship);
					invulnerable = tristate_set(objp->flags & OF_INVULNERABLE, invulnerable);
					targetable_as_bomb = tristate_set(objp->flags & OF_TARGETABLE_AS_BOMB, targetable_as_bomb);
					immobile = tristate_set(objp->flags & OF_IMMOBILE, immobile);
					hidden_from_sensors = tristate_set(shipp->flags & SF_HIDDEN_FROM_SENSORS, hidden_from_sensors);
					primitive_sensors = tristate_set(shipp->flags2 & SF2_PRIMITIVE_SENSORS, primitive_sensors);
					no_subspace_drive = tristate_set(shipp->flags2 & SF2_NO_SUBSPACE_DRIVE, no_subspace_drive);
					affected_by_gravity = tristate_set(shipp->flags2 & SF2_AFFECTED_BY_GRAVITY, affected_by_gravity);
					toggle_subsystem_scanning = tristate_set(shipp->flags2 & SF2_TOGGLE_SUBSYSTEM_SCANNING, toggle_subsystem_scanning);
					ignore_count = tristate_set(shipp->flags & SF_IGNORE_COUNT, ignore_count);
					no_arrival_music = tristate_set(shipp->flags & SF_NO_ARRIVAL_MUSIC, no_arrival_music);
					cargo_known = tristate_set(shipp->flags & SF_CARGO_REVEALED, cargo_known);
					no_dynamic = tristate_set( Ai_info[shipp->ai_index].ai_flags & AIF_NO_DYNAMIC, no_dynamic );
					disable_messages = tristate_set(shipp->flags2 & SF2_NO_BUILTIN_MESSAGES, disable_messages);
					set_class_dynamically = tristate_set(shipp->flags2 & SF2_SET_CLASS_DYNAMICALLY, set_class_dynamically);
					no_death_scream = tristate_set(shipp->flags2 & SF2_NO_DEATH_SCREAM, no_death_scream);
					always_death_scream = tristate_set(shipp->flags2 & SF2_ALWAYS_DEATH_SCREAM, always_death_scream);
					guardian = tristate_set(shipp->ship_guardian_threshold, guardian);
					vaporize = tristate_set(shipp->flags & SF_VAPORIZE, vaporize);
					stealth = tristate_set(shipp->flags2 & SF2_STEALTH, stealth);
					friendly_stealth_invisible = tristate_set(shipp->flags2 & SF2_FRIENDLY_STEALTH_INVIS, friendly_stealth_invisible);
					nav_carry = tristate_set(shipp->flags2 & SF2_NAVPOINT_CARRY, nav_carry);
					nav_needslink = tristate_set(shipp->flags2 & SF2_NAVPOINT_NEEDSLINK, nav_needslink);
					hide_ship_name = tristate_set(shipp->flags2 & SF2_HIDE_SHIP_NAME, hide_ship_name);
					no_ets = tristate_set(shipp->flags2 & SF2_NO_ETS, no_ets);
					cloaked = tristate_set(shipp->flags2 & SF2_CLOAKED, cloaked);
					scramble_messages = tristate_set(shipp->flags2 & SF2_SCRAMBLE_MESSAGES, scramble_messages);
					no_collide = tristate_set(!(objp->flags & OF_COLLIDES), no_collide);

					// check the final death time and set the internal variable according to whether or not
					// the final_death_time is set.  Also, the value in the edit box must be set if all the
					// values are the same, and cleared if the values are not the same.
					destroy_before_mission = tristate_set(shipp->flags & SF_KILL_BEFORE_MISSION, destroy_before_mission);
					m_destroy_value.set(shipp->final_death_time);

					kamikaze = tristate_set( Ai_info[shipp->ai_index].ai_flags & AIF_KAMIKAZE, kamikaze );
					m_kdamage.set( Ai_info[shipp->ai_index].kamikaze_damage );

					escort = tristate_set(shipp->flags & SF_ESCORT, escort);
					m_escort_value.init(shipp->escort_priority);

					if(The_mission.game_type & MISSION_TYPE_MULTI) {
						m_respawn_priority.init(shipp->escort_priority);
					}

					for (j=0; j<Num_reinforcements; j++) {
						if (!stricmp(Reinforcements[j].name, shipp->ship_name)) {
							break;
						}
					}
					reinforcement = tristate_set(j < Num_reinforcements, reinforcement);

					// check if ship in wing
					ship_in_wing = (shipp->wingnum != -1);;
				}

			}
		}

		objp = GET_NEXT(objp);
	}

	CDialog::OnInitDialog();
	
	m_protect_ship.SetCheck(protect_ship);
	m_beam_protect_ship.SetCheck(beam_protect_ship);
	m_flak_protect_ship.SetCheck(flak_protect_ship);
	m_laser_protect_ship.SetCheck(laser_protect_ship);
	m_missile_protect_ship.SetCheck(missile_protect_ship);
	m_ignore_count.SetCheck(ignore_count);
	m_reinforcement.SetCheck(reinforcement);
	m_cargo_known.SetCheck(cargo_known);
	m_destroy.SetCheck(destroy_before_mission);
	m_no_arrival_music.SetCheck(no_arrival_music);
	m_escort.SetCheck(escort);
	m_invulnerable.SetCheck(invulnerable);
	m_targetable_as_bomb.SetCheck(targetable_as_bomb);
	m_immobile.SetCheck(immobile);
	m_hidden.SetCheck(hidden_from_sensors);
	m_primitive_sensors.SetCheck(primitive_sensors);
	m_no_subspace_drive.SetCheck(no_subspace_drive);
	m_affected_by_gravity.SetCheck(affected_by_gravity);
	m_toggle_subsystem_scanning.SetCheck(toggle_subsystem_scanning);
	m_scannable.SetCheck(scannable);
	m_kamikaze.SetCheck(kamikaze);
	m_no_dynamic.SetCheck(no_dynamic);
	m_red_alert_carry.SetCheck(red_alert_carry);
	m_special_warpin.SetCheck(special_warpin);
	m_disable_messages.SetCheck(disable_messages);
	m_set_class_dynamically.SetCheck(set_class_dynamically);
	m_no_death_scream.SetCheck(no_death_scream);
	m_always_death_scream.SetCheck(always_death_scream);
	m_guardian.SetCheck(guardian);
	m_vaporize.SetCheck(vaporize);
	m_stealth.SetCheck(stealth);
	m_friendly_stealth_invisible.SetCheck(friendly_stealth_invisible);
	m_nav_carry.SetCheck(nav_carry);
	m_nav_needslink.SetCheck(nav_needslink);
	m_hide_ship_name.SetCheck(hide_ship_name);
	m_disable_ets.SetCheck(no_ets);
	m_cloaked.SetCheck(cloaked);
	m_scramble_messages.SetCheck(scramble_messages);
	m_no_collide.SetCheck(no_collide);
		
	m_kdamage.setup(IDC_KDAMAGE, this);
	m_destroy_value.setup(IDC_DESTROY_VALUE, this);
	m_escort_value.setup(IDC_ESCORT_PRIORITY, this);

	if(The_mission.game_type & MISSION_TYPE_MULTI) {
		m_respawn_priority.setup(IDC_RESPAWN_PRIORITY, this);
	}
	m_destroy_spin.SetRange(0, UD_MAXVAL);

	m_destroy_value.display();
	m_kdamage.display();
	m_escort_value.display();

	if(The_mission.game_type & MISSION_TYPE_MULTI) {
		m_respawn_priority.display();
	} else {
		GetDlgItem(IDC_RESPAWN_PRIORITY)->EnableWindow(FALSE);
	}

	// flags that enable/disable according to whether this isn't a player
	GetDlgItem(IDC_REINFORCEMENT)->EnableWindow(p_enable && !ship_in_wing);
	GetDlgItem(IDC_CARGO_KNOWN)->EnableWindow(p_enable);
	GetDlgItem(IDC_DESTROY_CHECK)->EnableWindow(p_enable);
	GetDlgItem(IDC_DESTROY_VALUE)->EnableWindow(p_enable);
	GetDlgItem(IDC_DESTROY_SPIN)->EnableWindow(p_enable);
	GetDlgItem(IDC_SCANNABLE)->EnableWindow(p_enable);

	// disable the spinner and edit window if the corrsponding check box
	// is not checked!
	if (m_destroy.GetCheck() != 1) {
		GetDlgItem(IDC_DESTROY_VALUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DESTROY_SPIN)->EnableWindow(FALSE);
	}

	// disable destroy option for ship in wing
	if (ship_in_wing) {
		GetDlgItem(IDC_DESTROY_CHECK)->EnableWindow(FALSE);
		GetDlgItem(IDC_DESTROY_VALUE)->EnableWindow(FALSE);
		GetDlgItem(IDC_DESTROY_SPIN)->EnableWindow(FALSE);
	}

	// maybe disable escort priority window
	if (m_escort.GetCheck() == 1)
		GetDlgItem(IDC_ESCORT_PRIORITY)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_ESCORT_PRIORITY)->EnableWindow(FALSE);

	// maybe disable kamikaze damage window
	if (m_kamikaze.GetCheck() == 1)
		GetDlgItem(IDC_KDAMAGE)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_KDAMAGE)->EnableWindow(FALSE);

	return TRUE;
}