QSGNode* PhysicsShape::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
    //TODO pametniji draw kruga, za sad je kocka
    QSGSimpleRectNode *n = static_cast<QSGSimpleRectNode *>(node);
    if (!n) {
        n = new QSGSimpleRectNode();
        n->setColor(Qt::green);
    }
    n->setRect(boundingRect());
    return n;
}