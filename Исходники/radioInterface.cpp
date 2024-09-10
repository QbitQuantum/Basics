bool RadioInterface::driveReceiveRadio()
{
  radioVector *burst = NULL;

  if (!mOn)
    return false;

  pullBuffer();

  GSM::Time rcvClock = mClock.get();
  rcvClock.decTN(receiveOffset);
  unsigned tN = rcvClock.TN();
  int recvSz = recvCursor;
  int readSz = 0;
  const int symbolsPerSlot = gSlotLen + 8;
  int burstSize = (symbolsPerSlot + (tN % 4 == 0)) * mSPSRx;

  /* 
   * Pre-allocate head room for the largest correlation size
   * so we can later avoid a re-allocation and copy
   * */
  size_t head = GSM::gRACHSynchSequence.size();

  /*
   * Form receive bursts and pass up to transceiver. Use repeating
   * pattern of 157-156-156-156 symbols per timeslot
   */
  while (recvSz > burstSize) {
    for (size_t i = 0; i < mChans; i++) {
      burst = new radioVector(rcvClock, burstSize, head, mMIMO);

      for (size_t n = 0; n < mMIMO; n++) {
        unRadioifyVector((float *)
                         (recvBuffer[mMIMO * i + n]->begin() + readSz),
                         *burst->getVector(n));
      }

      if (mReceiveFIFO[i].size() < 32)
        mReceiveFIFO[i].write(burst);
      else
        delete burst;
    }

    mClock.incTN();
    rcvClock.incTN();
    readSz += burstSize;
    recvSz -= burstSize;

    tN = rcvClock.TN();

    burstSize = (symbolsPerSlot + (tN % 4 == 0)) * mSPSRx;
  }

  if (readSz > 0) {
    for (size_t i = 0; i < recvBuffer.size(); i++) {
      memmove(recvBuffer[i]->begin(),
              recvBuffer[i]->begin() + readSz,
              (recvCursor - readSz) * 2 * sizeof(float));
    }

    recvCursor -= readSz;
  }

  return true;
}