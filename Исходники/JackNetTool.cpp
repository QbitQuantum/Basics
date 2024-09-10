 SERVER_EXPORT void TransportDataHToN ( net_transport_data_t* src_params, net_transport_data_t* dst_params )
 {
     dst_params->fNewState = htonl(src_params->fNewState);
     dst_params->fTimebaseMaster = htonl(src_params->fTimebaseMaster);
     dst_params->fState = htonl(src_params->fState);
     dst_params->fPosition.unique_1 = htonll(src_params->fPosition.unique_1);
     dst_params->fPosition.usecs = htonl(src_params->fPosition.usecs);
     dst_params->fPosition.frame_rate = htonl(src_params->fPosition.frame_rate);
     dst_params->fPosition.frame = htonl(src_params->fPosition.frame);
     dst_params->fPosition.valid = (jack_position_bits_t)htonl((uint32_t)src_params->fPosition.valid);
     dst_params->fPosition.bar = htonl(src_params->fPosition.bar);
     dst_params->fPosition.beat = htonl(src_params->fPosition.beat);
     dst_params->fPosition.tick = htonl(src_params->fPosition.tick);
     dst_params->fPosition.bar_start_tick = htonll((uint64_t)src_params->fPosition.bar_start_tick);
     dst_params->fPosition.beats_per_bar = htonl((uint32_t)src_params->fPosition.beats_per_bar);
     dst_params->fPosition.beat_type = htonl((uint32_t)src_params->fPosition.beat_type);
     dst_params->fPosition.ticks_per_beat = htonll((uint64_t)src_params->fPosition.ticks_per_beat);
     dst_params->fPosition.beats_per_minute = htonll((uint64_t)src_params->fPosition.beats_per_minute);
     dst_params->fPosition.frame_time = htonll((uint64_t)src_params->fPosition.frame_time);
     dst_params->fPosition.next_time = htonll((uint64_t)src_params->fPosition.next_time);
     dst_params->fPosition.bbt_offset = htonl(src_params->fPosition.bbt_offset);
     dst_params->fPosition.audio_frames_per_video_frame = htonl((uint32_t)src_params->fPosition.audio_frames_per_video_frame);
     dst_params->fPosition.video_offset = htonl(src_params->fPosition.video_offset);
     dst_params->fPosition.unique_2 = htonll(src_params->fPosition.unique_2);
 }