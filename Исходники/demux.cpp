Packet* Demux::Read()
{
  if(ConnectionLost() || Aborting()) {
    return NULL;
  }

  Packet* p = NULL;
  MsgPacket* pkt = NULL;
  m_lock.Lock();

  if(m_queuelocked) {
      m_lock.Unlock();
      return m_client->AllocatePacket(0);
  }

  if (m_buffer != NULL) {
    pkt = m_buffer->get();

    if (pkt == NULL) {
      m_lock.Unlock();
      m_cond.Wait(100);
      m_lock.Lock();
      pkt = m_buffer->get();
    }

    if (pkt != NULL) {
      pkt->rewind();

      switch (pkt->getMsgID()) {
      case XVDR_STREAM_MUXPKT: {
        uint16_t id = pkt->get_U16();
        int64_t pts = pkt->get_S64();
        int64_t dts = pkt->get_S64();
        uint32_t duration = pkt->get_U32();
        uint32_t length = pkt->get_U32();
        uint8_t* payload = pkt->consume(length);
        Stream& stream = m_streams[id];

        if (stream.PhysicalId != id) {
          m_client->Log(DEBUG, "stream id %i not found", id);
        } else {
          p = m_client->AllocatePacket(length);
          m_client->SetPacketData(p, payload, stream.Index, dts, pts, duration);
        }
        break;
      }
      case XVDR_STREAM_CHANGE: {
        StreamChange(pkt);
        p = m_client->StreamChange(m_streams);
        break;
      }
      }
    }

    if (p == NULL) {
      p = m_client->AllocatePacket(0);
    }

    m_buffer->release(pkt);

    m_lock.Unlock();
    return p;
  }

  bool bEmpty = m_queue.empty();

  // empty queue -> wait for packet
  if (bEmpty) {
         m_lock.Unlock();

         // request packets in timeshift mode
         if(m_timeshiftmode)
         {
           MsgPacket req(XVDR_CHANNELSTREAM_REQUEST, XVDR_CHANNEL_STREAM);
           if(!Session::TransmitMessage(&req))
             return NULL;
         }

         m_cond.Wait(100);

         m_lock.Lock();
         bEmpty = m_queue.empty();
  }

  if (!bEmpty)
  {
    p = m_queue.front();
    m_queue.pop();
  }

  m_lock.Unlock();

  if(p == NULL) {
    p = m_client->AllocatePacket(0);
  }

  return p;
}