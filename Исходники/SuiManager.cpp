void SuiManager::handleCharacterBuilderSelectItem(CreatureObject* player, SuiBox* suiBox, uint32 cancel, Vector<UnicodeString>* args) {
	ZoneServer* zserv = player->getZoneServer();

	if (args->size() < 1)
		return;

	bool otherPressed = false;
	int index = 0;

	if(args->size() > 1) {
		otherPressed = Bool::valueOf(args->get(0).toString());
		index = Integer::valueOf(args->get(1).toString());
	} else {
		index = Integer::valueOf(args->get(0).toString());
	}

	if (!suiBox->isCharacterBuilderBox())
		return;

	ManagedReference<SuiCharacterBuilderBox*> cbSui = cast<SuiCharacterBuilderBox*>( suiBox);

	CharacterBuilderMenuNode* currentNode = cbSui->getCurrentNode();

	PlayerObject* ghost = player->getPlayerObject();

	//If cancel was pressed then we kill the box/menu.
	if (cancel != 0)
		return;

	//Back was pressed. Send the node above it.
	if (otherPressed) {
		CharacterBuilderMenuNode* parentNode = currentNode->getParentNode();

		if(parentNode == NULL)
			return;

		cbSui->setCurrentNode(parentNode);

		ghost->addSuiBox(cbSui);
		player->sendMessage(cbSui->generateMessage());
		return;
	}

	CharacterBuilderMenuNode* node = currentNode->getChildNodeAt(index);

	//Node doesn't exist or the index was out of bounds. Should probably resend the menu here.
	if (node == NULL) {
		ghost->addSuiBox(cbSui);
		player->sendMessage(cbSui->generateMessage());
		return;
	}

	if (node->hasChildNodes()) {
		//If it has child nodes, display them.
		cbSui->setCurrentNode(node);
		ghost->addSuiBox(cbSui);
		player->sendMessage(cbSui->generateMessage());
	} else {

		String templatePath = node->getTemplatePath();

		if (templatePath.indexOf(".iff") < 0) { // Non-item selections

			if (templatePath == "unlearn_all_skills") {

				SkillManager::instance()->surrenderAllSkills(player);
				player->sendSystemMessage("All skills unlearned.");

			} else if (templatePath == "cleanse_character") {

				if (!player->isInCombat()) {
					player->sendSystemMessage("You have been cleansed from the signs of previous battles.");

					for (int i = 0; i < 9; ++i) {
						player->setWounds(i, 0);
					}

					player->setShockWounds(0);
				} else {
					player->sendSystemMessage("Not within combat.");
				}

			} else if (templatePath == "reset_buffs") {

				if (!player->isInCombat()) {
					player->sendSystemMessage("Your buffs have been reset.");

					player->clearBuffs(true);

					ghost->setFoodFilling(0);
					ghost->setDrinkFilling(0);
				} else {
					player->sendSystemMessage("Not within combat.");
				}

			} else if (templatePath.beginsWith("crafting_apron_")) {

				//"object/tangible/wearables/apron/apron_chef_s01.iff"
				//"object/tangible/wearables/ithorian/apron_chef_jacket_s01_ith.iff"

				uint32 itemCrc = ( player->getSpecies() != CreatureObject::ITHORIAN ) ? 0x5DDC4E5D : 0x6C191FBB;

				ManagedReference<WearableObject*> apron = zserv->createObject(itemCrc, 2).castTo<WearableObject*>();

				if (apron == NULL) {
					player->sendSystemMessage("There was an error creating the requested item. Please contact customer support with this issue.");
					ghost->addSuiBox(cbSui);
					player->sendMessage(cbSui->generateMessage());

					error("could not create frog crafting apron");
					return;
				}

				apron->createChildObjects();

				if (apron->isWearableObject()) {
					uint32 bitmask = apron->getOptionsBitmask() | OptionBitmask::YELLOW;
					apron->setOptionsBitmask(bitmask, false);

					UnicodeString modName = "(General)";
					apron->addSkillMod(SkillModManager::WEARABLE, "general_assembly", 25);
					apron->addSkillMod(SkillModManager::WEARABLE, "general_experimentation", 25);

					if(templatePath == "crafting_apron_armorsmith") {
						modName = "(Armorsmith)";
						apron->addSkillMod(SkillModManager::WEARABLE, "armor_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "armor_experimentation", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "armor_repair", 25);
					} else if(templatePath == "crafting_apron_weaponsmith") {
						modName = "(Weaponsmith)";
						apron->addSkillMod(SkillModManager::WEARABLE, "weapon_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "weapon_experimentation", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "weapon_repair", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "grenade_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "grenade_experimentation", 25);
					} else if(templatePath == "crafting_apron_tailor") {
						modName = "(Tailor)";
						apron->addSkillMod(SkillModManager::WEARABLE, "clothing_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "clothing_experimentation", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "clothing_repair", 25);
					} else if(templatePath == "crafting_apron_chef") {
						modName = "(Chef)";
						apron->addSkillMod(SkillModManager::WEARABLE, "food_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "food_experimentation", 25);
					} else if(templatePath == "crafting_apron_architect") {
						modName = "(Architect)";
						apron->addSkillMod(SkillModManager::WEARABLE, "structure_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "structure_experimentation", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "structure_complexity", 25);
					} else if(templatePath == "crafting_apron_droid_engineer") {
						modName = "(Droid Engineer)";
						apron->addSkillMod(SkillModManager::WEARABLE, "droid_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "droid_experimentation", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "droid_complexity", 25);
					} else if(templatePath == "crafting_apron_doctor") {
						modName = "(Doctor)";
						apron->addSkillMod(SkillModManager::WEARABLE, "medicine_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "medicine_experimentation", 25);
					} else if(templatePath == "crafting_apron_combat_medic") {
						modName = "(Combat Medic)";
						apron->addSkillMod(SkillModManager::WEARABLE, "combat_medicine_assembly", 25);
						apron->addSkillMod(SkillModManager::WEARABLE, "combat_medicine_experimentation", 25);
					}

					UnicodeString apronName = "Crafting Apron " + modName;
					apron->setCustomObjectName(apronName, false);
				}

				ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
				apron->sendTo(player, true);
				inventory->transferObject(apron, -1, true);

				StringIdChatParameter stringId;
				stringId.setStringId("@faction_perk:bonus_base_name"); //You received a: %TO.
				stringId.setTO(apron);
				player->sendSystemMessage(stringId);

			} else if (templatePath == "enhance_character") {

				ManagedReference<SceneObject*> scob = cbSui->getUsingObject();
				if (scob != NULL) {

					if (scob->getGameObjectType() == SceneObjectType::CHARACTERBUILDERTERMINAL) {
						CharacterBuilderTerminal* bluefrog = cast<CharacterBuilderTerminal*>( scob.get());
						bluefrog->enhanceCharacter(player);
					}
				}

			} else if (templatePath == "credits") {

				player->addCashCredits(50000, true);
				player->sendSystemMessage("You have received 50.000 Credits");

			} else if (templatePath == "faction_rebel") {

				ghost->increaseFactionStanding("rebel", 100000);

			} else if (templatePath == "faction_imperial") {

				ghost->increaseFactionStanding("imperial", 100000);

			} else if (templatePath == "language") {

				ManagedReference<SceneObject*> scob = cbSui->getUsingObject();
				if (scob != NULL) {

					if (scob->getGameObjectType() == SceneObjectType::CHARACTERBUILDERTERMINAL) {
						CharacterBuilderTerminal* bluefrog = cast<CharacterBuilderTerminal*>( scob.get());
						bluefrog->giveLanguages(player);
					}
				}

			} else if (templatePath == "apply_dots") {
				ManagedReference<SceneObject*> scob = cbSui->getUsingObject();
				player->addDotState(CreatureState::POISONED, scob->getObjectID(), 100, CreatureAttribute::HEALTH, 60, 80, 0);
				player->addDotState(CreatureState::BLEEDING, scob->getObjectID(), 100, CreatureAttribute::ACTION, 60, 80, 0);
				player->addDotState(CreatureState::DISEASED, scob->getObjectID(), 100, CreatureAttribute::ACTION, 60, 80, 0);
				player->addDotState(CreatureState::ONFIRE, scob->getObjectID(), 100, CreatureAttribute::HEALTH, 60, 80, 0);
			} else if (templatePath == "clear_dots") {
				player->clearDots();
			} else if (templatePath == "max_xp") {
				ghost->maximizeExperience();
				player->sendSystemMessage("You have maximized all xp types.");
			} else {

				if (templatePath.length() > 0) {

					SkillManager::instance()->awardSkill(templatePath, player, true, true, true);
					if (player->hasSkill(templatePath))
						player->sendSystemMessage("You have learned a skill.");

				} else {

					player->sendSystemMessage("Unknown selection.");

				}
			}

			ghost->addSuiBox(cbSui);
			player->sendMessage(cbSui->generateMessage());
		} else { // Items

			if (templatePath.contains("event_perk")) {
				if (ghost->getEventPerkCount() >= 5) {
					player->sendSystemMessage("@event_perk:pro_too_many_perks"); // You cannot rent any more items right now.
					ghost->addSuiBox(cbSui);
					player->sendMessage(cbSui->generateMessage());
					return;
				}
			}

			ManagedReference<SceneObject*> item = zserv->createObject(node->getTemplateCRC(), 1);

			if (item == NULL) {
				player->sendSystemMessage("There was an error creating the requested item. Please contact customer support with this issue.");
				ghost->addSuiBox(cbSui);
				player->sendMessage(cbSui->generateMessage());

				error("could not create frog item: " + node->getDisplayName());
				return;
			}

			item->createChildObjects();

			if (item->isEventPerkDeed()) {
				EventPerkDeed* deed = cast<EventPerkDeed*>(item.get());
				deed->setOwner(player);
				ghost->addEventPerk(deed);
			}

			ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
			item->sendTo(player, true);
			inventory->transferObject(item, -1, true);

			StringIdChatParameter stringId;
			stringId.setStringId("@faction_perk:bonus_base_name"); //You received a: %TO.
			stringId.setTO(item);
			player->sendSystemMessage(stringId);

			ghost->addSuiBox(cbSui);
			player->sendMessage(cbSui->generateMessage());
		}
	}
}