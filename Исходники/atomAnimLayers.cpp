//this function will pass in all anim layer objects found on a particular plug. since we want them to be
//kept in order, but don't want ALL of the anim layers to be specified if they aren't used we
bool atomAnimLayers::addAnimLayers(MObjectArray &layers)
{
	if(mOrderedAnimLayerNames.length() > 0)
	{
		//first time called set up the mAnimLayers object array.
		if(mAnimLayers.length() != mOrderedAnimLayerNames.length())
		{
			mAnimLayers.setLength(mOrderedAnimLayerNames.length());
			MObject nullObject;
			//initialize with nulls
			for(unsigned int k = 0; k < mAnimLayers.length(); ++k)
			{
				mAnimLayers[k] = nullObject;
			}
		}
	}
	//if here we have the ordered name list and the anim layer object list 
	//now we just need to set the objects passed in correctly
	for(unsigned int k = 0; k < layers.length(); ++k)
	{
		if(layers[k].hasFn (MFn::kDependencyNode))
		{
			MFnDependencyNode fnNode (layers[k]);
			MString layerName = fnNode.name();
			for(unsigned int z = 0; z < mOrderedAnimLayerNames.length();++z)
			{
				if(layerName == mOrderedAnimLayerNames[z])
				{
					mAnimLayers[z] = layers[k];
					break;
				}
			}
		}
	}
	
	return true;
}