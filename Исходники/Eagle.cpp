/*!
* Identify the target state that we wish the robot to be in. This will be the target which the A* algorithm plots towards.
*/
RobotState Eagle::IdentifyTarget(RobotState &ourRobotState, RobotState &enemyRobotState, Vector2 ballPos, bool doWeHaveBall, bool &isMovingToBall)
{
	RobotState targetState;

	Vector2 ourRobotPos = ourRobotState.Position();
	Vector2 enemyRobotPos = enemyRobotState.Position();

    Vector2 ourGoalCentre = GoalCentrePosition(m_pitchSide);
    Vector2 enemyGoalCentre;

    if (m_pitchSide == eLeftSide)
    {
        enemyGoalCentre = GoalCentrePosition(eRightSide);
    }
    else
    {
        enemyGoalCentre = GoalCentrePosition(eLeftSide);
    }
    
    ballPos.Clamp(Vector2(0,0), Vector2(m_pitchSizeX-1, m_pitchSizeY-1));
	isMovingToBall = false;

	// doWeHaveBall is a value which comes from the robot's rotational sensors.
    //ourRobotState.SetHasBall(doWeHaveBall);
	ourRobotState.SetHasBall(DoesRobotHaveBall(ourRobotState, ballPos));
    enemyRobotState.SetHasBall(DoesRobotHaveBall(enemyRobotState, ballPos));

    if (m_state == ePenaltyAttack)
	{
		m_isKickingPosSet = false;

         // When taking a penalty, we want to find a free position to kick to.
        // Position should stay the same - we only want to re-orientate.
        targetState.SetPosition(ourRobotPos);

        // We'll do this by checking for intersections between us and three positions on the goal line.
        Vector2 targetPositions[3];

        targetPositions[0] = enemyGoalCentre;
        targetPositions[1] = enemyGoalCentre - Vector2(0,50);
        targetPositions[2] = enemyGoalCentre + Vector2(0,50);

        int arrayLength = sizeof(targetPositions)/sizeof(Vector2);

        Vector2 optimalShootingTarget;
        float bestDistanceFromEnemy = 0;

        // Iterate through the positions, finding the best one, based on if it's unblocked and how far it is from the enemy robot.
        for (int i=0; i < arrayLength; i++)
        {
            // Check if the target is unblocked.
            bool isBlocked = m_intersection.LineCircleIntersection(ourRobotPos, targetPositions[i], enemyRobotPos, ROBOT_RADIUS);

            if (isBlocked)
            {
                continue;
            }

            float distanceSqdToEnemy = enemyRobotPos.DistanceSquared(&targetPositions[i]);

            // Check if this beats our previous best distance.
            if (distanceSqdToEnemy > bestDistanceFromEnemy)
            {
                bestDistanceFromEnemy = distanceSqdToEnemy;
                optimalShootingTarget = targetPositions[i];
            }

            // Check that we do actually have a target set.
            if (optimalShootingTarget.IsSet())
            {
                float angleToTarget = ourRobotPos.GetAngleTo(&optimalShootingTarget);

                targetState.SetOrientation(angleToTarget);
            }
            else
            {
                targetState.SetOrientation(ourRobotState.Orientation());
            }
        }


	}
    else if (m_state == ePenaltyDefend)
	{
		m_isKickingPosSet = false;
	
		// When defending, we're permitted to move up and down the goalline.
		// Orientation should stay the same.
		targetState.SetOrientation(ourRobotState.Orientation());

		// X-axis position should be the same, y-axis should be a position extrapolated in the direction of the enemy robot.
		//float extrapolationGradient = tan(enemyRobotState.Orientation());
		// I'm experimenting with extrapolating on a line between the robot and ball instead.
		float extrapolationGradient = enemyRobotPos.Gradient(&ballPos);

		int extrapolatedY = enemyRobotPos.Y() + ((ourRobotPos.X() - enemyRobotPos.X()) * extrapolationGradient); 

		Vector2 proposedPosition(ourRobotPos.X(), extrapolatedY);
		proposedPosition.Clamp(Vector2(0,0), Vector2(m_pitchSizeX-1, m_pitchSizeY-1));

		targetState.SetPosition(proposedPosition);
	}
	else
	{
		// If we're here, assume we're in open play.
		if (!ourRobotState.HasBall())
		{
			m_isKickingPosSet = false;

			// Check if the enemy robot has the ball.
			if (enemyRobotState.HasBall())
            {
				if (m_pitchSide == eLeftSide)
				{
                    targetState.SetPosition(ourGoalCentre.X() + 50, ourGoalCentre.Y());
					targetState.SetOrientation(0);
				}
				else
				{
                    targetState.SetPosition(ourGoalCentre.X() - 50, ourGoalCentre.Y());
					targetState.SetOrientation(M_PI);
				}
            }
			else
			{
				// If we don't have the ball, the aim should be to move to the ball.
				isMovingToBall = true;
				targetState.SetPosition(ballPos);
				
				if (m_pitchSide == eLeftSide)
				{
					targetState.SetOrientation(0);
				}
				else
				{
					targetState.SetOrientation(M_PI);
				}
			}
		}
		else
		{
			// Check if the previously calculated target pos is appropriate or if we need to recalc.
			if ((m_isKickingPosSet) && ((m_kickingPos.Distance(&ourRobotPos) < 30) || (m_kickingPos.Distance(&enemyRobotPos) < 40)))
			{
				m_isKickingPosSet = false;
			}

			if (!m_isKickingPosSet)
			{
				// If we have the ball, let's move to a more appropriate place.
				// This is done regardless of whether we're shooting or not.
				/*
					This should depend on:
					1. The opposite half of the pitch to the enemy robot.
					2. Within the kicking threshold.
					3. Fairly central, but outside of the enemy robot's radius
					4. Orientated towards the goal
				*/
				bool isEnemyOnBottomSide;
			
				// Determine which half of the pitch the enemy robot is on.
				if (enemyRobotState.Position().Y() < m_pitchSizeY/2)
				{
					isEnemyOnBottomSide = true;
				}
				else
				{
					isEnemyOnBottomSide = false;
				}

				// Determine where the kicking threshold is for this side of the pitch.
		                float kickingPositionX;
		                float kickingPositionY;
		
				if (m_pitchSide == eLeftSide)
				{
                   			 kickingPositionX = m_pitchSizeX - ((KICKING_THRESHOLD/2)*m_pitchSizeX);
				}
				else
				{
                    			kickingPositionX = (KICKING_THRESHOLD/2)*m_pitchSizeX;
				}
		
		                if (isEnemyOnBottomSide)
		                {
		                    kickingPositionY = m_pitchSizeY/2 + 80;
		                }
		                else
		                {
		                    kickingPositionY = m_pitchSizeY/2 - 80;
		                }
		
						// Check if the position is within two robot radii of the enemy.
		                Vector2 proposedPosition = Vector2(kickingPositionX,kickingPositionY);

				// Check if the proposed position is too close to the enemy robot to be used.
				if (proposedPosition.Distance(&enemyRobotPos) < 2*ROBOT_RADIUS)
				{
					float adjustedYPosition;

					if (isEnemyOnBottomSide)
					{
						adjustedYPosition = proposedPosition.Y() + 2*ROBOT_RADIUS;
					}
					else
					{
						adjustedYPosition = proposedPosition.Y() - 2*ROBOT_RADIUS;
					}

					proposedPosition = Vector2( proposedPosition.X(), adjustedYPosition);
				}

				proposedPosition.Clamp(Vector2(0,0), Vector2(m_pitchSizeX-1, m_pitchSizeY-1));
				m_kickingPos = proposedPosition;

				m_isKickingPosSet = true;
			}
		
			targetState.SetPosition(m_kickingPos);
			
			// We'll do this by checking for intersections between us and three positions on the goal line.
			Vector2 targetPositions[3];

			targetPositions[0] = enemyGoalCentre;
			targetPositions[1] = enemyGoalCentre - Vector2(0,50);
			targetPositions[2] = enemyGoalCentre + Vector2(0,50);

			int arrayLength = sizeof(targetPositions)/sizeof(Vector2);

			Vector2 optimalShootingTarget;
			float bestDistanceFromEnemy = 0;

			// Iterate through the positions, finding the best one, based on if it's unblocked and how far it is from the enemy robot.
			for (int i=0; i < arrayLength; i++)
			{
				// Check if the target is unblocked.
				bool isBlocked = m_intersection.LineCircleIntersection(m_kickingPos, targetPositions[i], enemyRobotPos, ROBOT_RADIUS);

				if (isBlocked)
				{
					continue;
				}

				float distanceSqdToEnemy = enemyRobotPos.DistanceSquared(&targetPositions[i]);

				// Check if this beats our previous best distance.
				if (distanceSqdToEnemy > bestDistanceFromEnemy)
				{
					bestDistanceFromEnemy = distanceSqdToEnemy;
					optimalShootingTarget = targetPositions[i];
				}

				// Check that we do actually have a target set.
				if (optimalShootingTarget.IsSet())
				{
					float angleToTarget = m_kickingPos.GetAngleTo(&optimalShootingTarget);

					targetState.SetOrientation(angleToTarget);
				}
				else
				{
					targetState.SetOrientation(ourRobotState.Orientation());
				}
			}
		}

		targetState.SetPosition((int)targetState.Position().X(), (int)targetState.Position().Y());
	}

	
	return targetState;
}