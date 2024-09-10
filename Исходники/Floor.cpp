Floor *Floor::create(int ID, CCString *name, int floorNumber, bool transferRight, bool transferLeft){
	Floor *f = new Floor(ID, name, floorNumber, transferRight, transferLeft);
	f->autorelease();
	
	if(!arrayFloors){
		arrayFloors = CCDictionary::create();
		arrayFloors->retain();
	}
		
	arrayFloors->setObject(f, ID);
    return f;
}