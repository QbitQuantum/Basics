TopoDS_Shape StepLoader::get_shape() {
  TopoDS_Shape shape;
  STEPControl_Reader reader;
  reader.ReadFile(filename.toLocal8Bit());
  reader.TransferRoots();
  shape = reader.OneShape();
  BRepTools::Clean(shape);
  return shape;
}