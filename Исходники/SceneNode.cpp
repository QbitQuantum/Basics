void SceneNode::Update(float32 timeElapsed)
{
    inUpdate = true;
	// TODO - move node update to render because any of objects can change params of other objects
	if (nodeAnimations.size() != 0)
	{
		Quaternion blendedRotation;
		Vector3 blendedTranslation;
		float32 accumWeight = 0.0f;
		std::deque<SceneNodeAnimation*>::const_iterator end = nodeAnimations.end();
		for (std::deque<SceneNodeAnimation*>::iterator it = nodeAnimations.begin(); it != end; ++it)
		{
			SceneNodeAnimation * animation = *it;
			SceneNodeAnimationKey & key = animation->Intepolate(animation->GetCurrentTime());
			if (accumWeight == 0.0f)
			{
				blendedTranslation = key.translation;
				blendedRotation = key.rotation;
				accumWeight = animation->weight;
			}else
			{
				float32 factor = animation->weight / (accumWeight + animation->weight);
				accumWeight += accumWeight;
				blendedTranslation.Lerp(blendedTranslation, key.translation, factor);
				blendedRotation.Slerp(blendedRotation, key.rotation, factor);
			}
			//key.GetMatrix(localTransform);
		}
		Matrix4 localTransformTrans;
		Matrix4 localTransformRot;
		Matrix4 localTransformFinal;
		localTransformTrans.CreateTranslation(blendedTranslation);
		localTransformRot = blendedRotation.GetMatrix();
		
		localTransform = localTransformRot * localTransformTrans;
		
//		if (nodeAnimations.size() != 1)
//		{
//			printf("-- blended node: %s\n", name.c_str());
//			std::deque<SceneNodeAnimation*>::const_iterator end = nodeAnimations.end();
//			for (std::deque<SceneNodeAnimation*>::iterator it = nodeAnimations.begin(); it != end; ++it)
//			{
//				SceneNodeAnimation * animation = *it;
//				printf(">>> blend: %s wei: %f inDelay: %f\n", animation->GetParent()->name.c_str(), animation->weight, animation->delayTime);
//			}
//		}
	}
	
    // update world transform only in case if 
    if (!(flags & NODE_WORLD_MATRIX_ACTUAL))  
	{
		if (parent)
        {
            worldTransform = localTransform * parent->worldTransform;
        }else 
		{
            worldTransform = localTransform;
        }
        
        // need propagate changes to child nodes
        flags |= NODE_WORLD_MATRIX_ACTUAL;
        uint32 size = (uint32)childs.size();
        for (uint32 c = 0; c < size; ++c)
        {
            childs[c]->InvalidateLocalTransform();
            childs[c]->Update(timeElapsed);
        }
        
	}
    else 
    {
        uint32 size = (uint32)childs.size();
        for (uint32 c = 0; c < size; ++c)
        {
            childs[c]->Update(timeElapsed);
        }
    }

	//printf("- node: %s tr: %f %f %f\n", name.c_str(), localTransform.data[12], localTransform.data[13], localTransform.data[14]); 
	
	
	inUpdate = false;

    if (!removedCache.empty()) 
    {
        for (std::deque<SceneNode*>::iterator t = removedCache.begin(); t != removedCache.end(); ++t)
        {
            RemoveNode(*t);
        }
        removedCache.clear();
    }
}