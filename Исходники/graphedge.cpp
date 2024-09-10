//void GraphEdge::adjust()
void GraphEdge::updateGeometry()
{
    if (!sourceNode_ || !destNode_) return;

    //sourceNode_->adjustSize();
    //destNode_->adjustSize();

    // line from center of sourceNode_ to center of destNode_
    QRectF sSBR (sourceNode_->sceneBoundingRect());
    QRectF dSBR (destNode_->sceneBoundingRect());
    QLineF centerline(sSBR.center(), dSBR.center());

    // set the source and destination points
    if(!sSBR.intersects(dSBR)) {
        QPointF po;
        if(QLineF::BoundedIntersection == centerline.intersect(QLineF(sSBR.topLeft(), sSBR.topRight()), &po)) sourcePoint = po;
        else if(QLineF::BoundedIntersection == centerline.intersect(QLineF(sSBR.bottomRight(), sSBR.topRight()), &po)) sourcePoint = po;
        else if(QLineF::BoundedIntersection == centerline.intersect(QLineF(sSBR.bottomLeft(), sSBR.bottomRight()), &po)) sourcePoint = po;
        else if(QLineF::BoundedIntersection == centerline.intersect(QLineF(sSBR.topLeft(), sSBR.bottomLeft()), &po)) sourcePoint = po;
        if(QLineF::BoundedIntersection == centerline.intersect(QLineF(dSBR.topLeft(), dSBR.topRight()), &po)) destPoint = po;
        else if(QLineF::BoundedIntersection == centerline.intersect(QLineF(dSBR.bottomRight(), dSBR.topRight()), &po)) destPoint = po;
        else if(QLineF::BoundedIntersection == centerline.intersect(QLineF(dSBR.bottomLeft(), dSBR.bottomRight()), &po)) destPoint = po;
        else if(QLineF::BoundedIntersection == centerline.intersect(QLineF(dSBR.topLeft(), dSBR.bottomLeft()), &po)) destPoint = po;
    } else {
        sourcePoint = destPoint = (sSBR.bottomLeft().y() < dSBR.bottomLeft().y()) ? sSBR.bottomLeft() : dSBR.bottomLeft();
    }
    QLineF line(sourcePoint, destPoint);
    // set label centered in the middle of the arrow
    QRectF label (label_->boundingRect());
    label.translate(line.pointAt(0.5));
    if(sourcePoint != destPoint) label.translate(-label.width()/2, -label.height()/2);

    // avoid overlapping
    bool overlapped;
    while(true) {
        overlapped = false;
        Graph *graph = reinterpret_cast<Graph *>(scene());
        if(!graph) break;
        Edges::const_iterator i = graph->edges_.constBegin();
        while (i != graph->edges_.constEnd()) {
            GraphEdge *e = i.value();
            if(e != this && e->label()->geometry().intersects(label)) {
                label.moveTo(label.x(), label.y() + 1 + e->label()->geometry().intersected(label).height());
                overlapped = true;
            }
            ++i;
        }
        // node overlapping
        Nodes::const_iterator j = graph->nodes_.constBegin();
        while (j != graph->nodes_.constEnd()) {
            GraphNode *n = j.value();
            if(n->geometry().intersects(label)) {
                label.moveTo(label.x(), label.y() + 1 + n->geometry().intersected(label).height());
                overlapped = true;
            }
            ++j;
        }

        if(!overlapped) break;
    };

    label_->setGeometry(label);
    labelRect_ = label;

    prepareGeometryChange();


    QGraphicsLayoutItem::updateGeometry();
}