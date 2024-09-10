void DxScienceDataRequest::marshall()
{
    SseMsg::marshall(sendBaselines);          // bool_t
    SseMsg::marshall(sendBaselineStatistics); // bool_t
    SseMsg::marshall(checkBaselineWarningLimits); // bool_t
    SseMsg::marshall(checkBaselineErrorLimits); // bool_t
    SseMsg::marshall(sendComplexAmplitudes);  // bool_t
    HTONL(baselineReportingHalfFrames);
    marshallReqType(requestType);
    NTOHL(subchannel);
    NTOHD(rfFreq);
}