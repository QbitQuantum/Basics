void DicomSurfaceSegmentationLoad::_updateOutputFields()
{
  handleNotificationOff();

  _outPointSetPositions.clear();
  _outLineSetPositions.clear();
  //_outLineSetConnections.clear();
  _cleanup();

  for (std::size_t i=0; i<_dicomPointSetsVector.size(); i++)
  {
	  _addPointSetToOutput((int)i);
  } 
  
	for (std::size_t i=0; i<_dicomLineSetsVector.size(); i++)
  {
		_addLineSetToOutput((int)i);
	}
  
	for (std::size_t i=0; i<_dicomMeshesVector.size(); i++)
  {
		_addMeshToOutput((int)i);
	} 
	
  handleNotificationOn();

  _outPointSetPositionsFld->touch();
  _outLineSetPositionsFld->touch();
  //_outLineSetConnectionsFld->touch();
  _notifyObservers();
}