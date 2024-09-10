	Real CMesh::getDistanceToCharacter(CCharacterController* character) {
		Vector3 characterPos = character->getCharacterPosOgre();
		Vector3 thisActorPos; // = NxTools::convert(this->getNxActor()->getGlobalPosition());

		CRender *render = dynamic_cast<CRender*>(getOwnerObject()->getComponent("CRender"));

		if(render)
			thisActorPos = render->getNode()->_getDerivedPosition();
		else
			return 0;

		return thisActorPos.distance(characterPos);
	}