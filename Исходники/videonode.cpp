VideoNode::VideoNode()
  : QSGGeometryNode()
{
    setFlags(OwnsGeometry | OwnsMaterial, true);
    setMaterialTypeSolidBlack();
}