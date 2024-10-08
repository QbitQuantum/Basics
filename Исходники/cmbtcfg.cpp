	void CombatConfig::read_combat_config()
	{
      Clib::ConfigFile cf;
      Clib::ConfigElem elem;
      if ( Clib::FileExists( "config/combat.cfg" ) )
	  {
		cf.open( "config/combat.cfg" );
		cf.readraw( elem );
	  }
	  else if ( Plib::systemstate.config.loglevel > 1 )
		INFO_PRINT << "File config/combat.cfg not found, skipping.\n";

	  settingsManager.combat_config.display_parry_success_messages = elem.remove_bool( "DisplayParrySuccessMessages", false );
	  settingsManager.combat_config.warmode_inhibits_regen = elem.remove_bool( "WarmodeInhibitsRegen", false );
	  settingsManager.combat_config.attack_self = elem.remove_bool( "SingleCombat", false );
	  settingsManager.combat_config.warmode_delay = elem.remove_ulong( "WarModeDelay", 1 );
	  settingsManager.combat_config.core_hit_sounds = elem.remove_bool( "CoreHitSounds", false );
	  settingsManager.combat_config.scripted_attack_checks = elem.remove_bool( "ScriptedAttackChecks", false );
	  settingsManager.combat_config.reset_swing_onturn = elem.remove_bool( "ResetSwingOnTurn", false );
	  settingsManager.combat_config.send_swing_packet = elem.remove_bool( "SendSwingPacket", true );
	  settingsManager.combat_config.send_damage_packet = elem.remove_bool( "SendDamagePacket", false );
	  settingsManager.combat_config.attack_while_frozen = elem.remove_bool( "AttackWhileFrozen", true );
	  settingsManager.combat_config.send_attack_msg = elem.remove_bool( "SendAttackMsg", true );
	}