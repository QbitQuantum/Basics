// Execute function
void BehDribbleBall::execute(ActuatorVars& AV, const ActuatorVars& lastAV, bool justActivated)
{
	//
	// Gaze control
	//

	// Look for the ball
	GazeBehLookForBall::execute(AV, lastAV, justActivated);

	//
	// Walking control
	//

	// If we have no ball then stop where you are
	if(!SV.haveBall)
	{
		// Set our walking GCV
		AV.GCV.setZero();
		AV.halt = false;
		AV.doKick = false;
		AV.rightKick = true;
		AV.doDive = DD_NONE;

		// Visualisation markers
		if(MM.willPublish())
		{
			MM.SubStateText.setText("Dribble without Ball");
			MM.SubStateText.updateAdd();
		}

		// Return as we have nothing more to do
		return;
	}

	// Required gait control vector
	Vec3f GCV(0.0f, 0.0f, 0.0f); // x forwards, y left, z CCW

	// Save the relative offsets to the ball and target in local variables
	Vec2f ball = SV.ballDir;         // Vector from robot to ball in body-fixed coordinates
	Vec2f target = GV.ballTargetDir; // Vector from robot to target in body-fixed coordinates
	if(!WBS.haveBallTarget)          // If we don't have a ball target then take one that's in the direction we're facing in front of the ball
		target << ball.x() + config.minBallToTargetDist(), ball.y();

	// Calculate the vector from the ball to the target in body-fixed coordinates
	Vec2f E = target - ball;                  // The E coordinate system is centred at the ball
	Vec2f unitEx = eigenNormalized(E);        // x-axis of E: Unit vector from the ball towards the ball target
	Vec2f unitEy = eigenRotatedCCW90(unitEx); // y-axis of E: Unit vector 90 deg CCW from the x-axis of E

	// Transform the robot position and orientation into the E coordinate frame
	Vec2f robotE(-ball.dot(unitEx), -ball.dot(unitEy));
	float robotAngle = -eigenAngleOf(unitEx);

	// Decide which foot we would prefer for dribbling based on the current robot position
	bool preferRightFoot = (robotE.y() >= WBS.reqBallDirMidY);

	// Decide whether we should reconsider the foot we're currently using for dribbling
	if(GV.suggestRightFoot()) // The right foot is being strongly suggested to us from above
		m_changeToRightFoot.vote(true, 2);
	else if(GV.suggestLeftFoot()) // The left foot is being strongly suggested to us from above
		m_changeToRightFoot.vote(false, 2);
	else
		m_changeToRightFoot.vote(preferRightFoot);
	bool reconsiderFoot = (m_changeToRightFoot.unanimous() && m_changeToRightFoot.decision() != m_useRightFoot);

	// Decide which foot to use for dribbling
	if(justActivated || reconsiderFoot)
		m_useRightFoot = m_changeToRightFoot.decision();

	// Calculate the desired path angle for the dribble approach
	Vec2f robotToBehindBallE, robotToPathTargetE;
	float pathAngle = calcPathAngle(m_useRightFoot, robotE, robotToBehindBallE, robotToPathTargetE);
	float localPathAngle = picut(pathAngle - robotAngle);

	// Calculate the robot to path angle interpolation factor u (0.0 = Walk to robot angle, 1.0 = Walk to path angle)
	float u = calcPathInterpFactor(robotToBehindBallE, localPathAngle);

	// Calculate the desired XY walking velocity
	float walkAngle = calcWalkAngle(robotToBehindBallE, u, localPathAngle, pathAngle);
	Vec2f walkVecXY = WBS.calcGcvXY(config.dbAppGcvSpeedX(), config.dbAppGcvSpeedY(), walkAngle);

	// Calculate the final GCV by factoring in the turning Z velocity and XY reduction for angular misalignments
	float angleRatio = localPathAngle / config.dbAppAngleErrLimit();
	float ratioXY = coerce<float>(1.0f - fabs(angleRatio), 0.0f, 1.0f);
	float signedRatioZ = coerceAbs(angleRatio, 1.0f);
	GCV.x() = ratioXY * walkVecXY.x();
	GCV.y() = ratioXY * walkVecXY.y();
	GCV.z() = signedRatioZ * config.dbAppGcvSpeedZ();

	// Normalise the GCV to our desired maximum walking speed
	float gcvNorm = GCV.norm();
	float speedLimit = fabs(config.dbAppGcvSpeedLimit());
	if(gcvNorm > speedLimit)
		GCV *= speedLimit / gcvNorm;

	// Apply obstacle avoidance and set the walking target
	Vec2f walkingTarget = robotToPathTargetE.x() * unitEx + robotToPathTargetE.y() * unitEy;
	WBS.obstacleAvoidance(GCV, walkingTarget);
	WBS.setWalkingTarget(walkingTarget);

	// Set our walking GCV
	AV.GCV = GCV;
	AV.halt = false;
	AV.doKick = false;
	AV.rightKick = true;
	AV.doDive = DD_NONE;

	// Plotting
	if(config.plotData())
	{
		PM.plotScalar(preferRightFoot * PMSCALE_FOOTSEL, PM_DBAPP_PREFERRIGHTFOOT);
		PM.plotScalar(reconsiderFoot * PMSCALE_FOOTOK, PM_DBAPP_RECONSIDERFOOT);
		PM.plotScalar(m_useRightFoot * PMSCALE_FOOTSEL, PM_DBAPP_USERIGHTFOOT);
		PM.plotScalar(robotE.x(), PM_DBAPP_ROBOTEX);
		PM.plotScalar(robotE.y(), PM_DBAPP_ROBOTEY);
		PM.plotScalar(localPathAngle, PM_DBAPP_LOCALPATHANGLE);
		PM.plotScalar(u, PM_DBAPP_UFACTOR);
		PM.plotScalar(ratioXY, PM_DBAPP_RATIOXY);
	}

	// Visualisation markers
	if(MM.willPublish())
	{
		MM.SubStateText.setText(m_useRightFoot ? "Right Dribble" : "Left Dribble");
		MM.SubStateText.updateAdd();
	}
}