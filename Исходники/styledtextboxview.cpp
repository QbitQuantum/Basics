void StyledTextboxView::configureObject(void)
{
  QRectF rect;
  QPolygonF pol;
  QPointF pnt;

  this->__configureObject();
  fold->setBrush(box->brush());
  fold->setPen(box->pen());

  rect=box->boundingRect();
  pol=box->polygon();

  if(rect.height() < fold->boundingRect().height())
    rect.setHeight(fold->boundingRect().height() + (2 * VERT_SPACING));

  this->resizePolygon(pol, rect.width() + fold->boundingRect().width(), rect.height());

  pnt=pol.at(2);
  pol.remove(2);
  pol.insert(2, QPointF(pnt.x(), roundf(pnt.y() - fold->boundingRect().height())));
  pol.insert(3, QPointF(roundf(pnt.x() - fold->boundingRect().width()), pnt.y()));
  box->setPolygon(pol);

  rect=box->boundingRect();
  fold->setPos(rect.width() - fold->boundingRect().width(),
               rect.height() - fold->boundingRect().height());

  this->configureObjectShadow();
  this->configureObjectSelection();
}