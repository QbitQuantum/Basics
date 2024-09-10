QPixmap XCursorImage::icon () const {
  if (mIcon.isNull()) mIcon = createIcon();
  return mIcon;
}