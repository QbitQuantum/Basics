void GeometryManager::flushAllGeometries()
{
  size_t i;
  
  flushUnusedGeometry();
  
  for (i = 0; i < geometryCollection.length(); i++)
  {
    deleteObject(geometryCollection(i)->getMedia());
    deleteObject(geometryCollection(i));
  }
  
  geometryCollection.clear();
  
  if (i) Logger::writeInfoLog(String("Flushed ") + int(i) + String(" active geometries"));
}