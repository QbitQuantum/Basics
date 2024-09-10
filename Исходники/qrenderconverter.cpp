void addLineEndingToItem(QGraphicsPathItem* item, const CLLineEnding* ending, const CLGroup* group, const CLRenderResolver* resolver, QPointF point, QPointF second, QGraphicsItemGroup* itemGroup)
{
  const CLGroup* lineGroup = ending->getGroup();

  for (size_t i = 0; i < lineGroup->getNumElements(); ++i)
    {
      const CLPolygon* poly = dynamic_cast<const CLPolygon*>(lineGroup->getElement(i));
      const CLRenderCurve* rcurve = dynamic_cast<const CLRenderCurve*>(lineGroup->getElement(i));
      const CLEllipse* ellipse = dynamic_cast<const CLEllipse*>(lineGroup->getElement(i));
      const CLRectangle* rect = dynamic_cast<const CLRectangle*>(lineGroup->getElement(i));

      if (rcurve != NULL)
        {
          QPainterPath path = item->path();
          QPainterPath& linePath = *getPath(rcurve, ending->getBoundingBox());
          applyRotationalMapping(linePath, ending, point, second);
          linePath.translate(point);
          path.addPath(linePath);
          item->setPath(path);
        }
      else if (poly != NULL)
        {
          QPainterPath path = item->path();
          QPainterPath& linePath = *getPath(poly, ending->getBoundingBox());
          applyRotationalMapping(linePath, ending, point, second);
          linePath.translate(point);
          path.addPath(linePath);
          item->setPath(path);

          if (poly->isSetFill() || group->isSetFill())
            {
              QBrush* brush = getBrush(poly, ending->getGroup(), resolver, ending->getBoundingBox());
              QPen* pen = getPen(poly, ending->getGroup(), resolver, ending->getBoundingBox());

              linePath.setFillRule(Qt::WindingFill);

              if (poly->isSetFillRule())
                {
                  switch (poly->getFillRule())
                    {
                      case CLGraphicalPrimitive2D::EVENODD:
                        linePath.setFillRule(Qt::OddEvenFill);
                        break;

                      case CLGraphicalPrimitive2D::NONZERO:
                      default:
                        linePath.setFillRule(Qt::WindingFill);
                        break;
                    }
                }

              if (group->isSetFillRule())
                {
                  switch (group->getFillRule())
                    {
                      case CLGraphicalPrimitive2D::EVENODD:
                        linePath.setFillRule(Qt::OddEvenFill);
                        break;

                      case CLGraphicalPrimitive2D::NONZERO:
                      default:
                        linePath.setFillRule(Qt::WindingFill);
                        break;
                    }
                }

              QGraphicsPathItem* outline = new QGraphicsPathItem(linePath);

              outline->setPen(*pen);
              outline->setBrush(*brush);
              itemGroup->addToGroup(outline);
            }
        }
      else if (ellipse != NULL)
        {
          QPainterPath path = item->path();
          QPainterPath& linePath = *getPath(ellipse, ending->getBoundingBox());
          applyRotationalMapping(linePath, ending, point, second);
          linePath.translate(point);
          path.addPath(linePath);
          item->setPath(path);

          if (ellipse->isSetFill() || group->isSetFill())
            {
              QBrush* brush = getBrush(ellipse, ending->getGroup(), resolver, ending->getBoundingBox());
              QPen* pen = getPen(ellipse, ending->getGroup(), resolver, ending->getBoundingBox());
              QGraphicsPathItem* outline = new QGraphicsPathItem(linePath);
              outline->setPen(*pen);
              outline->setBrush(*brush);
              itemGroup->addToGroup(outline);
            }
        }
      else if (rect != NULL)
        {
          QPainterPath path = item->path();
          QPainterPath& linePath = *getPath(rect, ending->getBoundingBox());
          applyRotationalMapping(linePath, ending, point, second);
          linePath.translate(point);
          path.addPath(linePath);
          item->setPath(path);

          if (rect->isSetFill() || group->isSetFill())
            {
              QBrush* brush = getBrush(rect, ending->getGroup(), resolver, ending->getBoundingBox());
              QPen* pen = getPen(rect, ending->getGroup(), resolver, ending->getBoundingBox());
              QGraphicsPathItem* outline = new QGraphicsPathItem(linePath);
              outline->setPen(*pen);
              outline->setBrush(*brush);
              itemGroup->addToGroup(outline);
            }
        }
    }
}