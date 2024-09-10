void SetLayerFlags::revert(ObjectsContainer* objects, UndoersCollector* redoers)
{
  Layer* layer = objects->getObjectT<Layer>(m_layerId);

  // Push another SetLayerFlags as redoer
  redoers->pushUndoer(new SetLayerFlags(objects, layer));

  layer->setFlags(m_flags);
}