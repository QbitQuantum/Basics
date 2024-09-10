void CameraBehaviorVehicleSpline::createSpline(const CameraManager::CameraContext &ctx)
{
	splineClosed = false;
	splineLength = 1.0f;

	spline->clear();
	splineNodes.clear();

	for (int i = 0; i < ctx.mCurrTruck->free_camerarail; i++)
	{
		splineNodes.push_back(&ctx.mCurrTruck->nodes[ctx.mCurrTruck->cameraRail[i]]);
	}

	std::list<Beam*> linkedBeams = ctx.mCurrTruck->getAllLinkedBeams();

	numLinkedBeams = linkedBeams.size();

	if ( numLinkedBeams > 0 )
	{
		for (std::list<Beam*>::iterator it = linkedBeams.begin(); it != linkedBeams.end(); ++it)
		{
			if ( (*it)->free_camerarail <= 0 ) continue;

			Vector3 curSplineFront = splineNodes.front()->AbsPosition;
			Vector3 curSplineBack  = splineNodes.back() ->AbsPosition;

			Vector3 linkedSplineFront = (*it)->nodes[(*it)->cameraRail[0]].AbsPosition;
			Vector3 linkedSplineBack  = (*it)->nodes[(*it)->cameraRail[(*it)->free_camerarail - 1]].AbsPosition;

			if        ( curSplineBack.distance(linkedSplineFront) < 5.0f )
			{
				for (int i = 1; i < (*it)->free_camerarail; i++)
				{
					splineNodes.push_back(&(*it)->nodes[(*it)->cameraRail[i]]);
				}
			} else if ( curSplineFront.distance(linkedSplineFront) < 5.0f )
			{
				for (int i = 1; i < (*it)->free_camerarail; i++)
				{
					splineNodes.push_front(&(*it)->nodes[(*it)->cameraRail[i]]);
				}
			} else if ( curSplineBack.distance(linkedSplineBack) < 5.0f )
			{
				for (int i = (*it)->free_camerarail - 2; i >= 0; i--)
				{
					splineNodes.push_back(&(*it)->nodes[(*it)->cameraRail[i]]);
				}
			} else if ( curSplineFront.distance(linkedSplineBack) < 5.0f )
			{
				for (int i = (*it)->free_camerarail - 2; i >= 0; i--)
				{
					splineNodes.push_front(&(*it)->nodes[(*it)->cameraRail[i]]);
				}
			}
		}
	}

	for (unsigned int i = 0; i < splineNodes.size(); i++)
	{
		spline->addPoint(splineNodes[i]->AbsPosition);
	}

	Vector3 firstPoint = spline->getPoint(0);
	Vector3 lastPoint  = spline->getPoint(spline->getNumPoints() - 1);

	if ( firstPoint.distance(lastPoint) < 1.0f )
	{
		splineClosed = true;
	}

	for (int i = 1; i < spline->getNumPoints(); i++)
	{
		splineLength += spline->getPoint(i - 1).distance(spline->getPoint(i));
	}

	splineLength /= 2.0f;

	if ( !splineObject && ctx.mDebug)
	{
		splineObject = gEnv->sceneManager->createManualObject();
		SceneNode* splineNode = gEnv->sceneManager->getRootSceneNode()->createChildSceneNode();

		splineObject->begin("tracks/transred", Ogre::RenderOperation::OT_LINE_STRIP);
		for (int i = 0; i < splineDrawResolution; i++)
		{
			splineObject->position(0, 0, 0);
		}
		splineObject->end();

		splineNode->attachObject(splineObject);
	}
}