void PAData::paintToScene(QGraphicsScene &scene, QGraphicsItemGroup *group)
{
    CODEBOOK *ts = static_cast<CODEBOOK*>(this->associatedData.data()->getData());
    PARTITIONING *pa = &this->partition;

    CONVEXHULLSET *hull = NULL;
    ConstructConvexHulls(ts, pa, &hull);

    QGraphicsItem *item = NULL;
    CONVEXVERTEX* CV;

    for (int index=0; index < CHS_size(hull); index++ )
    {
        CV = CHS_hullfirst(hull, index);
        if(!CV) continue;

        QPointF start_point = QPointF(VectorScalar(ts, CV->index, 0), VectorScalar(ts, CV->index, 1));
        QPainterPath path = QPainterPath(start_point);

        CV = CV_next(CV);
        while( CV != NULL )
        {
            QPointF point = QPointF(VectorScalar(ts, CV->index, 0), VectorScalar(ts, CV->index, 1));
            path.lineTo(point);

            CV = CV_next(CV);
        }

        item = new QGraphicsPathItem(path);

        if (group) group->addToGroup(item);
        else scene.addItem(item);
    }

    if (hull != NULL) FreeConvexHulls(hull);
}