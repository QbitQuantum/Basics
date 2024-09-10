// to check if an object is animated, we need to check e.g. its transform inputs
// if the object is from an instancer node, always return true
bool MayaObject::isObjAnimated()
{
	MStatus stat;
	bool returnValue = false;
	
	if( this->instancerParticleId > -1)
		return true;

	if( this->mobject.hasFn(MFn::kTransform))
	{
		MFnDependencyNode depFn(this->mobject, &stat);
		if(stat)
		{
			MPlugArray connections;
			depFn.getConnections(connections);
			if( connections.length() == 0)
				returnValue = false;
			else{
				for( uint cId = 0; cId < connections.length(); cId++)
				{
					if( connections[cId].isDestination())
					{
						returnValue = true;
					}
				}
			}
			
		}
	}
	return returnValue;
}