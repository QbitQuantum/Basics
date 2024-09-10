/*!
 * \internal
 */
QSGNode *QDeclarativeGeoMap::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    if (!map_) {
        delete oldNode;
        return 0;
    }

    QSGSimpleRectNode *root = static_cast<QSGSimpleRectNode *>(oldNode);
    if (!root)
        root = new QSGSimpleRectNode(boundingRect(), QColor::fromRgbF(0.9, 0.9, 0.9));
    else
        root->setRect(boundingRect());

    QSGNode *content = root->childCount() ? root->firstChild() : 0;
    content = map_->updateSceneGraph(content, window());
    if (content && root->childCount() == 0)
        root->appendChildNode(content);

    return root;
}