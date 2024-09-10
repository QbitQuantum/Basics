void WEBPImageDecoder::initializeNewFrame(size_t index) {
  if (!(m_formatFlags & ANIMATION_FLAG)) {
    ASSERT(!index);
    return;
  }
  WebPIterator animatedFrame;
  WebPDemuxGetFrame(m_demux, index + 1, &animatedFrame);
  ASSERT(animatedFrame.complete == 1);
  ImageFrame* buffer = &m_frameBufferCache[index];
  IntRect frameRect(animatedFrame.x_offset, animatedFrame.y_offset,
                    animatedFrame.width, animatedFrame.height);
  buffer->setOriginalFrameRect(
      intersection(frameRect, IntRect(IntPoint(), size())));
  buffer->setDuration(animatedFrame.duration);
  buffer->setDisposalMethod(animatedFrame.dispose_method ==
                                    WEBP_MUX_DISPOSE_BACKGROUND
                                ? ImageFrame::DisposeOverwriteBgcolor
                                : ImageFrame::DisposeKeep);
  buffer->setAlphaBlendSource(animatedFrame.blend_method == WEBP_MUX_BLEND
                                  ? ImageFrame::BlendAtopPreviousFrame
                                  : ImageFrame::BlendAtopBgcolor);
  buffer->setRequiredPreviousFrameIndex(
      findRequiredPreviousFrame(index, !animatedFrame.has_alpha));
  WebPDemuxReleaseIterator(&animatedFrame);
}