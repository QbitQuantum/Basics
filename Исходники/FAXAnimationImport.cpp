bool FArchiveXML::LoadAnimationClip(FCDObject* object, xmlNode* clipNode)
{ 
	FCDAnimationClip* animationClip = (FCDAnimationClip*)object;

	bool status = FArchiveXML::LoadEntity(animationClip, clipNode);
	if (!status) return status;
	if (!IsEquivalent(clipNode->name, DAE_ANIMCLIP_ELEMENT))
	{
		FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_UNKNOWN_ANIM_LIB_ELEMENT, clipNode->line);
		return status;
	}

	// Read in and verify the clip's time/input bounds
	animationClip->SetStart(FUStringConversion::ToFloat(ReadNodeProperty(clipNode, DAE_START_ATTRIBUTE)));
	animationClip->SetEnd(FUStringConversion::ToFloat(ReadNodeProperty(clipNode, DAE_END_ATTRIBUTE)));
	if (animationClip->GetEnd() - animationClip->GetStart() < FLT_TOLERANCE)
	{
		FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_INVALID_SE_PAIR, clipNode->line);
	}

	// Read in the <input> elements and segment the corresponding animation curves
	xmlNodeList inputNodes;
	FindChildrenByType(clipNode, DAE_INSTANCE_ANIMATION_ELEMENT, inputNodes);
	for (xmlNodeList::iterator itI = inputNodes.begin(); itI != inputNodes.end(); ++itI)
	{
		FCDEntityInstance* animationInstance = animationClip->AddInstanceAnimation();
		if (!LoadSwitch(animationInstance, &animationInstance->GetObjectType(), *itI))
		{
			SAFE_DELETE(animationInstance);
			continue;
		}

		fm::string name = ReadNodeProperty(*itI, DAE_NAME_ATTRIBUTE);
		animationClip->SetAnimationName(name, animationClip->GetAnimationCount() - 1);
	}

	// Check for an empty clip
	if (animationClip->GetClipCurves().empty())
	{
		FUError::Error(FUError::WARNING_LEVEL, FUError::WARNING_EMPTY_ANIM_CLIP, clipNode->line);
	}

	animationClip->SetDirtyFlag();
	return status;
}		