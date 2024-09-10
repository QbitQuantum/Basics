void ConstraintSearchThread::testConstraint(
		const KeyFrame::SharedPtr &keyframe,
		const KeyFrame::SharedPtr &candidate,
		KFConstraintStruct* e1_out, KFConstraintStruct* e2_out,
		Sim3 candidateToFrame_initialEstimate,
		float strictness)
{
//	candidateTrackingReference->importFrame(candidate);

	Sim3 FtoC = candidateToFrame_initialEstimate.inverse(), CtoF = candidateToFrame_initialEstimate;
	Matrix7x7 FtoCInfo, CtoFInfo;

	float err_level3 = tryTrackSim3(keyframe, candidate,	// A = frame; b = candidate
																	SIM3TRACKING_MAX_LEVEL-1, 3,
																	USESSE,
																	FtoC, CtoF);

	if(err_level3 > 3000*strictness)
	{
		// LOGF_IF(DEBUG,Conf().print.constraintSearchInfo,
		// 		"FAILED %d -> %d (lvl %d): errs (%.1f / - / -).",
		// 		newKFTrackingReference->frameID, candidateTrackingReference->frameID,
		// 		3,
		// 		sqrtf(err_level3));

		e1_out = e2_out = 0;

		keyframe->trackingFailed.insert(std::pair< KeyFrame::SharedPtr,Sim3>(candidate, candidateToFrame_initialEstimate));
		return;
	}

	float err_level2 = tryTrackSim3(
			keyframe, candidate,
			2, 2,
			USESSE,
			FtoC, CtoF);

	if(err_level2 > 4000*strictness)
	{
		// LOGF_IF(DEBUG,Conf().print.constraintSearchInfo,
		// 	"FAILED %d -> %d (lvl %d): errs (%.1f / %.1f / -).",
		// 		newKFTrackingReference->frameID, candidateTrackingReference->frameID,
		// 		2,
		// 		sqrtf(err_level3), sqrtf(err_level2));

		e1_out = e2_out = 0;
		keyframe->trackingFailed.insert(std::pair<KeyFrame::SharedPtr,Sim3>(candidate, candidateToFrame_initialEstimate));
		return;
	}

	e1_out = new KFConstraintStruct();
	e2_out = new KFConstraintStruct();


	float err_level1 = tryTrackSim3(
			keyframe, candidate,
			1, 1,
			USESSE,
			FtoC, CtoF, e1_out, e2_out);

	if(err_level1 > 6000*strictness)
	{
		// LOGF_IF(DEBUG,Conf().print.constraintSearchInfo,
		// 		"FAILED %d -> %d (lvl %d): errs (%.1f / %.1f / %.1f).",
		// 			newKFTrackingReference->frameID, candidateTrackingReference->frameID,
		// 			1,
		// 			sqrtf(err_level3), sqrtf(err_level2), sqrtf(err_level1));

		delete e1_out;
		delete e2_out;
		e1_out = e2_out = 0;
		keyframe->trackingFailed.insert(std::pair<KeyFrame::SharedPtr,Sim3>(candidate, candidateToFrame_initialEstimate));
		return;
	}


	// LOGF_IF(DEBUG,Conf().print.constraintSearchInfo,
	// 		"ADDED %d -> %d: errs (%.1f / %.1f / %.1f).",
	// 		newKFTrackingReference->frameID, candidateTrackingReference->frameID,
	// 		sqrtf(err_level3), sqrtf(err_level2), sqrtf(err_level1));


	const float kernelDelta = 5 * sqrt(6000*loopclosureStrictness);
	e1_out->robustKernel = new g2o::RobustKernelHuber();
	e1_out->robustKernel->setDelta(kernelDelta);
	e2_out->robustKernel = new g2o::RobustKernelHuber();
	e2_out->robustKernel->setDelta(kernelDelta);
}