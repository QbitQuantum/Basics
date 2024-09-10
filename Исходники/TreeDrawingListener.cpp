void NodesIdTreeDrawingListener::afterDrawNode(const DrawNodeEvent& event)
{
  GraphicDevice* gd = event.getGraphicDevice();
  Cursor cursor     = event.getCursor();
  Font fontBck      = gd->getCurrentFont();
  if (settings_)
    gd->setCurrentFont(settings_->fontNodesId);
  string name = "#" + TextTools::toString(event.getNodeId());
  gd->drawText(cursor.getX(), cursor.getY(), name, cursor.getHPos(), cursor.getVPos(), cursor.getAngle());
  gd->setCurrentFont(fontBck);
}