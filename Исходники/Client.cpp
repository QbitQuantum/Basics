	Angle Client::calcPlayerObjAngle(Vec2<int> mouseScreenPos)
	{
		if (worldModel.getPlayerObjs().exists(playerId))
		{
			PlayerObj *playerObj = (worldModel.getPlayerObjs())[playerId];

			float angle;
			Pos mousePos(viewportHandler.screenToGame(worldRenderer.getRenderArea(playerObj), mouseScreenPos));
			Vec aimVec = mousePos - playerObj->pos;
			aimVec.normalize();
			if ((aimVec.x > 0.5) || (aimVec.x < 0.5f))
			{
				angle = asin(aimVec.y);
				if (aimVec.x < 0.0f) angle = PI_F - angle;
			}
			else
			{
				angle = acos(aimVec.x);
				if (aimVec.y < 0.0f) angle = -angle;
			}

			return angle;
		}
		
		return 0.0f;
	}