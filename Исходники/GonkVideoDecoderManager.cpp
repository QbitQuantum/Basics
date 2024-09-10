static void
CopyGraphicBuffer(sp<GraphicBuffer>& aSource, sp<GraphicBuffer>& aDestination)
{
  void* srcPtr = nullptr;
  aSource->lock(GraphicBuffer::USAGE_SW_READ_OFTEN, &srcPtr);
  void* destPtr = nullptr;
  aDestination->lock(GraphicBuffer::USAGE_SW_WRITE_OFTEN, &destPtr);
  MOZ_ASSERT(srcPtr && destPtr);

  // Build PlanarYCbCrData for source buffer.
  PlanarYCbCrData srcData;
  switch (aSource->getPixelFormat()) {
    case HAL_PIXEL_FORMAT_YV12:
      // Android YV12 format is defined in system/core/include/system/graphics.h
      srcData.mYChannel = static_cast<uint8_t*>(srcPtr);
      srcData.mYSkip = 0;
      srcData.mYSize.width = aSource->getWidth();
      srcData.mYSize.height = aSource->getHeight();
      srcData.mYStride = aSource->getStride();
      // 4:2:0.
      srcData.mCbCrSize.width = srcData.mYSize.width / 2;
      srcData.mCbCrSize.height = srcData.mYSize.height / 2;
      srcData.mCrChannel = srcData.mYChannel + (srcData.mYStride * srcData.mYSize.height);
      // Aligned to 16 bytes boundary.
      srcData.mCbCrStride = Align(srcData.mYStride / 2, 16);
      srcData.mCrSkip = 0;
      srcData.mCbChannel = srcData.mCrChannel + (srcData.mCbCrStride * srcData.mCbCrSize.height);
      srcData.mCbSkip = 0;
      break;
    case GrallocImage::HAL_PIXEL_FORMAT_YCbCr_420_SP_VENUS:
      // Venus formats are doucmented in kernel/include/media/msm_media_info.h:
      srcData.mYChannel = static_cast<uint8_t*>(srcPtr);
      srcData.mYSkip = 0;
      srcData.mYSize.width = aSource->getWidth();
      srcData.mYSize.height = aSource->getHeight();
      // - Y & UV Width aligned to 128
      srcData.mYStride = aSource->getStride();
      srcData.mCbCrSize.width = (srcData.mYSize.width + 1) / 2;
      srcData.mCbCrSize.height = (srcData.mYSize.height + 1) / 2;
      // - Y height aligned to 32
      srcData.mCbChannel = srcData.mYChannel + (srcData.mYStride * Align(srcData.mYSize.height, 32));
      // Interleaved VU plane.
      srcData.mCbSkip = 1;
      srcData.mCrChannel = srcData.mCbChannel + 1;
      srcData.mCrSkip = 1;
      srcData.mCbCrStride = srcData.mYStride;
      break;
    default:
      NS_ERROR("Unsupported input gralloc image type. Should never be here.");
  }
  // Build PlanarYCbCrData for destination buffer.
  PlanarYCbCrData destData;
  destData.mYChannel = static_cast<uint8_t*>(destPtr);
  destData.mYSkip = 0;
  destData.mYSize.width = aDestination->getWidth();
  destData.mYSize.height = aDestination->getHeight();
  destData.mYStride = aDestination->getStride();
  // 4:2:0.
  destData.mCbCrSize.width = destData.mYSize.width / 2;
  destData.mCbCrSize.height = destData.mYSize.height / 2;
  destData.mCrChannel = destData.mYChannel + (destData.mYStride * destData.mYSize.height);
  // Aligned to 16 bytes boundary.
  destData.mCbCrStride = Align(destData.mYStride / 2, 16);
  destData.mCrSkip = 0;
  destData.mCbChannel = destData.mCrChannel + (destData.mCbCrStride * destData.mCbCrSize.height);
  destData.mCbSkip = 0;

  CopyYUV(srcData, destData);

  aSource->unlock();
  aDestination->unlock();
}