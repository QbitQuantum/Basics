void EraserTool::itemPressed(QGraphicsItem *item, const TupBrushManager *brush, const QPointF &pos)
{
    QList<QGraphicsItem *> collides = item->collidingItems();
    
    if (collides.count() == 0) {
        QRect intersectRect(pos.x() - (brush->pen().width()/2), pos.y() - (brush->pen().width())/2, 
                    brush->pen().width(), brush->pen().width());
        
        TupPathItem *path = qgraphicsitem_cast<TupPathItem*>(item);
        
        if (!path) {
            /*
             QString conv = "<convert type=\"2\" />"; // to path type
             TupProjectRequest *event = new TupProjectRequest(TupProjectRequest::Convert, 
             scene->currentSceneIndex(), scene->currentLayerIndex(), scene->currentFrameIndex(), 
             scene->currentFrame()->graphics().indexOf(item), conv);
             addProjectRequest(event);
            */
        } else {
            QPainterPath ppath = path->path();
        }
    }
}