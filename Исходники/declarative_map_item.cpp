QSGNode *
QcMapItem::updatePaintNode(QSGNode * old_node, UpdatePaintNodeData *)
{
  // qInfo() << old_node;

  // if (!m_map) {
  //   delete old_node;
  //   return nullptr;
  // }

  QSGSimpleRectNode * root = static_cast<QSGSimpleRectNode *>(old_node);
  if (!root)
    root = new QSGSimpleRectNode(boundingRect(), m_color);
  else {
    root->setRect(boundingRect());
    root->setColor(m_color);
  }

  QSGNode * content = root->childCount() ? root->firstChild() : 0;
  content = m_map_view->update_scene_graph(content, window());
  if (content and root->childCount() == 0)
    root->appendChildNode(content);

  return root;
}