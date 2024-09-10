void
tag_target_c::account_simple_block(KaxSimpleBlock &simple_block,
                                   KaxCluster &cluster) {
  auto num_frames = simple_block.NumberFrames();
  auto stats_itr  = m_track_statistics_by_number.find(simple_block.TrackNum());

  if (!num_frames || (stats_itr == m_track_statistics_by_number.end()))
    return;

  simple_block.SetParent(cluster);

  auto frame_duration  = m_default_durations_by_number[simple_block.TrackNum()];
  auto first_timestamp = simple_block.GlobalTimecode();

  for (int idx = 0; idx < static_cast<int>(num_frames); ++idx) {
    auto &data_buffer = simple_block.GetBuffer(idx);
    stats_itr->second.account(first_timestamp + idx * frame_duration, frame_duration, data_buffer.Size());
  }
}