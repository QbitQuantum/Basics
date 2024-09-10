void ChangeDisplay::addArrow(Ogre::Vector3 from, Ogre::Vector3 to, int r, int g, int b) {
	Ogre::SceneNode* frame_node = scene_node_->createChildSceneNode();
	ArrowPtr arrow(new Arrow(context_->getSceneManager(), frame_node));
	arrow->setColor(255.0, 0, 0, 1.0);
	arrow->setPosition(from);
	Ogre::Vector3 direct = to - from;
	float length = direct.length();
	arrow->setDirection(direct);
	arrow->setScale(Ogre::Vector3(length*0.8, length, length));

	frame_node->setPosition(position);
	frame_node->setOrientation(orientation);

	arrows.push_back(arrow);
}