	void CSObject::setIdRecursive(ISceneNode* node, int id)
	{
		if (node)
		{
			// set the data
			node->setID(getObjectType());
			node->setName(intToStringc(id));
			// edited
			// set all the children also
			list<ISceneNode*> list = node->getChildren();
			core::list<ISceneNode*>::Iterator Iterator;
			for (Iterator = list.begin(); Iterator != list.end(); ++Iterator)
			{
				setIdRecursive((*Iterator), id);
			}

		}

	}