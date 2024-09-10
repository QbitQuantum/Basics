void ItemController::spawnCrates(int level, Game *gamePtr) {
	std::list<VECTOR2>* crateLocations = levelCrateLoc[0];
	int locCounter = 0;
	for (std::list<VECTOR2>::iterator crateLocationIter = crateLocations->begin(); crateLocationIter != crateLocations->end(); ++crateLocationIter) {
		locCounter++;
		int itemCounter = 0;
		std::list<int>* crateItem = levelCrateItemType[0];
		for (std::list<int>::iterator crateItemTypeIter = crateItem->begin(); crateItemTypeIter != crateItem->end(); ++crateItemTypeIter) {
			itemCounter++;
			if (locCounter == itemCounter) {
				Crate* c = new Crate();
				int itemtype = (*crateItemTypeIter);
				c->initialize(gamePtr, itemTexture, itemtype);
				c->setX((*crateLocationIter).x);
				c->setY((*crateLocationIter).y);
				crateList->push_back(c);

				//Create Crate Icon
				Image* itemIco = new Image();
				itemIco->initialize(graphics, itemControllerNS::ICO_TEXTURE_SIZE, itemControllerNS::ICO_TEXTURE_SIZE, 1, itemIconTexture);
				itemIco->setCurrentFrame(1);
				itemIco->setScale(0.5);
				itemIco->setX(GAME_WIDTH*0.6);
				itemIco->setY(50);
				crateIcons.push_back(itemIco);
			}
		}
	}
}