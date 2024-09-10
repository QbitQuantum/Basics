void ThermalZonesController::onRemoveObject(openstudio::model::ModelObject modelObject)
{
  // DLM: should this check isRemovable?
  modelObject.remove();
}