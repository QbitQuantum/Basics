void
SourceSurfaceD2D1::EnsureRealizedBitmap()
{
  if (mRealizedBitmap) {
    return;
  }

  RefPtr<ID2D1DeviceContext> dc;
  Factory::GetD2D1Device()->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, byRef(dc));

  D2D1_BITMAP_PROPERTIES1 props;
  props.dpiX = 96;
  props.dpiY = 96;
  props.pixelFormat = D2DPixelFormat(mFormat);
  props.colorContext = nullptr;
  props.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET;
  dc->CreateBitmap(D2DIntSize(mSize), nullptr, 0, props, (ID2D1Bitmap1**)byRef(mRealizedBitmap));

  dc->SetTarget(mRealizedBitmap);

  dc->BeginDraw();
  dc->DrawImage(mImage);
  dc->EndDraw();
}