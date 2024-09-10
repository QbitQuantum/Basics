/** The PF algorithm implementation for "optimal sampling" approximated with scan matching (Stachniss method)
  */
void  CLSLAM_RBPF_2DLASER::prediction_and_update_pfOptimalProposal(
	CLocalMetricHypothesis	*LMH,
	const mrpt::slam::CActionCollection	* actions,
	const mrpt::slam::CSensoryFrame		* sf,
	const bayes::CParticleFilter::TParticleFilterOptions &PF_options )
{
	MRPT_START

	CTicTac tictac;

	// Get the current robot pose estimation:
	TPoseID		currentPoseID = LMH->m_currentRobotPose;

	// ----------------------------------------------------------------------
	//	  We can execute optimal PF only when we have both, an action, and
	//     a valid observation from which to compute the likelihood:
	//   Accumulate odometry/actions until we have a valid observation, then
	//    process them simultaneously.
	// ----------------------------------------------------------------------
	bool  SFhasValidObservations = false;
	// A valid action?
	if (actions!=NULL)
	{
		CActionRobotMovement2DPtr act = actions->getBestMovementEstimation();	// Find a robot movement estimation:
		if (!act) THROW_EXCEPTION("Action list does not contain any CActionRobotMovement2D derived object!");

		if (!LMH->m_accumRobotMovementIsValid) // Reset accum.
		{
			act->poseChange->getMean( LMH->m_accumRobotMovement.rawOdometryIncrementReading );
			LMH->m_accumRobotMovement.motionModelConfiguration = act->motionModelConfiguration;
		}
		else
			LMH->m_accumRobotMovement.rawOdometryIncrementReading =
				LMH->m_accumRobotMovement.rawOdometryIncrementReading +
				act->poseChange->getMeanVal();

		LMH->m_accumRobotMovementIsValid = true;
	}

	if (sf!=NULL)
	{
		ASSERT_(LMH->m_particles.size()>0);
		SFhasValidObservations = (*LMH->m_particles.begin()).d->metricMaps.canComputeObservationsLikelihood( *sf );
	}

	// All the needed things?
	if (!LMH->m_accumRobotMovementIsValid || !SFhasValidObservations)
		return; // Nothing we can do here...
	ASSERT_(sf!=NULL);
	ASSERT_(!PF_options.adaptiveSampleSize);

	// OK, we have all we need, let's start!

	// The odometry-based increment since last step is
	// in:   LMH->m_accumRobotMovement.rawOdometryIncrementReading
	const CPose2D initialPoseEstimation = LMH->m_accumRobotMovement.rawOdometryIncrementReading;
	LMH->m_accumRobotMovementIsValid = false; // To reset odometry at next iteration!


	// ----------------------------------------------------------------------
	//						1) FIXED SAMPLE SIZE VERSION
	// ----------------------------------------------------------------------

	// ICP used if "pfOptimalProposal_mapSelection" = 0 or 1
	CICP					icp;
	CICP::TReturnInfo	icpInfo;

	// ICP options
	// ------------------------------
	icp.options.maxIterations = 80;
	icp.options.thresholdDist = 0.50f;
	icp.options.thresholdAng = DEG2RAD( 20 );
	icp.options.smallestThresholdDist = 0.05f;
	icp.options.ALFA		  = 0.5f;
	icp.options.onlyClosestCorrespondences = true;
	icp.options.doRANSAC = false;

	// Build the map of points to align:
	CSimplePointsMap	localMapPoints;

	ASSERT_( LMH->m_particles[0].d->metricMaps.m_gridMaps.size() > 0);
	//float	minDistBetweenPointsInLocalMaps = 0.02f; //3.0f * m_particles[0].d->metricMaps.m_gridMaps[0]->getResolution();

	// Build local map:
	localMapPoints.clear();
	localMapPoints.insertionOptions.minDistBetweenLaserPoints =  0.02;
	sf->insertObservationsInto( &localMapPoints );

	// Process the particles
	const size_t M = LMH->m_particles.size();
	LMH->m_log_w_metric_history.resize(M);

	for (size_t i=0;i<M;i++)
	{
		CLocalMetricHypothesis::CParticleData  &part = LMH->m_particles[i];
		CPose3D *part_pose = LMH->getCurrentPose(i);

		if ( LMH->m_SFs.empty() )
		{
			// The first robot pose in the SLAM execution: All m_particles start
			// at the same point (this is the lowest bound of subsequent uncertainty):
			// New pose = old pose.
			// part_pose: Unmodified
		}
		else
		{
			// ICP and add noise:
			CPosePDFGaussian	icpEstimation;

			// Select map to use with ICP:
			CMetricMap *mapalign;

			if (!part.d->metricMaps.m_pointsMaps.empty())
				mapalign = part.d->metricMaps.m_pointsMaps[0].pointer();
			else if (!part.d->metricMaps.m_gridMaps.empty())
				mapalign = part.d->metricMaps.m_gridMaps[0].pointer();
			else
				THROW_EXCEPTION("There is no point or grid map. At least one needed for ICP.");

			// Use ICP to align to each particle's map:
			CPosePDFPtr alignEst = icp.Align(
				mapalign,
				&localMapPoints,
				initialPoseEstimation,
				NULL,
				&icpInfo);

			icpEstimation.copyFrom( *alignEst );

#if 0
			// HACK:
			CPose3D Ap = finalEstimatedPoseGauss.mean - ith_last_pose;
			double  Ap_dist = Ap.norm();
			finalEstimatedPoseGauss.cov.zeros();
			finalEstimatedPoseGauss.cov(0,0) = square( fabs(Ap_dist)*0.01 );
			finalEstimatedPoseGauss.cov(1,1) = square( fabs(Ap_dist)*0.01 );
			finalEstimatedPoseGauss.cov(2,2) = square( fabs(Ap.yaw())*0.02 );
#endif

			// Generate gaussian-distributed 2D-pose increments according to "finalEstimatedPoseGauss":
			// -------------------------------------------------------------------------------------------
			// Set the gaussian pose:
			CPose3DPDFGaussian finalEstimatedPoseGauss( icpEstimation );

			CPose3D noisy_increment;
			finalEstimatedPoseGauss.drawSingleSample(noisy_increment);

			CPose3D new_pose;
			new_pose.composeFrom(*part_pose,noisy_increment);

			CPose2D new_pose2d = CPose2D(new_pose);

			// Add the pose to the path:
			part.d->robotPoses[ LMH->m_currentRobotPose ] = new_pose;

			// Update the weight:
			// ---------------------------------------------------------------------------
			const double log_lik =
				PF_options.powFactor *
				auxiliarComputeObservationLikelihood(
					PF_options,
					LMH,
					i,
					sf,
					&new_pose2d);

			part.log_w += log_lik;

			// Add to historic record of log_w weights:
			LMH->m_log_w_metric_history[i][currentPoseID] += log_lik;

		} // end else we can do ICP

	} // end for each particle i

	// Accumulate the log likelihood of this LMH as a whole:
	double out_max_log_w;
	LMH->normalizeWeights( &out_max_log_w );	// Normalize weights:
	LMH->m_log_w += out_max_log_w;

	printf("[CLSLAM_RBPF_2DLASER] Overall likelihood = %.2e\n",out_max_log_w);
	printf("[CLSLAM_RBPF_2DLASER] Done in %.03fms\n",1e3*tictac.Tac());

	MRPT_END
}