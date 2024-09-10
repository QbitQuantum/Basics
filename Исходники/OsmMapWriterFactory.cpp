bool OsmMapWriterFactory::hasElementOutputStream(QString url)
{
  bool result = false;
  shared_ptr<OsmMapWriter> writer = createWriter(url);
  shared_ptr<ElementOutputStream> streamWriter = dynamic_pointer_cast<ElementOutputStream>(writer);
  if (streamWriter)
  {
    result = true;
  }

  return result;
}