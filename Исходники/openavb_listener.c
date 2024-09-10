static inline bool listenerDoStream(tl_state_t *pTLState)
{
	AVB_TRACE_ENTRY(AVB_TRACE_TL);

	if (!pTLState) {
		AVB_LOG_ERROR("Invalid TLState");
		AVB_TRACE_EXIT(AVB_TRACE_TL);
		return FALSE;
	}

	openavb_tl_cfg_t *pCfg = &pTLState->cfg;
	listener_data_t *pListenerData = pTLState->pPvtListenerData;
	bool bRet = FALSE;

	if (pTLState->bStreaming) {
		U64 nowNS;

		pListenerData->nReportCalls++;

		// Try to receive a frame
		if (IS_OPENAVB_SUCCESS(openavbAvtpRx(pListenerData->avtpHandle))) {
			pListenerData->nReportFrames++;
		}

		CLOCK_GETTIME64(OPENAVB_TIMER_CLOCK, &nowNS);

		if (pCfg->report_seconds > 0) {
			if (nowNS > pListenerData->nextReportNS) {
			  
				U64 lost = openavbAvtpLost(pListenerData->avtpHandle);
				U64 bytes = openavbAvtpBytes(pListenerData->avtpHandle);
				U32 rxbuf = openavbAvtpRxBufferLevel(pListenerData->avtpHandle);
				U32 mqbuf = openavbMediaQCountItems(pTLState->pMediaQ, TRUE);
				U32 mqrdy = openavbMediaQCountItems(pTLState->pMediaQ, FALSE);
			
				AVB_LOGRT_INFO(LOG_RT_BEGIN, LOG_RT_ITEM, FALSE, "RX UID:%d, ", LOG_RT_DATATYPE_U16, &pListenerData->streamID.uniqueID);
				AVB_LOGRT_INFO(FALSE, LOG_RT_ITEM, FALSE, "calls=%ld, ", LOG_RT_DATATYPE_U32, &pListenerData->nReportCalls);
				AVB_LOGRT_INFO(FALSE, LOG_RT_ITEM, FALSE, "frames=%ld, ", LOG_RT_DATATYPE_U32, &pListenerData->nReportFrames);
				AVB_LOGRT_INFO(FALSE, LOG_RT_ITEM, FALSE, "lost=%lld, ", LOG_RT_DATATYPE_U64, &lost);
				AVB_LOGRT_INFO(FALSE, LOG_RT_ITEM, FALSE, "bytes=%lld, ", LOG_RT_DATATYPE_U64, &bytes);
				AVB_LOGRT_INFO(FALSE, LOG_RT_ITEM, FALSE, "rxbuf=%d, ", LOG_RT_DATATYPE_U32, &rxbuf);
				AVB_LOGRT_INFO(FALSE, LOG_RT_ITEM, FALSE, "mqbuf=%d, ", LOG_RT_DATATYPE_U32, &mqbuf);
				AVB_LOGRT_INFO(FALSE, LOG_RT_ITEM, LOG_RT_END, "mqrdy=%d", LOG_RT_DATATYPE_U32, &mqrdy);

				openavbListenerAddStat(pTLState, TL_STAT_RX_CALLS, pListenerData->nReportCalls);
				openavbListenerAddStat(pTLState, TL_STAT_RX_FRAMES, pListenerData->nReportFrames);
				openavbListenerAddStat(pTLState, TL_STAT_RX_LOST, lost);
				openavbListenerAddStat(pTLState, TL_STAT_RX_BYTES, bytes);

				pListenerData->nReportCalls = 0;
				pListenerData->nReportFrames = 0;
				pListenerData->nextReportNS += (pCfg->report_seconds * NANOSECONDS_PER_SECOND);  
			}
		}

		if (nowNS > pListenerData->nextSecondNS) {
			pListenerData->nextSecondNS += NANOSECONDS_PER_SECOND;
			bRet = TRUE;
		}
	}
	else {
            SLEEP(1);
            bRet = TRUE;
	}

	AVB_TRACE_EXIT(AVB_TRACE_TL);
	return bRet;
}