void update_npc_ai(void)
{
	uint8 i = 0;
	uint32 mapnum = 1;
	uint8 mapnpcnum = 0;
	uint16 npcnum, target;
	double  tickcount;
	uint32 damage;
	char *string = NULL;

	for(mapnum = 1; mapnum < MAX_MAPS; mapnum++){
		if(players_on_map(mapnum)){
			tickcount = gettickcount();

			for(mapnpcnum = 0; mapnpcnum < MAX_MAP_NPCS; mapnpcnum++){
				npcnum = map(mapnum)->npc[mapnpcnum].num;

				if(npcnum > 0){
					target = map(mapnum)->npc[mapnpcnum].target;

					ai_attack_on_sight(mapnpcnum, target, mapnum);

					if(npc(npcnum)->behavior != BEHAVIOR_SHOPKEEPER){
						if(target > 0){
							if(temp_player(target)->loggedin && player(target)->map == mapnum){
								ai_npc_collision(ai_npc_move(mapnum, mapnpcnum, target), mapnum, mapnpcnum, target);

								if(can_npc_attack_player(mapnpcnum,target)){
									if(!can_player_block_hit(target)){
										damage = npc(npcnum)->stat[STAT_STRENGTH] - get_player_protection(target);
										npc_attack_player(mapnpcnum, target, damage);
									}
									else{
										string = comb_4str(item(player(target)->inv[player(target)->equipment[EQUIPMENT_SHIELD]].id)->name, " blocks the ", npc(npcnum)->name,"'s hit!");
										player_msg(target, string, 1); //bright cyan
									}
								}
								else
									map(mapnum)->npc[mapnpcnum].target = 0;
							}
							else
								map(mapnum)->npc[mapnpcnum].target = 0;
						}
					}
					else{
						if((rand() % 4) == 1){
							i = rand() % 4;

							if(can_npc_move(mapnum,mapnpcnum, i))
								npc_move(mapnum,mapnpcnum,i);
						}
					}

					ai_hp_regen(tickcount, mapnum, mapnpcnum);

					if(tickcount > map(mapnum)->npc[mapnpcnum].spawnwait + npc(map(mapnum)->npc[mapnpcnum].num)->spawnsecs * 1000)
						spawn_npc(mapnpcnum, mapnum);
				}
			}
		}
	}
}