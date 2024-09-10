void AdminAccomLocations::loadLocations(QMultiMap<QString, SaverDbAccomLocations> loc) {

	// Remove the currently existing islands
	foreach(int k, allItemsBNB.keys()) {
		allItemsBNB.value(k)->hide();
		delete allItemsBNB.value(k);

		allDelsBNB.value(k)->hide();
		delete allDelsBNB.value(k);
	}
	allItemsBNB.clear();
	allDelsBNB.clear();
	foreach(int k, allItemsHOSTEL.keys()) {
		allItemsHOSTEL.value(k)->hide();
		delete allItemsHOSTEL.value(k);

		allDelsHOSTEL.value(k)->hide();
		delete allDelsHOSTEL.value(k);
	}
	allItemsHOSTEL.clear();
	allDelsHOSTEL.clear();


	QMapIterator<QString,SaverDbAccomLocations> iter(loc);
	while(iter.hasNext()) {
		iter.next();



		// the lineedit to edit the island name
		QLineEdit *item = new QLineEdit;
		item->setStyleSheet("font-size: 10pt; font-weight: bold");
		item->setText(iter.value().name);

		int pos = (QDateTime::currentMSecsSinceEpoch()%qrand())*(iter.key() == "bnb" ? allItemsBNB.keys().count() : allItemsHOSTEL.keys().count());

		// Delete an island
		QPushButton *del = new QPushButton("X");
		del->setFixedWidth(40);
		del->setCursor(Qt::PointingHandCursor);
		del->setStyleSheet("font-weight: bold; color: red");
		// Deleting an island will do some special stuff (see deleteItem())
		QSignalMapper *mapper = new QSignalMapper;
		mapper->setMapping(del,pos);
		connect(del, SIGNAL(clicked()), mapper, SLOT(map()));
		connect(mapper, SIGNAL(mapped(int)), this, SLOT(deleteItem(int)));

		// Put lineedit and pushbutton into a horizontal layout
		QHBoxLayout *itemLay = new QHBoxLayout;
		itemLay->addWidget(item);
		itemLay->addWidget(del);

		if(iter.key() == "bnb") {

			// Add set to scroll area layout
			layBNB->insertLayout(layBNB->count()-1,itemLay);

			// And store items for later use
			allItemsBNB.insert(pos,item);
			allDelsBNB.insert(pos,del);

		} else {

			// Add set to scroll area layout
			layHOSTEL->insertLayout(layHOSTEL->count()-1,itemLay);

			// And store items for later use
			allItemsHOSTEL.insert(pos,item);
			allDelsHOSTEL.insert(pos,del);

		}

	}

}