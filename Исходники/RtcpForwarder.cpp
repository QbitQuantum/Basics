int RtcpForwarder::addREMB(char* buf, int len, uint32_t bitrate) {
  buf+=len;
  RtcpHeader theREMB;
  theREMB.setPacketType(RTCP_PS_Feedback_PT);
  theREMB.setBlockCount(RTCP_AFB);
  memcpy(&theREMB.report.rembPacket.uniqueid, "REMB", 4);

  theREMB.setSSRC(rtcpSink_->getVideoSinkSSRC());
  theREMB.setSourceSSRC(rtcpSource_->getVideoSourceSSRC());
  theREMB.setLength(5);
  theREMB.setREMBBitRate(bitrate);
  theREMB.setREMBNumSSRC(1);
  theREMB.setREMBFeedSSRC(rtcpSource_->getVideoSourceSSRC());
  int rembLength = (theREMB.getLength()+1)*4;

  memcpy(buf, reinterpret_cast<uint8_t*>(&theREMB), rembLength);
  return (len+rembLength);
}