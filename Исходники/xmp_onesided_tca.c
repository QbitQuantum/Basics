static void _XMP_tca_ring_buf_recv(tca_ring_buf_t *ring_buf, int *tag, int *data)
{
  psn_t local_recv_psn = ring_buf->psn_pairs[1]; //1: local_recv
  int buf_pos = local_recv_psn % RING_SIZE;

  _XMP_tca_lock();

#ifdef _USE_NOTIFY_TO_WAIT_PACKET
  //wait notify for recv_buf
  const int buf_wait_slot = _wait_slot_offset + buf_pos;
  TCA_CHECK(tcaWaitDMARecvDesc(&(ring_buf->remote_psn_pairs_handle), buf_wait_slot, _packet_wait_tag));
#else
  //wait until (remote_send_psn > local_recv_psn) become true
  volatile psn_t* remote_send_psn_p = &(ring_buf->psn_pairs[2]); //2: remote_send
  while(*remote_send_psn_p <= local_recv_psn){
    ++spin_wait_count;
    _mm_pause();
  }
#endif

  //copy recved data
  *tag = ring_buf->recv_buffer[buf_pos].tag;
  *data = ring_buf->recv_buffer[buf_pos].data;

  //fprintf(stderr, "recv: psn=%ull, tag=%d, data=%d\n", local_recv_psn, *tag, *data);

  //update local_recv_psn
  ring_buf->psn_pairs[1] = ++local_recv_psn;

  if(local_recv_psn - ring_buf->last_send_local_recv_psn >= (RING_SIZE/2)){
    //send local psn pair
    const int psn_wait_slot = _wait_slot_offset + RING_SIZE;
    ring_buf->last_send_local_recv_psn = ring_buf->psn_pairs[1];
    TCA_CHECK(tcaDescSet(ring_buf->psn_desc, _dmac_channel));
    TCA_CHECK(tcaStartDMADesc(_dmac_channel));
    TCA_CHECK(tcaWaitDMARecvDesc(&(ring_buf->local_psn_pairs_handle), psn_wait_slot, _psn_wait_tag));
    TCA_CHECK(tcaWaitDMAC(_dmac_channel)); //important
  }

  //printf("psns: %llu, %llu, %llu, %llu\n", ring_buf->psn_pairs[0],ring_buf->psn_pairs[1],ring_buf->psn_pairs[2],ring_buf->psn_pairs[3]);
  _XMP_tca_unlock();
}