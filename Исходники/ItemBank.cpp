void ItemBank::update() {
	vector<string>items;

	for (vector<Item*>::iterator iter = bank.begin(); iter != bank.end(); iter++) {
		items = updateItem(items, *iter);
	}
	
	DataStorage* dataStorage = dataStorage->getInstance();
	dataStorage->writeToFile(items);

	return;
}