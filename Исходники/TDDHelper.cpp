void TDDHelper::addTestButton(Node *parent, Point pos)
{
	if(HAS_TDD == false) {
		log("ERROR: TDD Framework is disable!");
		return;
	}
	
	
	if(parent == NULL) {
		log("ERROR: addTestButton: parent is NULL");		// or use Assert
		return;
	}
	
	Menu *menu = createMenu(pos, "Test!", [](Ref *sender) {
												TDDHelper::showTests();
											}
							);
	
	parent->addChild(menu);
}