void CraftingSessionImplementation::initialAssembly(int clientCounter) {
	ManagedReference<CraftingTool*> craftingTool = this->craftingTool.get();
	ManagedReference<CreatureObject*> crafter = this->crafter.get();
	ManagedReference<PlayerObject*> crafterGhost = this->crafterGhost.get();
	ManagedReference<CraftingStation*> craftingStation = this->craftingStation.get();
	ManagedReference<ManufactureSchematic*> manufactureSchematic = this->manufactureSchematic.get();
	ManagedReference<TangibleObject*> prototype = this->prototype.get();
	// Get the appropriate number of Experimentation points from Skill
	ManagedReference<DraftSchematic*> draftSchematic = manufactureSchematic->getDraftSchematic();

	// Set crafter
	manufactureSchematic->setCrafter(crafter);

	String expskill = draftSchematic->getExperimentationSkill();
	experimentationPointsTotal = int(crafter->getSkillMod(expskill) / 10);
	experimentationPointsUsed = 0;

	// Calculate exp failure for red bars
	int experimentalFailureRate = craftingManager.get()->calculateExperimentationFailureRate(crafter, manufactureSchematic, 0);

	// Get the level of customization
	String custskill = draftSchematic->getCustomizationSkill();
	int custpoints = int(crafter->getSkillMod(custskill));

	// Determine the outcome of the craft, Amazing through Critical
	assemblyResult = craftingManager.get()->calculateAssemblySuccess(crafter,
			draftSchematic, craftingTool->getEffectiveness());

	Locker locker(prototype);
	//Set initial crafting percentages
	craftingManager.get()->setInitialCraftingValues(prototype,manufactureSchematic,assemblyResult);
	//prototype->setInitialCraftingValues(manufactureSchematic, assemblyResult);

	Reference<CraftingValues*> craftingValues = manufactureSchematic->getCraftingValues();
	craftingValues->setManufactureSchematic(manufactureSchematic);
	craftingValues->setPlayer(crafter);

	for (int i = 0; i < manufactureSchematic->getSlotCount(); ++i) {

		ComponentSlot* compSlot = cast<ComponentSlot*>(manufactureSchematic->getSlot(i));
		if (compSlot == NULL)
			continue;

		ManagedReference<TangibleObject*> tano = compSlot->getPrototype();
		if (tano == NULL)
			continue;

		// we know that we can only have one component per hardpoint slot, so don't worry about checking them
		ComponentMapEntry entry = ComponentMap::instance()->get(tano->getClientObjectCRC());
		if (entry.getId() > 0)
			prototype->addVisibleComponent(entry.getId(), false);
	}

	if (prototype->getVisibleComponents() != NULL && prototype->getVisibleComponents()->size() > 0) {
		prototype->sendDestroyTo(crafter);
		prototype->sendTo(crafter, true);
	}

	// Flag to get the experimenting window
	if (craftingStation != NULL && (craftingValues->getVisibleExperimentalPropertyTitleSize() > 0 || manufactureSchematic->allowFactoryRun()))
		// Assemble with Experimenting
		state = 3;

	else
		// Assemble without Experimenting
		state = 4;

	// Start DPLAY9 ***********************************************************
	// Updates the stage of crafting, sets the number of experimentation points
	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(crafter->getPlayerObject());
	dplay9->setCraftingState(state); // 3 If Experimenting is active, 4 if already experimented/ No experimenting
	dplay9->setExperimentationPoints(experimentationPointsTotal);
	dplay9->close();

	crafter->sendMessage(dplay9);
	// End DPLAY9 *************************************************************

	// Set Crafter name and generate serial number
	String name = crafter->getFirstName();
	prototype->setCraftersName(name);

	String serial = craftingManager.get()->generateSerial();
	prototype->setSerialNumber(serial);

	// Update the prototype with new values
	prototype->updateCraftingValues(craftingValues, true);

	addSkillMods();

	addWeaponDots();

	// Set default customization
	SharedTangibleObjectTemplate* templateData =
			cast<SharedTangibleObjectTemplate*>(prototype->getObjectTemplate());
	if (templateData == NULL) {
		error("No template for: " + String::valueOf(prototype->getServerObjectCRC()));
		return;
	}

	AssetCustomizationManagerTemplate::instance()->getCustomizationVariables(templateData->getAppearanceFilename().hashCode(), variables, true);

	for (int i = 0; i < variables.size(); ++i) {
		Reference<RangedIntCustomizationVariable*> var = cast<RangedIntCustomizationVariable*>(variables.get(i).get());
		if(var != NULL) {
			prototype->setCustomizationVariable(variables.elementAt(i).getKey(), var->getDefaultValue());
		}
	}

	prototype->setComplexity(manufactureSchematic->getComplexity());

	// Start DMSCO3 ***********************************************************
	// Sends the updated values to the crafting screen
	ManufactureSchematicObjectDeltaMessage3* dMsco3 =
			new ManufactureSchematicObjectDeltaMessage3(manufactureSchematic);
	dMsco3->updateCraftingValues(manufactureSchematic);
	dMsco3->updateComplexity(manufactureSchematic->getComplexity());

	dMsco3->close();

	crafter->sendMessage(dMsco3);
	// End DMSCO3 *************************************************************

	// Start DMSCO7 ***********************************************************
	// Sends the experimental properties and experimental percentages
	ManufactureSchematicObjectDeltaMessage7* dMsco7 =
			new ManufactureSchematicObjectDeltaMessage7(manufactureSchematic);

	dMsco7->updateForAssembly(manufactureSchematic, experimentalFailureRate);
	if (custpoints > 0)
		dMsco7->updateCustomizationOptions(&variables, custpoints);

	dMsco7->close();

	crafter->sendMessage(dMsco7);
	// End DMSCO7 *************************************************************

	// Start DTANO3 ***********************************************************
	// Updates the Complexity and the condition
	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(
			prototype);
	dtano3->updateComplexity();
	dtano3->updateMaxCondition();
	dtano3->close();

	crafter->sendMessage(dtano3);
	// End DTANO3 *************************************************************


	// Start Object Controller *******************************************
	// Send the results
	ObjectControllerMessage* objMsg = new ObjectControllerMessage(
			crafter->getObjectID(), 0x1B, 0x01BE);
	objMsg->insertInt(0x109);

	objMsg->insertInt(assemblyResult); // Assembly Results

	objMsg->insertByte(clientCounter);

	crafter->sendMessage(objMsg);
	// End Object Controller ******************************************

	crafter->notifyObservers(ObserverEventType::CRAFTINGASSEMBLY, crafter, 0);

	// Remove all resources - Not recovering them
	if (assemblyResult == CraftingManager::CRITICALFAILURE) {

		createPrototypeObject(draftSchematic);

		state = 2;

		// re-setup the slots and ingredients
		manufactureSchematic->synchronizedUIListen(crafter, 0);

		// Start Dplay9 **************************************
		// Reset crafting state
		PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(
				crafter->getPlayerObject());
		dplay9->setExperimentationPoints(0xFFFFFFFF);
		dplay9->setCraftingState(state);

		dplay9->close();

		crafter->sendMessage(dplay9);
		// End DPLAY9 ****************************************

	} else {

		crafterGhost->decreaseSchematicUseCount(draftSchematic);

	}

	if(crafterGhost != NULL && crafterGhost->getDebug()) {
		crafter->sendSystemMessage(craftingValues->toString());
	}
}