SharedGameObject SceneSerializer::DeserializedGameObject(XMLReader& reader, IScene* const scene)
{
	SharedGameObject newObject = SharedGameObject(new GameObject(scene));

	std::string currNode = reader.GetCurrentNodeName();

	//Handle game object attributes
	if(reader.NodeHasAttributes())
	{
		std::string currAttr;

		do 
		{
			currAttr = reader.GetCurrentAttributeName();

			if(currAttr == ObjectName)
				newObject->name = reader.GetStringValue(true);

			if(currAttr == ObjectTag)
				newObject->tag = reader.GetStringValue(true);

		} while (reader.MoveToNextAttribute());
	}

	Ogre::Vector3 objectPosition = Ogre::Vector3(0.0f);
	Ogre::Quaternion objectRotation = Ogre::Quaternion::IDENTITY;
	Ogre::Vector3 objectScale = Ogre::Vector3(1.0f);

	if(reader.MoveToChildNode())
	{
		do 
		{
			currNode = reader.GetCurrentNodeName();

			if(currNode == Position)
			{
				if(DeserializeVector3(reader, objectPosition))
					newObject->SetWorldPosition(objectPosition);
			}
			else if(currNode == Rotation)
			{
				if(!DeserializeVector4(reader, objectRotation.x,
					objectRotation.y, objectRotation.z, objectRotation.w))
					printf("Rot Fail\n");
				else
					newObject->SetWorldOrientation(objectRotation);

				bool inheritRot = true;

				if(reader.GetBoolValue(inheritRot, false))
					newObject->SetInheritOrientation(inheritRot);
			}
			else if(currNode == Scale)
			{
				if(DeserializeVector3(reader, objectScale))
					newObject->SetScale(objectScale);

				bool inheritScale = true;

				if(reader.GetBoolValue(inheritScale, false))
					newObject->SetInheritScale(inheritScale);
			}
			//Handle game object components
			else if(currNode == MeshRenderComponen)
				//Not worried about return type because component attaches to game object anyways
					//and errors get logged into Log Manager
						DeserializeMeshRenderComponent(reader, newObject);
			else if(currNode == RigidBodyComponen)
			{
				if(!DeserializeRigidBodyComponent(reader, newObject))
					printf("Rigid Body Failed\n");
			}
			else if(currNode == ParticleComponen)
			{
				DeserializeParticleComponent(reader, newObject);
			}
			else if(currNode == GameObjectNode)
			{
				SharedGameObject childObject = DeserializedGameObject(reader, scene);
				if(childObject)
					newObject->AddChild(childObject);
			}
			
		} while (reader.MoveToNextSiblingNode());
	}

	reader.PopNode();

	newObject->SetWorldTransform(objectPosition, objectRotation, objectScale);

	return newObject;
}