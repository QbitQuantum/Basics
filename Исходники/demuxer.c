void cTSDemuxer::SendPacket(sStreamPacket *pkt)
{
  int64_t dts = (pkt->dts == DVD_NOPTS_VALUE) ? pkt->dts : Rescale(pkt->dts);
  int64_t pts = (pkt->pts == DVD_NOPTS_VALUE) ? pkt->pts : Rescale(pkt->pts);

  // Rescale
  pkt->type     = m_type;
  pkt->content  = m_content;
  pkt->pid      = GetPID();
  pkt->dts      = dts;
  pkt->pts      = pts;
  pkt->duration = Rescale(pkt->duration);

  m_Streamer->sendStreamPacket(pkt);
}