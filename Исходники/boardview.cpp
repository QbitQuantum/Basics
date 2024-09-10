 void BoardView::fillPolygon(QPainter& painter, float cellSize)
 {
   const QColor firstColor(Settings::firstPointColor());
   const QColor secondColor(Settings::secondPointColor());
   
   const auto& polygonVector = m_model->polygons();
   
   const QBrush firstPolyBrush(firstColor,
       BrushComboDelegate::getBrushStyle(Settings::firstFillStyle()));
   const QBrush secondPolyBrush(secondColor,
       BrushComboDelegate::getBrushStyle(Settings::secondFillStyle()));
   
   for (Polygon_ptr polygon : polygonVector)
   {
     QPolygon qPoly;
     for(const QPoint& point : polygon->points())
     {
       const QPoint& newPoint = point + QPoint{1, 1};
       qPoly << QPoint(newPoint) * cellSize;
     }
     QPainterPath path;
     path.addPolygon(qPoly);
     painter.fillPath(path, polygon->owner() == Owner::FIRST
         ? firstPolyBrush
         : secondPolyBrush);
   }
 }