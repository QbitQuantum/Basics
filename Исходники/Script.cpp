ValueType getSystemVar(const EERIE_SCRIPT * es, Entity * entity, const std::string & name,
                       std::string& txtcontent, float * fcontent,long * lcontent) {
	
	arx_assert(!name.empty() && name[0] == '^', "bad system variable: \"%s\"", name.c_str());
	
	char c = (name.length() < 2) ? '\0' : name[1];
	switch(c) {
		
		case '$': {
			
			if(name == "^$param1") {
				txtcontent = SSEPARAMS[0];
				return TYPE_TEXT;
			}
			
			if(name == "^$param2") {
				txtcontent = SSEPARAMS[1];
				return TYPE_TEXT;
			}
			
			if(name == "^$param3") {
				txtcontent = SSEPARAMS[2];
				return TYPE_TEXT;
			}
			
			if(name == "^$objontop") {
				txtcontent = "none";
				if(entity) {
					MakeTopObjString(entity, txtcontent);
				}
				return TYPE_TEXT;
			}
			
			break;
		}
		
		case '&': {
			
			if(name == "^&param1") {
				*fcontent = (float)atof(SSEPARAMS[0]);
				return TYPE_FLOAT;
			}
			
			if(name == "^&param2") {
				*fcontent = (float)atof(SSEPARAMS[1]);
				return TYPE_FLOAT;
			}
			
			if(name == "^&param3") {
				*fcontent = (float)atof(SSEPARAMS[2]);
				return TYPE_FLOAT;
			}
			
			if(name == "^&playerdist") {
				if(entity) {
					*fcontent = fdist(player.pos, entity->pos);
					return TYPE_FLOAT;
				}
			}
			
			break;
		}
		
		case '#': {
			
			if(name == "^#playerdist") {
				if(entity) {
					*lcontent = (long)fdist(player.pos, entity->pos);
					return TYPE_LONG;
				}
			}
			
			if(name == "^#param1") {
				*lcontent = atol(SSEPARAMS[0]);
				return TYPE_LONG;
			}
			
			if(name == "^#param2") {
				*lcontent = atol(SSEPARAMS[1]);
				return TYPE_LONG;
			}
			
			if(name == "^#param3") {
				*lcontent = atol(SSEPARAMS[2]);
				return TYPE_LONG;
			}
			
			if(name == "^#timer1") {
				if(!entity || entity->script.timers[0] == 0) {
					*lcontent = 0;
				} else {
					*lcontent = long((unsigned long)(arxtime) - es->timers[0]);
				}
				return TYPE_LONG;
			}
			
			if(name == "^#timer2") {
				if(!entity || entity->script.timers[1] == 0) {
					*lcontent = 0;
				} else {
					*lcontent = long((unsigned long)(arxtime) - es->timers[1]);
				}
				return TYPE_LONG;
			}
			
			if(name == "^#timer3") {
				if(!entity || entity->script.timers[2] == 0) {
					*lcontent = 0;
				} else {
					*lcontent = long((unsigned long)(arxtime) - es->timers[2]);
				}
				return TYPE_LONG;
			}
			
			if(name == "^#timer4") {
				if(!entity || entity->script.timers[3] == 0) {
					*lcontent = 0;
				} else {
					*lcontent = long((unsigned long)(arxtime) - es->timers[3]);
				}
				return TYPE_LONG;
			}
			
			break;
		}
		
		case 'g': {
			
			if(name == "^gore") {
				*lcontent = 1;
				return TYPE_LONG;
			}
			
			if(name == "^gamedays") {
				*lcontent = static_cast<long>(float(arxtime) / 86400000);
				return TYPE_LONG;
			}
			
			if(name == "^gamehours") {
				*lcontent = static_cast<long>(float(arxtime) / 3600000);
				return TYPE_LONG;
			}
			
			if(name == "^gameminutes") {
				*lcontent = static_cast<long>(float(arxtime) / 60000);
				return TYPE_LONG;
			}
			
			if(name == "^gameseconds") {
				*lcontent = static_cast<long>(float(arxtime) / 1000);
				return TYPE_LONG;
			}
			
			break;
		}
		
		case 'a': {
			
			if(boost::starts_with(name, "^amount")) {
				if(entity && (entity->ioflags & IO_ITEM)) {
					*fcontent = entity->_itemdata->count;
				} else {
					*fcontent = 0;
				}
				return TYPE_FLOAT;
			}
			
			if(name == "^arxdays") {
				*lcontent = static_cast<long>(float(arxtime) / 7200000);
				return TYPE_LONG;
			}
			
			if(name == "^arxhours") {
				*lcontent = static_cast<long>(float(arxtime) / 600000);
				return TYPE_LONG;
			}
			
			if(name == "^arxminutes") {
				*lcontent = static_cast<long>(float(arxtime) / 10000);
				return TYPE_LONG;
			}
			
			if(name == "^arxseconds") {
				*lcontent = static_cast<long>(float(arxtime) / 1000) * 6;
				return TYPE_LONG;
			}
			
			if(name == "^arxtime_hours") {
				*lcontent = static_cast<long>(float(arxtime) / 600000);
				while(*lcontent > 12) {
					*lcontent -= 12;
				}
				return TYPE_LONG;
			}
			
			if(name == "^arxtime_minutes") {
				*lcontent = static_cast<long>(float(arxtime) / 10000);
				while(*lcontent > 60) {
					*lcontent -= 60;
				}
				return TYPE_LONG;
			}
			
			if(name == "^arxtime_seconds") {
				*lcontent = static_cast<long>(float(arxtime) * 6 / 1000);
				while(*lcontent > 60) {
					*lcontent -= 60;
				}
				return TYPE_LONG;
			}
			
			break;
		}
		
		case 'r': {
			
			if(boost::starts_with(name, "^realdist_")) {
				if(entity) {
					const char * obj = name.c_str() + 10;
					
					if(!strcmp(obj, "player")) {
						if(entity->requestRoomUpdate) {
							UpdateIORoom(entity);
						}
						long Player_Room = ARX_PORTALS_GetRoomNumForPosition(player.pos, 1);
						*fcontent = SP_GetRoomDist(entity->pos, player.pos, entity->room, Player_Room);
						return TYPE_FLOAT;
					}
					
					EntityHandle t = entities.getById(obj);
					if(ValidIONum(t)) {
						if((entity->show == SHOW_FLAG_IN_SCENE
						    || entity->show == SHOW_FLAG_IN_INVENTORY)
						   && (entities[t]->show == SHOW_FLAG_IN_SCENE
						       || entities[t]->show == SHOW_FLAG_IN_INVENTORY)) {
							
							Vec3f pos  = GetItemWorldPosition(entity);
							Vec3f pos2 = GetItemWorldPosition(entities[t]);
							
							if(entity->requestRoomUpdate) {
								UpdateIORoom(entity);
							}
							
							if(entities[t]->requestRoomUpdate) {
								UpdateIORoom(entities[t]);
							}
							
							*fcontent = SP_GetRoomDist(pos, pos2, entity->room, entities[t]->room);
							
						} else {
							// Out of this world item
							*fcontent = 99999999999.f;
						}
						return TYPE_FLOAT;
					}
					
					*fcontent = 99999999999.f;
					return TYPE_FLOAT;
				}
			}
			
			if(boost::starts_with(name, "^repairprice_")) {
				EntityHandle t = entities.getById(name.substr(13));
				if(ValidIONum(t)) {
					*fcontent = ARX_DAMAGES_ComputeRepairPrice(entities[t], entity);
				} else {
					*fcontent = 0;
				}
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^rnd_")) {
				const char * max = name.c_str() + 5;
				// TODO should max be inclusive or exclusive?
				// if inclusive, use proper integer random, otherwise fix rnd()?
				if(max[0]) {
					float t = (float)atof(max);
					*fcontent = Random::getf(0.f, t);
					return TYPE_FLOAT;
				}
				*fcontent = 0;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^rune_")) {
				std::string temp = name.substr(6);
				*lcontent = 0;
				if(temp == "aam") {
					*lcontent = player.rune_flags & FLAG_AAM;
				} else if(temp == "cetrius") {
					*lcontent = player.rune_flags & FLAG_CETRIUS;
				} else if(temp == "comunicatum") {
					*lcontent = player.rune_flags & FLAG_COMUNICATUM;
				} else if(temp == "cosum") {
					*lcontent = player.rune_flags & FLAG_COSUM;
				} else if(temp == "folgora") {
					*lcontent = player.rune_flags & FLAG_FOLGORA;
				} else if(temp == "fridd") {
					*lcontent = player.rune_flags & FLAG_FRIDD;
				} else if(temp == "kaom") {
					*lcontent = player.rune_flags & FLAG_KAOM;
				} else if(temp == "mega") {
					*lcontent = player.rune_flags & FLAG_MEGA;
				} else if(temp == "morte") {
					*lcontent = player.rune_flags & FLAG_MORTE;
				} else if(temp == "movis") {
					*lcontent = player.rune_flags & FLAG_MOVIS;
				} else if(temp == "nhi") {
					*lcontent = player.rune_flags & FLAG_NHI;
				} else if(temp == "rhaa") {
					*lcontent = player.rune_flags & FLAG_RHAA;
				} else if(temp == "spacium") {
					*lcontent = player.rune_flags & FLAG_SPACIUM;
				} else if(temp == "stregum") {
					*lcontent = player.rune_flags & FLAG_STREGUM;
				} else if(temp == "taar") {
					*lcontent = player.rune_flags & FLAG_TAAR;
				} else if(temp == "tempus") {
					*lcontent = player.rune_flags & FLAG_TEMPUS;
				} else if(temp == "tera") {
					*lcontent = player.rune_flags & FLAG_TERA;
				} else if(temp == "vista") {
					*lcontent = player.rune_flags & FLAG_VISTA;
				} else if(temp == "vitae") {
					*lcontent = player.rune_flags & FLAG_VITAE;
				} else if(temp == "yok") {
					*lcontent = player.rune_flags & FLAG_YOK;
				}
				return TYPE_LONG;
			}
			
			break;
		}
		
		case 'i': {
			
			if(boost::starts_with(name, "^inzone_")) {
				const char * zone = name.c_str() + 8;
				ARX_PATH * ap = ARX_PATH_GetAddressByName(zone);
				*lcontent = 0;
				if(entity && ap) {
					if(ARX_PATH_IsPosInZone(ap, entity->pos)) {
						*lcontent = 1;
					}
				}
				return TYPE_LONG;
			}
			
			if(boost::starts_with(name, "^ininitpos")) {
				*lcontent = 0;
				if(entity) {
					Vec3f pos = GetItemWorldPosition(entity);
					if(pos == entity->initpos)
						*lcontent = 1;
				}
				return TYPE_LONG;
			}
			
			if(boost::starts_with(name, "^inplayerinventory")) {
				*lcontent = 0;
				if(entity && (entity->ioflags & IO_ITEM) && IsInPlayerInventory(entity)) {
					*lcontent = 1;
				}
				return TYPE_LONG;
			}
			
			break;
		}
		
		case 'b': {
			
			if(boost::starts_with(name, "^behavior")) {
				txtcontent = "";
				if(entity && (entity->ioflags & IO_NPC)) {
					if(entity->_npcdata->behavior & BEHAVIOUR_LOOK_AROUND) {
						txtcontent += "l";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_SNEAK) {
						txtcontent += "s";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_DISTANT) {
						txtcontent += "d";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_MAGIC) {
						txtcontent += "m";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_FIGHT) {
						txtcontent += "f";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_GO_HOME) {
						txtcontent += "h";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_FRIENDLY) {
						txtcontent += "r";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_MOVE_TO) {
						txtcontent += "t";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_FLEE) {
						txtcontent += "e";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_LOOK_FOR) {
						txtcontent += "o";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_HIDE) {
						txtcontent += "i";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_WANDER_AROUND) {
						txtcontent += "w";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_GUARD) {
						txtcontent += "u";
					}
					if(entity->_npcdata->behavior & BEHAVIOUR_STARE_AT) {
						txtcontent += "a";
					}
				}
				return TYPE_TEXT;
			}
			
			break;
		}
		
		case 's': {
			
			if(boost::starts_with(name, "^sender")) {
				if(!EVENT_SENDER) {
					txtcontent = "none";
				} else if(EVENT_SENDER == entities.player()) {
					txtcontent = "player";
				} else {
					txtcontent = EVENT_SENDER->idString();
				}
				return TYPE_TEXT;
			}
			
			if(boost::starts_with(name, "^scale")) {
				*fcontent = (entity) ? entity->scale * 100.f : 0.f;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^speaking")) {
				if(entity) {
					for(size_t i = 0; i < MAX_ASPEECH; i++) {
						if(aspeech[i].exist && entity == aspeech[i].io) {
							*lcontent = 1;
							return TYPE_LONG;
						}
					}
				}
				*lcontent = 0;
				return TYPE_LONG;
			}
			
			break;
		}
		
		case 'm': {
			
			if(boost::starts_with(name, "^me")) {
				if(!entity) {
					txtcontent = "none";
				} else if(entity == entities.player()) {
					txtcontent = "player";
				} else {
					txtcontent = entity->idString();
				}
				return TYPE_TEXT;
			}
			
			if(boost::starts_with(name, "^maxlife")) {
				*fcontent = 0;
				if(entity && (entity->ioflags & IO_NPC)) {
					*fcontent = entity->_npcdata->lifePool.max;
				}
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^mana")) {
				*fcontent = 0;
				if(entity && (entity->ioflags & IO_NPC)) {
					*fcontent = entity->_npcdata->manaPool.current;
				}
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^maxmana")) {
				*fcontent = 0;
				if(entity && (entity->ioflags & IO_NPC)) {
					*fcontent = entity->_npcdata->manaPool.max;
				}
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^myspell_")) {
				SpellType id = GetSpellId(name.substr(9));
				if(id != SPELL_NONE) {
					if(spells.ExistAnyInstanceForThisCaster(id, entity->index())) {
						*lcontent = 1;
						return TYPE_LONG;
					}
				}
				*lcontent = 0;
				return TYPE_LONG;
			}
			
			if(boost::starts_with(name, "^maxdurability")) {
				*fcontent = (entity) ? entity->max_durability : 0.f;
				return TYPE_FLOAT;
			}
			
			break;
		}
		
		case 'l': {
			
			if(boost::starts_with(name, "^life")) {
				*fcontent = 0;
				if(entity && (entity->ioflags & IO_NPC)) {
					*fcontent = entity->_npcdata->lifePool.current;
				}
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^last_spawned")) {
				txtcontent = (LASTSPAWNED) ? LASTSPAWNED->idString() : "none";
				return TYPE_TEXT;
			}
			
			break;
		}
		
		case 'd': {
			
			if(boost::starts_with(name, "^dist_")) {
				if(entity) {
					const char * obj = name.c_str() + 6;
					
					if(!strcmp(obj, "player")) {
						*fcontent = fdist(player.pos, entity->pos);
						return TYPE_FLOAT;
					}
					
					EntityHandle t = entities.getById(obj);
					if(ValidIONum(t)) {
						if((entity->show == SHOW_FLAG_IN_SCENE
						    || entity->show == SHOW_FLAG_IN_INVENTORY)
						   && (entities[t]->show == SHOW_FLAG_IN_SCENE
						       || entities[t]->show == SHOW_FLAG_IN_INVENTORY)) {
							Vec3f pos  = GetItemWorldPosition(entity);
							Vec3f pos2 = GetItemWorldPosition(entities[t]);
							*fcontent = fdist(pos, pos2);
							return TYPE_FLOAT;
						}
					}
					
					*fcontent = 99999999999.f;
					return TYPE_FLOAT;
				}
			}
			
			if(boost::starts_with(name, "^demo")) {
				*lcontent = (resources->getReleaseType() & PakReader::Demo) ? 1 : 0;
				return TYPE_LONG;
			}
			
			if(boost::starts_with(name, "^durability")) {
				*fcontent = (entity) ? entity->durability : 0.f;
				return TYPE_FLOAT;
			}
			
			break;
		}
		
		case 'p': {
			
			if(boost::starts_with(name, "^price")) {
				*fcontent = 0;
				if(entity && (entity->ioflags & IO_ITEM)) {
					*fcontent = static_cast<float>(entity->_itemdata->price);
				}
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_zone")) {
				txtcontent = (player.inzone) ? player.inzone->name : "none";
				return TYPE_TEXT;
			}
			
			if(boost::starts_with(name, "^player_life")) {
				*fcontent = player.Full_life; // TODO why not player.life like everywhere else?
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^poisoned")) {
				*fcontent = 0;
				if(entity && (entity->ioflags & IO_NPC)) {
					*fcontent = entity->_npcdata->poisonned;
				}
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^poisonous")) {
				*fcontent = (entity) ? entity->poisonous : 0.f;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^possess_")) {
				EntityHandle t = entities.getById(name.substr(9));
				if(ValidIONum(t)) {
					if(IsInPlayerInventory(entities[t])) {
						*lcontent = 1;
						return TYPE_LONG;
					}
					for(long i = 0; i < MAX_EQUIPED; i++) {
						if(ValidIONum(player.equiped[i]) && player.equiped[i] == t) {
							*lcontent = 2;
							return TYPE_LONG;
						}
					}
				}
				*lcontent = 0;
				return TYPE_LONG;
			}
			
			if(boost::starts_with(name, "^player_gold")) {
				*fcontent = static_cast<float>(player.gold);
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_maxlife")) {
				*fcontent = player.Full_maxlife;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_attribute_strength")) {
				*fcontent = player.m_attributeFull.strength;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_attribute_dexterity")) {
				*fcontent = player.m_attributeFull.dexterity;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_attribute_constitution")) {
				*fcontent = player.m_attributeFull.constitution;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_attribute_mind")) {
				*fcontent = player.m_attributeFull.mind;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_skill_stealth")) {
				*fcontent = player.m_skillFull.stealth;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_skill_mecanism")) {
				*fcontent = player.m_skillFull.mecanism;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_skill_intuition")) {
				*fcontent = player.m_skillFull.intuition;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_skill_etheral_link")) {
				*fcontent = player.m_skillFull.etheralLink;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_skill_object_knowledge")) {
				*fcontent = player.m_skillFull.objectKnowledge;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_skill_casting")) {
				*fcontent = player.m_skillFull.casting;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_skill_projectile")) {
				*fcontent = player.m_skillFull.projectile;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_skill_close_combat")) {
				*fcontent = player.m_skillFull.closeCombat;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_skill_defense")) {
				*fcontent = player.m_skillFull.defense;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_hunger")) {
				*fcontent = player.hunger;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^player_poison")) {
				*fcontent = player.poison;
				return TYPE_FLOAT;
			}
			
			if(boost::starts_with(name, "^playercasting")) {
				for(size_t i = 0; i < MAX_SPELLS; i++) {
					const SpellBase * spell = spells[SpellHandle(i)];
					
					if(spell && spell->m_caster == PlayerEntityHandle) {
						if(   spell->m_type == SPELL_LIFE_DRAIN
						   || spell->m_type == SPELL_HARM
						   || spell->m_type == SPELL_FIRE_FIELD
						   || spell->m_type == SPELL_ICE_FIELD
						   || spell->m_type == SPELL_LIGHTNING_STRIKE
						   || spell->m_type == SPELL_MASS_LIGHTNING_STRIKE
						) {
							*lcontent = 1;
							return TYPE_LONG;
						}
					}
				}
				*lcontent = 0;
				return TYPE_LONG;
			}
			
			if(boost::starts_with(name, "^playerspell_")) {
				std::string temp = name.substr(13);
				
				SpellType id = GetSpellId(temp);
				if(id != SPELL_NONE) {
					if(spells.ExistAnyInstanceForThisCaster(id, PlayerEntityHandle)) {
						*lcontent = 1;
						return TYPE_LONG;
					}
				}
				
				if(temp == "invisibility" && entities.player()->invisibility > 0.3f) {
					*lcontent = 1;
					return TYPE_LONG;
				}
				
				*lcontent = 0;
				return TYPE_LONG;
			}
			
			break;
		}
		
		case 'n': {
			
			if(boost::starts_with(name, "^npcinsight")) {
				Entity * ioo = ARX_NPC_GetFirstNPCInSight(entity);
				if(!ioo) {
					txtcontent = "none";
				} else if(ioo == entities.player()) {
					txtcontent = "player";
				} else {
					txtcontent = ioo->idString();
				}
				return TYPE_TEXT;
			}
			
			break;
		}
		
		case 't': {
			
			if(boost::starts_with(name, "^target")) {
				if(!entity) {
					txtcontent = "none";
				} else if(entity->targetinfo == PlayerEntityHandle) {
					txtcontent = "player";
				} else if(!ValidIONum(entity->targetinfo)) {
					txtcontent = "none";
				} else {
					txtcontent = entities[entity->targetinfo]->idString();
				}
				return TYPE_TEXT;
			}
			
			break;
		}
		
		case 'f': {
			
			if(boost::starts_with(name, "^focal")) {
				if(entity && (entity->ioflags & IO_CAMERA)) {
					*fcontent = entity->_camdata->cam.focal;
					return TYPE_FLOAT;
				}
			}
			
			if(boost::starts_with(name, "^fighting")) {
				*lcontent = long(ARX_PLAYER_IsInFightMode());
				return TYPE_LONG;
			}
			
			break;
		}
		
	}
	
	*lcontent = 0;
	return TYPE_LONG;
}