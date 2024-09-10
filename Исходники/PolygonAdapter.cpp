void PolygonAdapter::createNewPolygon(WFMath::Polygon<2>* existingPoly)
{
	delete mPolygon;
	mPolygon = 0;
	Ogre::SceneNode* entitySceneNode = getEntitySceneNode();
	if (entitySceneNode) {
		mPolygon = new Authoring::Polygon(entitySceneNode, mPositionProvider);
		WFMath::Polygon<2> poly;
		if (existingPoly) {
			poly = *existingPoly;
		} else {
			poly.addCorner(0, WFMath::Point<2>(-1, -1));
			poly.addCorner(1, WFMath::Point<2>(-1, 1));
			poly.addCorner(2, WFMath::Point<2>(1, 1));
			poly.addCorner(3, WFMath::Point<2>(1, -1));
		}

		mPolygon->loadFromShape(poly);
		if (!mPickListener) {
			mPickListener = new Authoring::PolygonPointPickListener(*mPolygon);
			mPickListener->EventPickedPoint.connect(sigc::mem_fun(*this, &PolygonAdapter::pickListener_PickedPoint));
			EmberOgre::getSingleton().getWorld()->getMainCamera().pushWorldPickListener(mPickListener);
		}
	}

}