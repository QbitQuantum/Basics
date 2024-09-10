QPixmap XCursorThemeData::icon () const {
  if (mIcon.isNull()) mIcon = createIcon();
  return mIcon;
}