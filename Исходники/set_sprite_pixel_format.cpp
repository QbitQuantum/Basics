void SetSpritePixelFormat::revert(ObjectsContainer* objects, UndoersCollector* redoers)
{
  Sprite* sprite = objects->getObjectT<Sprite>(m_spriteId);

  // Push another SetSpritePixelFormat as redoer
  redoers->pushUndoer(new SetSpritePixelFormat(objects, sprite));

  sprite->setPixelFormat(static_cast<PixelFormat>(m_format));
}