void SuDoKuLayer::closeCallback(CCObject * pSender) {
	Menu* menu = Menu::node();
	if (menu) {
		menu->setMenu(2);
		CCDirector::sharedDirector()->replaceScene(menu);
	}
}