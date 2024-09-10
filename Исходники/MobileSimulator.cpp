void MobileSimulator::MouseMotionEvent(Vec2i screenCoordinates)
{
	Vector2 pos = MathUtil::ScreenToWorld(screenCoordinates);
	_fingerGhost1->SetPosition(pos);
	_fingerGhost2->SetPosition(-pos);

	if (_mouseDown)
	{
		//move touch(es)
		TouchList *tl = &TouchListener::GetTouchList();
		if (tl->size() > 0)
		{
			(*tl)[0]->CurrentPoint = screenCoordinates;
			if ( (*tl)[0]->MotionStartTime < 0.0f )
			{
				(*tl)[0]->MotionStartTime = theWorld.GetCurrentTimeSeconds();
			}
		}
		if (tl->size() > 1)
		{
			Vector2 negCoordsVec = MathUtil::WorldToScreen(-pos);
			Vec2i negCoords((int)negCoordsVec.X, (int)negCoordsVec.Y);
			(*tl)[1]->CurrentPoint = negCoords;
			if ( (*tl)[1]->MotionStartTime < 0.0f )
			{
				(*tl)[1]->MotionStartTime = theWorld.GetCurrentTimeSeconds();
			}

			Touch* t1 = (*tl)[0];
			Touch* t2 = (*tl)[1];

			Vector2 start1(t1->StartingPoint);
			Vector2 current1(t1->CurrentPoint);
			Vector2 start2(t2->StartingPoint);
			Vector2 current2(t2->CurrentPoint);

			Vector2 initialVector = start2 - start1;
			Vector2 currentVector = current2 - current1;

			Vector2 initNorm = Vector2::Normalize(initialVector);
			Vector2 currentNorm = Vector2::Normalize(currentVector);
			float radiansRotated = acos(Vector2::Dot(initNorm, currentNorm));

			if (!_multiGestureOngoing)
			{					
				Vector2 motion = current1 - start1;

				if (motion.LengthSquared() >= (MULTI_MIN_DISTANCE * MULTI_MIN_DISTANCE) )
				{
					_multiGestureOngoing = true;
					
					// figure out if it's a rotate or a pinch
					if (radiansRotated > MULTI_ROTATE_ANGLE)
					{
						_gestureType = ROTATE;
					}
					else
					{
						_gestureType = PINCH;
					}
				}
			}

			if (_multiGestureOngoing)
			{
				GestureData gd;
				gd.Velocity = 0.0f; // don't want to store all the extra datums
									//  needed to actually calculate this

				if      (_gestureType == ROTATE)
				{
					float cross = Vector2::Cross(initNorm, currentNorm);
					if (cross > 0.0f)
					{
						radiansRotated = -radiansRotated;
					}
					gd.GestureMagnitude = radiansRotated;
					theSwitchboard.Broadcast(new TypedMessage<GestureData>("MultiTouchRotate", gd));
				}
				else if (_gestureType == PINCH)
				{
					gd.GestureMagnitude = currentVector.Length() / initialVector.Length();
					theSwitchboard.Broadcast(new TypedMessage<GestureData>("MultiTouchPinch", gd));	
				}
			}
		}
	}
}