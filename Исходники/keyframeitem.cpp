KeyFrameItem::KeyFrameItem()
{
  setPixmap(QPixmap(s_keyFramePixmap));
  setFlags(ItemIsMovable);
  setCacheMode(DeviceCoordinateCache);
}