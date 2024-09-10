bool Rocket::Straw::touchEvent(Touch::TouchEvent evt, int x, int y, unsigned int contactIndex) {
	Project::Element::touchEvent(evt, x, y, contactIndex);
	switch(evt) {
		case Touch::TOUCH_PRESS: {
			Rocket *rocket = (Rocket*)_project;
			MyNode *node = getNode();
			if(rocket->getTouchNode() == node) {
				Vector3 trans = rocket->getTouchPoint() - node->getTranslationWorld();
				Matrix straw = node->getWorldMatrix(), strawInv;
				straw.invert(&strawInv);
				strawInv.transformVector(&trans);
				float scale = ((rocket->_strawLength/2 - trans.z) / rocket->_strawLength) * node->getScaleZ();
				node->setScaleZ(scale);
				rocket->_strawLength = rocket->_originalStrawLength * scale;
			}
		}
	}
}