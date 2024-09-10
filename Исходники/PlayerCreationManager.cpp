bool PlayerCreationManager::createCharacter(ClientCreateCharacterCallback* callback) {
	TemplateManager* templateManager = TemplateManager::instance();

	ZoneClientSession* client = callback->getClient();

	if (client->getCharacterCount(zoneServer.get()->getGalaxyID()) >= 10) {
		ErrorMessage* errMsg = new ErrorMessage("Create Error", "You are limited to 10 characters per galaxy.", 0x0);
		client->sendMessage(errMsg);

		return false;
	}

	PlayerManager* playerManager = zoneServer.get()->getPlayerManager();

	SkillManager* skillManager = SkillManager::instance();

	//Get all the data and validate it.
	UnicodeString characterName;
	callback->getCharacterName(characterName);

	//TODO: Replace this at some point?
	if (!playerManager->checkPlayerName(callback))
		return false;

	String raceFile;
	callback->getRaceFile(raceFile);

	uint32 serverObjectCRC = raceFile.hashCode();

	PlayerCreatureTemplate* playerTemplate =
			dynamic_cast<PlayerCreatureTemplate*>(templateManager->getTemplate(
					serverObjectCRC));

	if (playerTemplate == NULL) {
		error("Unknown player template selected: " + raceFile);
		return false;
	}

	String fileName = playerTemplate->getTemplateFileName();
	String clientTemplate = templateManager->getTemplateFile(
			playerTemplate->getClientObjectCRC());

	RacialCreationData* raceData = racialCreationData.get(fileName);

	if (raceData == NULL)
		raceData = racialCreationData.get(0); //Just get the first race, since they tried to create a race that doesn't exist.

	String profession, customization, hairTemplate, hairCustomization;
	callback->getSkill(profession);

	if (profession.contains("jedi"))
		profession = "crafting_artisan";

	callback->getCustomizationString(customization);
	callback->getHairObject(hairTemplate);
	callback->getHairCustomization(hairCustomization);

	float height = callback->getHeight();
	height = MAX(MIN(height, playerTemplate->getMaxScale()),
			playerTemplate->getMinScale());

	//validate biography
	UnicodeString bio;
	callback->getBiography(bio);

	bool doTutorial = callback->getTutorialFlag();
	//bool doTutorial = false;

	ManagedReference<CreatureObject*> playerCreature =
			zoneServer.get()->createObject(
					serverObjectCRC, 2).castTo<CreatureObject*>();

	if (playerCreature == NULL) {
		error("Could not create player with template: " + raceFile);
		return false;
	}

	Locker playerLocker(playerCreature);

	playerCreature->createChildObjects();
	playerCreature->setHeight(height);
	playerCreature->setCustomObjectName(characterName, false); //TODO: Validate with Name Manager.

	client->setPlayer(playerCreature);
	playerCreature->setClient(client);

	// Set starting cash and starting bank
	playerCreature->setCashCredits(startingCash, false);
	playerCreature->setBankCredits(startingBank, false);

	ManagedReference<PlayerObject*> ghost = playerCreature->getPlayerObject();

	if (ghost != NULL) {
		//Set skillpoints before adding any skills.
		ghost->setSkillPoints(skillPoints);
		ghost->setStarterProfession(profession);
	}

	addCustomization(playerCreature, customization,
			playerTemplate->getAppearanceFilename());
	addHair(playerCreature, hairTemplate, hairCustomization);
	if (!doTutorial) {
		addProfessionStartingItems(playerCreature, profession, clientTemplate,
				false);
		addStartingItems(playerCreature, clientTemplate, false);
		addRacialMods(playerCreature, fileName,
				playerTemplate->getStartingSkills(),
				playerTemplate->getStartingItems(), false);
	} else {
		addProfessionStartingItems(playerCreature, profession, clientTemplate,
				true);
		addStartingItems(playerCreature, clientTemplate, true);
		addRacialMods(playerCreature, fileName,
				playerTemplate->getStartingSkills(),
				playerTemplate->getStartingItems(), true);
	}

	// Set starting cash and starting bank
	playerCreature->setCashCredits(startingCash, false);
	playerCreature->setBankCredits(startingBank, false);

	if (ghost != NULL) {

		ghost->setAccountID(client->getAccountID());

		if (!freeGodMode) {
			try {
				uint32 accID = client->getAccountID();

				ManagedReference<Account*> playerAccount = playerManager->getAccount(accID);

				if (playerAccount == NULL) {
					playerCreature->destroyPlayerCreatureFromDatabase(true);
					return false;
				}

				int accountPermissionLevel = playerAccount->getAdminLevel();
				String accountName = playerAccount->getUsername();

				if(accountPermissionLevel > 0 && (accountPermissionLevel == 9 || accountPermissionLevel == 10 || accountPermissionLevel == 12 || accountPermissionLevel == 15)) {
					playerManager->updatePermissionLevel(playerCreature, accountPermissionLevel);

					/*
					Reference<ShipControlDevice*> shipControlDevice = zoneServer->createObject(STRING_HASHCODE("object/intangible/ship/sorosuub_space_yacht_pcd.iff"), 1).castTo<ShipControlDevice*>();
					//ShipObject* ship = (ShipObject*) server->createObject(STRING_HASHCODE("object/ship/player/player_sorosuub_space_yacht.iff"), 1);
					Reference<ShipObject*> ship = zoneServer->createObject(STRING_HASHCODE("object/ship/player/player_basic_tiefighter.iff"), 1).castTo<ShipObject*>();

					shipControlDevice->setControlledObject(ship);

					if (!shipControlDevice->transferObject(ship, 4))
						info("Adding of ship to device failed");

					ManagedReference<SceneObject*> datapad = playerCreature->getSlottedObject("datapad");

					if (datapad != NULL) {
						if (!datapad->transferObject(shipControlDevice, -1)) {
							shipControlDevice->destroyObjectFromDatabase(true);
						}
					} else {
						shipControlDevice->destroyObjectFromDatabase(true);
						error("could not get datapad from player");
					}
					*/
				}

				if (accountPermissionLevel < 9) {
					try {
						StringBuffer query;
						//query << "SELECT UNIX_TIMESTAMP(creation_date) FROM characters c WHERE galaxy_id = " << zoneServer.get()->getGalaxyID() << " AND account_id = " << client->getAccountID() << " ORDER BY creation_date desc;";
						uint32 galaxyId = zoneServer.get()->getGalaxyID();
						uint32 accountId = client->getAccountID();
						query << "(SELECT UNIX_TIMESTAMP(c.creation_date) as t FROM characters as c WHERE c.account_id = " << accountId << " AND c.galaxy_id = " << galaxyId << " ORDER BY c.creation_date DESC) UNION (SELECT UNIX_TIMESTAMP(d.creation_date) FROM deleted_characters as d WHERE d.account_id = " << accountId << " AND d.galaxy_id = " << galaxyId << " ORDER BY d.creation_date DESC) ORDER BY t DESC LIMIT 1";

						Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);

						if (res != NULL && res->next()) {
							uint32 sec = res->getUnsignedInt(0);

							Time timeVal(sec);

							if (timeVal.miliDifference() < 3600000) {
								ErrorMessage* errMsg = new ErrorMessage("Create Error", "You are only permitted to create one character per hour. Repeat attempts prior to 1 hour elapsing will reset the timer.", 0x0);
								client->sendMessage(errMsg);

								playerCreature->destroyPlayerCreatureFromDatabase(true);
								return false;
							}
							//timeVal.se
						}
					} catch (DatabaseException& e) {
						error(e.getMessage());
					}

					Locker locker(&charCountMutex);

					if (lastCreatedCharacter.containsKey(accID)) {
						Time lastCreatedTime = lastCreatedCharacter.get(accID);

						if (lastCreatedTime.miliDifference() < 3600000) {
							ErrorMessage* errMsg = new ErrorMessage("Create Error", "You are only permitted to create one character per hour. Repeat attempts prior to 1 hour elapsing will reset the timer.", 0x0);
							client->sendMessage(errMsg);

							playerCreature->destroyPlayerCreatureFromDatabase(true);
							return false;
						} else {
							lastCreatedTime.updateToCurrentTime();

							lastCreatedCharacter.put(accID, lastCreatedTime);
						}
					} else {
						lastCreatedCharacter.put(accID, Time());
					}
				}

			} catch (Exception& e) {
				error(e.getMessage());
			}
		} else {
			playerManager->updatePermissionLevel(playerCreature, PermissionLevelList::instance()->getLevelNumber("admin"));
		}

		if (doTutorial)
			playerManager->createTutorialBuilding(playerCreature);
		else
			playerManager->createSkippedTutorialBuilding(playerCreature);

		ValidatedPosition* lastValidatedPosition =
				ghost->getLastValidatedPosition();
		lastValidatedPosition->update(playerCreature);

		ghost->setBiography(bio);

		ghost->setLanguageID(playerTemplate->getDefaultLanguage());
	}

	ClientCreateCharacterSuccess* msg = new ClientCreateCharacterSuccess(
			playerCreature->getObjectID());
	playerCreature->sendMessage(msg);

	ChatManager* chatManager = zoneServer.get()->getChatManager();
	chatManager->addPlayer(playerCreature);

	String firstName = playerCreature->getFirstName();
	String lastName = playerCreature->getLastName();
	int raceID = playerTemplate->getRace();

	try {
		StringBuffer query;
		query
				<< "INSERT INTO `characters_dirty` (`character_oid`, `account_id`, `galaxy_id`, `firstname`, `surname`, `race`, `gender`, `template`)"
				<< " VALUES (" << playerCreature->getObjectID() << ","
				<< client->getAccountID() << "," << zoneServer.get()->getGalaxyID()
				<< "," << "'" << firstName.escapeString() << "','"
				<< lastName.escapeString() << "'," << raceID << "," << 0 << ",'"
				<< raceFile.escapeString() << "')";

		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}

	playerManager->addPlayer(playerCreature);

	// Copy claimed veteran rewards from player's alt character
	uint32 accID = client->getAccountID();
	ManagedReference<Account*> playerAccount = playerManager->getAccount(accID);
	if (playerAccount != NULL && ghost != NULL) {

		// Find the first alt character
		ManagedReference<CreatureObject*> altPlayer = NULL;
		CharacterList* characters = playerAccount->getCharacterList();
		for(int i = 0; i < characters->size(); ++i) {
			CharacterListEntry* entry = &characters->get(i);
			if(entry->getGalaxyID() == zoneServer.get()->getGalaxyID() &&
		       entry->getFirstName() != playerCreature->getFirstName() ) {

				altPlayer = playerManager->getPlayer(entry->getFirstName());
				if( altPlayer != NULL ){
					break;
				}
			}
		}

		// Record the rewards if alt player was found
		if( altPlayer != NULL && altPlayer->getPlayerObject() != NULL){

			Locker alocker( altPlayer );
			for( int i = 0; i < playerManager->getNumVeteranRewardMilestones(); i++ ){
				int milestone = playerManager->getVeteranRewardMilestone(i);
				String claimedReward = altPlayer->getPlayerObject()->getChosenVeteranReward(milestone);
				if( !claimedReward.isEmpty() ){
					ghost->addChosenVeteranReward(milestone,claimedReward);
				}
			}
		}
	}

	client->addCharacter(playerCreature->getObjectID(), zoneServer.get()->getGalaxyID());

	JediManager::instance()->onPlayerCreated(playerCreature);

	chatManager->sendMail("system", "@newbie_tutorial/newbie_mail:welcome_subject", "@newbie_tutorial/newbie_mail:welcome_body", playerCreature->getFirstName());

	//Join auction chat room
	ghost->addChatRoom(chatManager->getAuctionRoom()->getRoomID());

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(playerCreature, SuiWindowType::NONE);
	box->setPromptTitle("PLEASE NOTE");
	box->setPromptText("You are limited to creating one character per hour. Attempting to create another character or deleting your character before the 1 hour timer expires will reset the timer.");

	ghost->addSuiBox(box);
	playerCreature->sendMessage(box->generateMessage());

	return true;
}