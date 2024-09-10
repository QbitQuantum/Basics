int FDK_QmfDomain_InitFilterBank(HANDLE_FDK_QMF_DOMAIN qd, UINT extra_flags) {
  FDK_ASSERT(qd != NULL);
  int err = 0;
  int ch, ts;
  HANDLE_FDK_QMF_DOMAIN_GC gc = &qd->globalConf;
  int noCols = gc->nQmfTimeSlots;
  int lsb = gc->nBandsAnalysis;
  int usb = fMin((INT)gc->nBandsSynthesis, 64);
  int nProcBands = gc->nQmfProcBands;
  FDK_ASSERT(nProcBands % ALIGNMENT_DEFAULT == 0);

  if (extra_flags & QMF_FLAG_MPSLDFB) {
    gc->flags &= ~QMF_FLAG_CLDFB;
    gc->flags |= QMF_FLAG_MPSLDFB;
  }
  for (ch = 0; ch < gc->nInputChannels; ch++) {
    /* distribute memory to slots array */
    FIXP_DBL *ptrOv =
        qd->QmfDomainIn[ch].pOverlapBuffer; /* persistent memory for overlap */
    if ((ptrOv == NULL) && (gc->nQmfOvTimeSlots != 0)) {
      err = 1;
      return err;
    }
    /* This assumes the workbuffer defined for ch0 is the big one being used to
     * hold one full frame of QMF data. */
    FIXP_DBL **ptr =
        qd->QmfDomainIn[fMin(ch, fMax((INT)gc->nQmfProcChannels - 1, 0))]
            .pWorkBuffer; /* non-persistent workbuffer */
    USHORT workBufferOffset =
        qd->QmfDomainIn[fMin(ch, fMax((INT)gc->nQmfProcChannels - 1, 0))]
            .workBufferOffset;
    USHORT workBufferSectSize =
        qd->QmfDomainIn[fMin(ch, fMax((INT)gc->nQmfProcChannels - 1, 0))]
            .workBufferSectSize;

    if ((ptr == NULL) && (gc->nQmfTimeSlots != 0)) {
      err = 1;
      return err;
    }

    qd->QmfDomainIn[ch].pGlobalConf = gc;
    for (ts = 0; ts < gc->nQmfOvTimeSlots; ts++) {
      qd->QmfDomainIn[ch].hQmfSlotsReal[ts] = ptrOv;
      ptrOv += nProcBands;
      qd->QmfDomainIn[ch].hQmfSlotsImag[ts] = ptrOv;
      ptrOv += nProcBands;
    }
    for (; ts < (gc->nQmfOvTimeSlots + gc->nQmfTimeSlots); ts++) {
      qd->QmfDomainIn[ch].hQmfSlotsReal[ts] = FDK_getWorkBuffer(
          ptr, workBufferOffset, workBufferSectSize, nProcBands);
      workBufferOffset += nProcBands;
      qd->QmfDomainIn[ch].hQmfSlotsImag[ts] = FDK_getWorkBuffer(
          ptr, workBufferOffset, workBufferSectSize, nProcBands);
      workBufferOffset += nProcBands;
    }
    err |= qmfInitAnalysisFilterBank(
        &qd->QmfDomainIn[ch].fb, qd->QmfDomainIn[ch].pAnaQmfStates, noCols,
        (qd->QmfDomainIn[ch].fb.lsb == 0) ? lsb : qd->QmfDomainIn[ch].fb.lsb,
        (qd->QmfDomainIn[ch].fb.usb == 0) ? usb : qd->QmfDomainIn[ch].fb.usb,
        gc->nBandsAnalysis, gc->flags | extra_flags);
  }

  for (ch = 0; ch < gc->nOutputChannels; ch++) {
    FIXP_DBL outGain_m = qd->QmfDomainOut[ch].fb.outGain_m;
    int outGain_e = qd->QmfDomainOut[ch].fb.outGain_e;
    int outScale = qmfGetOutScalefactor(&qd->QmfDomainOut[ch].fb);
    err |= qmfInitSynthesisFilterBank(
        &qd->QmfDomainOut[ch].fb, qd->QmfDomainOut[ch].pSynQmfStates, noCols,
        (qd->QmfDomainOut[ch].fb.lsb == 0) ? lsb : qd->QmfDomainOut[ch].fb.lsb,
        (qd->QmfDomainOut[ch].fb.usb == 0) ? usb : qd->QmfDomainOut[ch].fb.usb,
        gc->nBandsSynthesis, gc->flags | extra_flags);
    if (outGain_m != (FIXP_DBL)0) {
      qmfChangeOutGain(&qd->QmfDomainOut[ch].fb, outGain_m, outGain_e);
    }
    if (outScale) {
      qmfChangeOutScalefactor(&qd->QmfDomainOut[ch].fb, outScale);
    }
  }

  return err;
}