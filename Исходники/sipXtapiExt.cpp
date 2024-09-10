SIPXTAPI_API SIPX_RESULT sipxQOSDebug(SIPX_INST phInst, CStdString& txt) {
	CStdString buff;

#ifdef INCLUDE_RTCP
	IRTCPControl* ic = CRTCManager::getRTCPControl();
	IRTCPSession* sess = ic->GetFirstSession();
	while (sess) {
		buff.Format("Sess: %d ", sess->GetSessionID());
		txt += buff;
		IRTCPConnection* conn = sess->GetFirstConnection();
		while (conn) {
			txt += "Conn\n";
			CRTCPRender* render = (CRTCPRender*)((CRTCPConnection*)conn)->GetRenderInterface();
			IGetSrcDescription* statDesc;
			IGetSenderStatistics* statSender;
			IGetReceiverStatistics* statRcvr;
			IGetByeInfo* statBye;
			render->GetStatistics(&statDesc, &statSender, &statRcvr, &statBye);
			char appName [255];
			statDesc->GetAppName((unsigned char*)appName);
			unsigned long packetCount, octetCount;
			statSender->GetSenderStatistics(&packetCount, &octetCount);
			unsigned long fractionalLoss, cumulativeLoss, highestSeq, interarrivalJitter, SRtimestamp, packetDelay;
			statRcvr->GetReceiverStatistics(&fractionalLoss, &cumulativeLoss, &highestSeq, &interarrivalJitter, &SRtimestamp, &packetDelay);

			buff.Format("app=%s, packet=%d, octet=%d, loss=%d, cLoss=%d, seq=%d, jitt=%d, SR=%d, delay=%d", appName, packetCount, octetCount, fractionalLoss, cumulativeLoss, highestSeq, interarrivalJitter, SRtimestamp, packetDelay);
			txt += buff + "\n";
			conn = sess->GetNextConnection();
		}

		sess = ic->GetNextSession();
	}
#endif 

	MpMediaTask* mtask = MpMediaTask::getMediaTask(32);
	MpFlowGraphBase* flowGraph = mtask->getFocus();
	if (flowGraph) {
		for (int i=0; i < flowGraph->mResourceCnt; i++) {
			MpResource* r = flowGraph->mExecOrder[i];
			if (strstr(r->getName(), "Dejitter")) {
				/*
				MprDejitter* dejj = (MprDejitter*) r;
				buff.Format("<u>%s</u>:: ave=%d, buff=%d, pull=%d, push=%d, " 
					//"lmax=%d, lmin=%d, " 
					"disc=%d, packs=%d ", dejj->getName().data(), dejj->getAveBufferLength(), dejj->mBufferLength, dejj->mLastPulled, dejj->mLastPushed 
					//, dejj->mLatencyMax, dejj->mLatencyMin
					, dejj->mNumDiscarded, dejj->mNumPackets);
				txt += buff + "<br/>";
				*/
			} else if (strstr(r->getName(), "Decode")) {
				/*
				MprDecode* decode = (MprDecode*) r;

				for (int c=0; c < decode->mNumCurrentCodecs; c++) {
					MpDecoderBase* mpd = decode->mpCurrentCodecs[c];
					if (mpd->getInfo()->getCodecType() == SdpCodec::SDP_CODEC_PCMU || mpd->getInfo()->getCodecType() == SdpCodec::SDP_CODEC_PCMA) {
						MpdSipxPcma* pcma = (MpdSipxPcma*)mpd;
						MpJitterBuffer* jb = (MpJitterBuffer*)pcma->pJBState;
						buff.Format("Codec::%d tci=%d, pull=%d, wait=%d, under=%d, seq=%d, few=%d, many=%d, last=%d", pcma->getInfo()->getCodecType(), pcma->mTimerCountIncrement, pcma->mNextPullTimerCount, pcma->mWaitTimeInFrames, pcma->mUnderflowCount, pcma->mLastSeqNo, pcma->mTooFewPacketsInBuffer, pcma->mTooManyPacketsInBuffer, pcma->mLastReportSize);
						txt += buff + ", JB:";
						buff.Format("avail=%d, qc=%d, qi=%d, qo=%d", jb->JbPacketsAvail, jb->JbQCount, jb->JbQIn, jb->JbQOut);
						txt += buff + "<br/>";
					}
				}
*/
			}/* else if (stristr(r->getName(), "FromNet")) {
				MprFromNet* fromNet = (MprFromNet*) r;
			}*/
		}
	}

	int rating = 0;
	sipxQOSRating(phInst, rating);
	buff.Format("Rating: <b>%d</b>", rating);
	txt += buff;

/*
MprDejitter::getAveBufferLength -> MprDejitter -> MprDecode::getMyDejitter / MprFromNet::getMyDejitter()
MpdSipxPcmu -> MpConnection::mapPayloadType  MpCodecFactory::createDecoder 
MpdSipxPcma (MpDecoderBase)
MpJitterBuffer -> MpConnection::getJBinst

MpCallFlowGraph::getConnectionPtr
*/
	return SIPX_RESULT_SUCCESS;
}