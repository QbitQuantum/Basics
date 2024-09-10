  BULKIO::StreamSRISequence * InSDDSPort::attachedSRIs()
  {
    boost::mutex::scoped_lock lock(sriUpdateLock);
    BULKIO::StreamSRISequence_var sris = new BULKIO::StreamSRISequence();
    sris->length(currentHs.size());
    SriMap::iterator sriIter;
    unsigned int idx = 0;

    sriIter = currentHs.begin();
    while (sriIter != currentHs.end()) {
      sris[idx++] = (*sriIter).second.first;
      sriIter++;
    }
    return sris._retn();
  }