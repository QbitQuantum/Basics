void NodeClickableAreasTreeDrawingListener::afterDrawNode(const DrawNodeEvent& event)
{
  const TreeDrawing* td = event.getTreeDrawing();
  double r = td->getDisplaySettings().pointArea;
  GraphicDevice* gd = event.getGraphicDevice();
  Cursor cursor     = event.getCursor();
  gd->drawRect(cursor.getX() - r, cursor.getY() - r, 2 * r, 2 * r);
}