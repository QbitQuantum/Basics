void
nsShmImage::Put(const mozilla::LayoutDeviceIntRegion& aRegion)
{
  AutoTArray<xcb_rectangle_t, 32> xrects;
  xrects.SetCapacity(aRegion.GetNumRects());

  for (auto iter = aRegion.RectIter(); !iter.Done(); iter.Next()) {
    const mozilla::LayoutDeviceIntRect &r = iter.Get();
    xcb_rectangle_t xrect = { (short)r.x, (short)r.y, (unsigned short)r.width, (unsigned short)r.height };
    xrects.AppendElement(xrect);
  }

  if (!mGC) {
    mGC = xcb_generate_id(mConnection);
    xcb_create_gc(mConnection, mGC, mWindow, 0, nullptr);
  }

  xcb_set_clip_rectangles(mConnection, XCB_CLIP_ORDERING_YX_BANDED, mGC, 0, 0,
                          xrects.Length(), xrects.Elements());

  if (mPixmap != XCB_NONE) {
    mLastRequest = xcb_copy_area_checked(mConnection, mPixmap, mWindow, mGC,
                                         0, 0, 0, 0, mSize.width, mSize.height);
  } else {
    mLastRequest = xcb_shm_put_image_checked(mConnection, mWindow, mGC,
                                             mSize.width, mSize.height,
                                             0, 0, mSize.width, mSize.height,
                                             0, 0, mDepth,
                                             XCB_IMAGE_FORMAT_Z_PIXMAP, 0,
                                             mShmSeg, 0);
  }

  xcb_flush(mConnection);
}