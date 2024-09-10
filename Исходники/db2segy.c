void
initialize_trace_header(SEGYTraceHeader *header, int16_t segy_format)
{
	assert( sizeof(SEGYTraceHeader)==SEGY_TRACE_HEADER_SIZE );
	memset(header, '\0', sizeof(SEGYTraceHeader));
	header->lineSeq = htonl(1);
	header->event_number = htonl(1);
	header->channel_number = htonl(1);
	header->energySourcePt = htonl(1);
	header->cdpEns = htonl(0);
	header->traceInEnsemble = htonl(0);
	header->traceID = SEGY_TRACE_ID_DEAD;
	header->vertSum = htons(0);
	header->dataUse = htons(0);
	header->sourceToRecDist = htonl(0);
	header->recElevation = htonl(0);
	header->sourceSurfaceElevation = htonl(0);
	header->sourceDepth = htonl(0);
	header->datumElevRec = htonl(0);
	header->recWaterDepth = htonl(0);
	header->elevationScale = htons(1);
	header->coordScale = htons(1);
	header->sourceLongOrX = htonl(0);
	header->recLongOrX = htonl(0);
	header->coordUnits = SEGY_TRACE_COORDUNITS_LENGTH;  /* sets units to m */
	header->weatheringVelocity = htons(0);
	header->subWeatheringVelocity = htons(0);
	header->sourceUpholeTime = htons(0);
	header->sourceStaticCor = htons(0);
	header->totalStatic = htons(0);
	header->lagTimeA = htons(0);
	header->delay = htons(0);
	header->muteStart = htons(0);
	header->sampleLength = htons(0);
	header->deltaSample = htons(0);
	header->gainType = SEGY_TRACE_GAIN_UNKNOWN;
	header->gainConst = htons(0);
	header->correlated = htons(0);
	header->sweepStart = htons(0);
	header->sweepLength = htons(0);
	header->sweepType = htons(0);
	header->sweepTaperAtStart = htons(0);
	header->taperType = htons(0);
	header->aliasFreq = htons(0);
	header->notchFreq = htons(0);
	header->lowCutFreq = htons(0);
	header->lowCutSlope = htons(0);
	header->year = htons(0);
    /* SEG-Y "classic" supports only time basis codes 0-3. Antelope records
     * in UTC (which has leap second corrections). */
    if (ntohs(segy_format)>=0x0100) {
        header->timeBasisCode = SEGY_TRACE_TIMEBASIS_UTC;
    } else {
        header->timeBasisCode = SEGY_TRACE_TIMEBASIS_GMT;
    }
	header->traceWeightingFactor = htons(0);
	header->phoneRollPos1 = htons(0);
	header->gapSize = htons(0);
	header->taperOvertravel = htons(0);
	/*header->extrash[10] is pre-zero'd */
	header->samp_rate = htonl(0);
	/* Begin Pavlis/IRIS-PASSCAL non-standard extensions */
	if (ntohs(segy_format)<0x0100) {
		/* Always ieee floats in this program for now */
		header->data_form  = htons(5);
		header->trigyear   = htons(0);
		header->trigday    = htons(0);
		header->trighour   = htons(0);
		header->trigminute = htons(0);
		header->trigsecond = htons(0);
		header->trigmills  = htons(0);
		header->scale_fac = htonf(0);
		header->inst_no = htons(0);
		header->not_to_be_used = htons(0);
		header->num_samps = htonl(0);
		/* header->extra is pre-zeroed */
	}
	/* End Pavlis non-standard extension */
	header->reelSeq = htonl(1);
	header->horSum = htons(0);
	header->datumElemSource = htonl(0);
	header->sourceWaterDepth = htonl(0);
	header->sourceLatOrY = htonl(0);
	header->recLatOrY = htonl(0);
	header->recUpholeTime = htons(0);
	header->recStaticCor = htons(0);
	header->lagTimeB = htons(0);
	header->muteEnd = htons(0);
	header->sweepTaperAtEnd = htons(0);
	header->aliasSlope = htons(0);
	header->notchSlope = htons(0);
	header->hiCutFreq = htons(0);
	header->hiCutSlope = htons(0);
	header->day    = htons(0);
	header->hour   = htons(0);
	header->minute = htons(0);
	header->second = htons(0);
	header->phoneFirstTrace = htons(0);
	header->phoneLastTrace  = htons(0);
	header->m_secs = htons(0);
	header->initialGain = htons(0);
	header->sweepEnd    = htons(0);
}