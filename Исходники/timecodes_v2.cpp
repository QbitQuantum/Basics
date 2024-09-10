static void
handle_simpleblock(KaxSimpleBlock &simpleblock,
                   KaxCluster &cluster) {
    if (0 == simpleblock.NumberFrames())
        return;

    simpleblock.SetParent(cluster);

    std::vector<timecode_extractor_t>::iterator extractor = find_extractor_by_track_number(simpleblock.TrackNum());
    if (timecode_extractors.end() == extractor)
        return;

    // Pass the block to the extractor.
    size_t i;
    for (i = 0; simpleblock.NumberFrames() > i; ++i)
        extractor->m_timecodes.push_back(timecode_t(simpleblock.GlobalTimecode() + i * extractor->m_default_duration, extractor->m_default_duration));
}