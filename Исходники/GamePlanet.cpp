void GamePlanet::cameraPositionChanged(IngameCamera* camera)
{
	Ogre::Vector3 camPos = camera->GetPosition();
	Ogre::Vector3 planetPos = node->getPosition();
	double dist = camPos.distance(planetPos) - radius;
	if(dist < 0)
	{
		dist = 0;
	}
	double pixelSize = camera->mPerspectiveScallingFactor * (2 * radius) / dist;

	PlanetLOD lodLevel;
	if (pixelSize <= 1)
	{
		//LOD_Invisible is used when the planet is extremely far away, and would normally be smaller than one pixel
		unloadLOD(LOD_Sprite);
		unloadLOD(LOD_Simple);
		unloadLOD(LOD_Complex);
		lodLevel = LOD_Invisible;
		loadLOD(LOD_Invisible);
	}
	else
	{
		if(pixelSize <= 10)
		{
			//LOD_Sprite is for long distances, where only a few pixels are rendered for the planet
			//At this LOD, all other LOD levels should be unloaded because the most likely won't be needed soon.
			unloadLOD(LOD_Simple);
			unloadLOD(LOD_Complex);
			lodLevel = LOD_Sprite;
			loadLOD(LOD_Sprite);
			// if (fullyLoadedPlanet == &planet) fullyLoadedPlanet = NULL;
		}
		else
		{
			if (pixelSize <= 750) 
			{
				//LOD_Simple is for medium-ranged planets, needing moderate orbital-perspective detail, but not surface detail.
				lodLevel = LOD_Simple;
				//Load not only LOD_Simple, but also ensure LOD_Sprite is loaded
				loadLOD(LOD_Sprite);
				loadLOD(LOD_Simple);
			}
			else
			{
				if (pixelSize > 750) 
				{
					//LOD_Complex is the highest level of detail, which loads everything on the planet for surface view.
						//If this LOD has not been loaded yet, the planet should use LOD_Medium until it is.
						lodLevel = LOD_Complex;
						//Ensure LOD_Simple and LOD_Sprite are loaded - until LOD_Complex can load, it will fall back on these
						loadLOD(LOD_Sprite);
						loadLOD(LOD_Simple);
						loadLOD(LOD_Complex);
				}
			}
		}
	}
	/*
	while (lodLevel < LOD_Invisible && !isloadedLOD(lodLevel))
	{
		lodLevel = (GamePlanet::PlanetLOD)(((uint32)lodLevel) + 1);
	}
	*/
	setLOD(lodLevel);
}