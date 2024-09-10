// Stand alone test file format:
//
//	command=value
//  #optional commands
//
//	Sample format:
//
//		# Start with a header.code of CONFIGURE_DX (40003)
//		Command=40003
//		# This activityId is not used, but it is read outside the switch
//		activityId=0
//		Command=40010
//		# The activityId for this command is a random number.
//		#  Must match the activityId for the START_TIME command.
//		activityId=100
//		ObsLen=16
//		ifcSkyFreq=4
//		dxSkyFreq=4
//		channelNumber=0
//		baselineDelay=0
//		operationsFlag=11
//		daddResolution=0
//		pulseThreshold=.5
//		maxPulsesPerHalfFrame=5000
//		maxPulsesPerSubchannelPerHalfFrame=10
//		daddThreshold=7
//
//		#	operations flag
// 		#			For CD_ONLY use a value of 1
//		#			For Baseline only use a value of 2
// 		#			For CD and CWD use a value of 17
//		#			For Baseline, CD & CWD use a value of 19
//		#			Any mode can be used with -s (simulated data)
//		#			Only CD_ONLY mode can be used with -z (DDC)
//		#				 operations flag is a bitmask, where the bit numbers
//		#				 are defined by the OperationsMask enum in
// 		#				 sseInterface.h.  To check the mask for a
//		#				 particular value, you need to mask it with
//		#				 (1 << enum_value).
//		#				 For some (but not all) useful masks, there are a
//		#				 separate set of #defines in SseInputTask.h with
//		#				 the conversion from bit numbers to masks already done.
//		#				Anything except "Baseline only" requires CD.
//		#				Pulses require Baselines to work properly, so...
//		#			For PULSE_DETECTION use a value of 11 (CD & Baseline needed)
//		#			For PULSE, CW, and CD use a value of 27
//
//		# header.code of START_TIME (40013)
//		Command=40013
//		# activityId for this command must be the same as for the
//		# SEND_DX_ACTIVITY_PARAMETERS command
//		activityId=100
//
//
void
SseInputTask::processIpFromFile()
{
	SseInterfaceHeader hdr;
	Msg *msg = 0;
	MemBlk *blk;
	void *data;
	int i;
	int counter = 0;
	static int lastMsg = 0;
	Timer timer;
	int obsLength = 0;
	int baseLineDelay = 0;
	int additionalAlarmDelay = 30;

		// Wait a bit...
	timer.sleep(1000);

	passThruCfg *pt = new passThruCfg();

	/*
	** Kludge --
	** Originally all standalone files started with the
	** CONFIGURE_DX command (40003) and had 13 fixed
	** entries. The config file should be changed to be
	** parameter based... but in the mean time (which
	** might be a long time)... An integer version number
	** has been added to the top of the file.
	**
	** Thus, if the first entry is 40003 this code looks
	** for the original 13 fixed entries and uses a
	** resolution of 1HZ.  If the first entry is a
	** version number than the version number is checked
	** as needed and new entries can be read from the file.
	*/
	/*
	** Remove ALL the version code. Configuration
	** file is now parameterized.
	*/

	int cmd = pt->getNxtCmd();
	while (cmd)
	{
		timer.sleep(3000);
		if (++counter == 10)
			Fatal(ERR_IPIV); 	// Something is wrong!

		hdr.activityId = pt->getActivityId();
		hdr.code = cmd;

		LogInfo(0, -1, "Reading standalone Config File cmd %d actId %d",
				hdr.code, hdr.activityId);

		hdr.messageNumber = lastMsg++;
		switch (hdr.code) {
			case CONFIGURE_DX:
			{
				hdr.dataLength = sizeof(DxConfiguration);
				msg = msgList->alloc();
				msg->setHeader(hdr);

					/* Allocate space for the cmd specific data */
				blk = partitionSet->alloc((size_t) hdr.dataLength);
				Assert(blk);
				if (!blk)
					Fatal(ERR_MAF);

				data = blk->getData();

				/* Initialize data.... */
				DxConfiguration *config = (DxConfiguration *)data;
				config->a2dClockrate = 104.16;

				msg->setData(data, hdr.dataLength, blk);
				break;
			}
			case SEND_DX_ACTIVITY_PARAMETERS:
			{
				hdr.dataLength = sizeof(DxActivityParameters);
				msg = msgList->alloc();
				msg->setHeader(hdr);

					/* Allocate space for the cmd specific data */
				blk = partitionSet->alloc((size_t) hdr.dataLength);
				Assert(blk);
				if (!blk)
					Fatal(ERR_MAF);

				data = blk->getData();

				/* Initialize data.... */
				DxActivityParameters *params = (DxActivityParameters *)data;
				params->activityId = hdr.activityId;
				obsLength = pt->getInt("ObsLen",cmd);;
				params->dataCollectionLength = obsLength; // seconds
					// RF Freq/MHz of IF band center
				params->ifcSkyFreq = pt->getInt("ifcSkyFreq",cmd);
				; 	// RF Freq/MHz of DX band center
				params->dxSkyFreq = pt->getInt("dxSkyFreq",cmd);
					// Number of subchannels. bins
				params->channelNumber = pt->getInt("channelNumber",cmd);
				baseLineDelay = pt->getInt("baselineDelay",cmd);
				cmdArgs->setBaselineDelay(baseLineDelay);
				int optParams = pt->getInt("operationsFlag",cmd);
					// optParams is a bitmask, where the bit numbers are
					// defined by the OperationsMask enum in
					// sseInterface.h.  To check the mask for a particular
					// value, you need to mask it with (1 << enum_value).
					// For some (but not all) useful masks, there are a
					// separate set of #defines in SseInputTask.h with
					// the conversion from bit numbers to masks already done.
LogInfo(0, -1, "processIpFromFile: optParams = %d ",optParams);
//					Either mode can be used with -s (simulated data)
//					Only CD_ONLY mode can be used with -z (DDC)
					//
					// For CD_ONLY use a value of 1
					// For CD and CWD use a value of 9
					// For CD, CWD & Baseline use a value of 11
					//
				params->operations = optParams;		// bit mask for DX operations
				if ((optParams & (1 << POWER_CWD)))
					additionalAlarmDelay += 30;

				params->sensitivityRatio = 0;       // main/remote rel sensitivity
				params->maxNumberOfCandidates = 0;
				params->clusteringFreqTolerance = 0; // Hz
				params->zeroDriftTolerance = 0;      // Hz/Sec
				params->zeroDriftTolerance = 0;      // Hz/Sec
				params->cwClusteringDeltaFreq = 0;   // bins
				params->badBandCwPathLimit = 12;    // max # paths /kHz (default approx == 256/slice)
					// Add daddResoultion to config file
				int res = pt->getInt("daddResolution",cmd);
				params->daddResolution = (Resolution)res;

				float32_t pulseThresh = pt->getFloat("pulseThreshold", cmd);
				params->maxPulsesPerHalfFrame =
						pt->getInt("maxPulsesPerHalfFrame",cmd);
				params->maxPulsesPerSubchannelPerHalfFrame =
						pt->getInt("maxPulsesPerSubchannelPerHalfFrame",cmd);

				params->daddThreshold =
						pt->getFloat("daddThreshold",cmd);
									// Sigma
									// Sigma 0==115 clusters
									// daddThreshold = 2 1137 clusters power.5
									// daddThreshold = 5 391 clusters power.5
									// daddThreshold = 7 11 clusters power.5
									// daddThreshold = 7  10 clusters power 0
									// daddThreshold = 8  1 clusters power 0
									// daddThreshold = 8.1  1 clusters power 0
									// *** 8.2 is where noise is gone ****
									// daddThreshold = 8.2  0 clusters power 0
									// daddThreshold = 8.5  0 clusters power 0
									// daddThreshold = 10 0 clusters power.5

				params->cwCoherentThreshold = 0;    // Sigma
				params->limitsForCoherentDetection = 0;
				params->badBandPulseTripletLimit = 0;  // # of paths
				params->badBandPulseLimit = 0;
				params->pulseClusteringDeltaFreq = 0;    // bins
				params->pulseTrainSignifThresh = 0;
				for (i = 0; i < MAX_RESOLUTIONS; ++i)
					params->requestPulseResolution[i] = SSE_FALSE;
				params->requestPulseResolution[RES_1HZ] = SSE_TRUE;
				params->alignPad2 = 0;         // alignment padding for marshalling
				for (i=0; i<MAX_RESOLUTIONS; ++i) {
					params->pd[i].pulseThreshold = pulseThresh;
					params->pd[i].tripletThreshold = 0;
					params->pd[i].singletThreshold = 0;
				}
				params->scienceDataRequest.sendBaselines = SSE_FALSE;
				params->scienceDataRequest.baselineReportingHalfFrames = 0;
#if 1
				params->scienceDataRequest.sendComplexAmplitudes = SSE_FALSE;
				params->scienceDataRequest.requestType = REQ_FREQ;
				params->scienceDataRequest.subchannel = 0;
#else
				// for waterfall debug
				params->scienceDataRequest.sendComplexAmplitudes = SSE_TRUE;
				params->scienceDataRequest.requestType = REQ_SUBCHANNEL;
				params->scienceDataRequest.subchannel = 1200;
#endif
				params->scienceDataRequest.rfFreq = 0;
				params->baselineSubchannelAverage = -1;
				params->baselineInitAccumHalfFrames = pt->getInt("baselineHalfFrames",cmd);
				LogInfo(0, -1, "actId: %d, obsLen: %d sendComplexAmplitudes: %d, ifcSkyFreq: %d", hdr.activityId,obsLength,params->scienceDataRequest.sendComplexAmplitudes,params->ifcSkyFreq);
				msg->setData(data, hdr.dataLength, blk);
				break;
				}
			case START_TIME:
			{
					LogInfo(0, -1, "processIpFromFile/START_TIME");
					hdr.dataLength = sizeof(StartActivity);
					msg = msgList->alloc();
					msg->setHeader(hdr);

						/* Allocate space for the cmd specific data */
					blk = partitionSet->alloc((size_t) hdr.dataLength);
					Assert(blk);
				if (!blk)
					Fatal(ERR_MAF);

				data = blk->getData();

				/* Initialize data.... */
				StartActivity *params = (StartActivity *)data;
				params->startTime.tv_sec = 0;
				params->startTime.tv_usec = 0;
				msg->setData(data, hdr.dataLength, blk);
				break;
			}

			default:
				FatalStr(hdr.code, "msg code");
		}
		cmdQ->send(msg);
		cmd = pt->getNxtCmd();
		hdr.code = cmd;
	}
		// Give the dx only so long to show its stuff...
//	double mtt = 2.5*(obsLength+baseLineDelay) + additionalAlarmDelay;
	double mtt = 100*(obsLength+baseLineDelay) + additionalAlarmDelay;
	int max_time_to_run = ((int) mtt);
	alarm(max_time_to_run);
	string n;
	name(n);
	LogInfo(0, -1, "Start Alarm on stand alone version: %d seconds. %d frames %d baseline delay\n",
			max_time_to_run, obsLength, baseLineDelay);

}