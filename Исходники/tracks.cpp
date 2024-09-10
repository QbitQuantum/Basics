static void
handle_simpleblock(KaxSimpleBlock &simpleblock,
                   KaxCluster &cluster) {
  if (0 == simpleblock.NumberFrames())
    return;

  simpleblock.SetParent(cluster);

  // Do we need this block group?
  xtr_base_c *extractor = NULL;
  size_t i;
  for (i = 0; i < extractors.size(); i++)
    if (simpleblock.TrackNum() == extractors[i]->m_track_num) {
      extractor = extractors[i];
      break;
    }

  if (NULL == extractor)
    return;

  int64_t duration = extractor->m_default_duration * simpleblock.NumberFrames();

  for (i = 0; i < simpleblock.NumberFrames(); i++) {
    int64_t this_timecode, this_duration;

    if (0 > duration) {
      this_timecode = simpleblock.GlobalTimecode();
      this_duration = duration;
    } else {
      this_timecode = simpleblock.GlobalTimecode() + i * duration / simpleblock.NumberFrames();
      this_duration = duration / simpleblock.NumberFrames();
    }

    DataBuffer &data = simpleblock.GetBuffer(i);
    memory_cptr frame(new memory_c(data.Buffer(), data.Size(), false));
    extractor->handle_frame(frame, NULL, this_timecode, this_duration, -1, -1, simpleblock.IsKeyframe(), simpleblock.IsDiscardable(), false);
  }
}