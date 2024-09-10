bool FArchiveXML::LoadSceneNode(FCDObject* object, xmlNode* node)
{ 
	if (!FArchiveXML::LoadEntity(object, node)) return false;

	bool status = true;
	FCDSceneNode* sceneNode = (FCDSceneNode*)object;
	if (!IsEquivalent(node->name, DAE_VSCENE_ELEMENT) && !IsEquivalent(node->name, DAE_NODE_ELEMENT))
	{
		FUError::Error(FUError::ERROR_LEVEL, FUError::ERROR_UNKNOWN_ELEMENT, node->line);
	}

	// Read a subid if we gots one
	fm::string nodeSubId = ReadNodeProperty(node, DAE_SID_ATTRIBUTE);
	sceneNode->SetSubId(nodeSubId);

	// Read in the <node> element's type
	fm::string nodeType = ReadNodeProperty(node, DAE_TYPE_ATTRIBUTE);
	if (nodeType == DAE_JOINT_NODE_TYPE) sceneNode->SetJointFlag(true);
	else if (nodeType.length() == 0 || nodeType == DAE_NODE_NODE_TYPE) {} // No special consideration
	else
	{
		FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_UNKNOW_NODE_ELEMENT_TYPE, node->line);
	}

	// The scene node has ordered elements, so process them directly and in order.
	for (xmlNode* child = node->children; child != NULL; child = child->next)
	{
		if (child->type != XML_ELEMENT_NODE) continue;

		if (IsEquivalent(child->name, DAE_NODE_ELEMENT))
		{
			// Load the child scene node
			FCDSceneNode* node = sceneNode->AddChildNode();
			status = FArchiveXML::LoadSceneNode(node, child);
			if (!status) break;
		}
		// Although this case can be handled by FCDEntityInstanceFactory,
		// we can do some special case handling here.
		else if (IsEquivalent(child->name, DAE_INSTANCE_NODE_ELEMENT))
		{
			FUUri url = ReadNodeUrl(child);
			if (!url.IsFile())
			{
				// cannot find the node
				FCDSceneNode* node = sceneNode->GetDocument()->FindSceneNode(TO_STRING(url.GetFragment()));
				if (node != NULL)
				{
					
					if (!sceneNode->AddChildNode(node))
					{
						FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_CYCLE_DETECTED, child->line);
					}
				}
				else
				{
					FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_INVALID_NODE_INST, child->line);
				}
			}
			else
			{
				FCDEntityInstance* reference = sceneNode->AddInstance(FCDEntity::SCENE_NODE);
				FArchiveXML::LoadEntityInstance(reference, child);
			}
		}
		else if (IsEquivalent(child->name, DAE_EXTRA_ELEMENT)) {} // Handled by FCDEntity.
		else if (IsEquivalent(child->name, DAE_ASSET_ELEMENT)) {} // Handled by FCDEntity.
		else
		{
			uint32 transformType = FArchiveXML::GetTransformType(child);
			if (transformType != (uint32) ~0)
			{
				FCDTransform* transform = sceneNode->AddTransform((FCDTransform::Type) transformType);
				fm::string childSubId = ReadNodeProperty(child, DAE_SID_ATTRIBUTE);
				transform->SetSubId(childSubId);
				status &= (FArchiveXML::LoadSwitch(transform, &transform->GetObjectType(), child));
			}
			else
			{
				uint32 instanceType = FArchiveXML::GetEntityInstanceType(child);
				if (instanceType != (uint32) ~0)
				{
					FCDEntityInstance* instance = sceneNode->AddInstance((FCDEntity::Type) instanceType);
					status &= (FArchiveXML::LoadSwitch(instance, &instance->GetObjectType(), child));
				}
				else
				{
					FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_INVALID_TRANSFORM, child->line);
				}
			}
		}
	}

	status &= FArchiveXML::LoadFromExtraSceneNode(sceneNode);
	sceneNode->SetTransformsDirtyFlag();
	sceneNode->SetDirtyFlag();
	return status;
}		