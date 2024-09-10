void AGOSEngine_Elvira2::oe2_drawItem() {
	// 113: draw item
	Item *i = getNextItemPtr();
	int a = getVarOrByte();
	int x = getVarOrWord();
	int y = getVarOrWord();
	mouseOff();
	drawIcon(_windowArray[a % 8], itemGetIconNumber(i), x, y);
	mouseOn();
}