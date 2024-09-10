ISystem* getSystem()
{
	if( !sg_system )
	{
		sg_system = new System;
		sg_system->initialize();
	}
	return sg_system.get();
}