bool CacheTreeCollector::visit(LayerCache::CacheTree::Node* node, int32_t d) {
    if(!m_viewport.intersects(Rect(node->x(), node->y(),node->size(),node->size()))) {
        return false;
    }
    std::set<int32_t>& list = node->data();
    for(std::set<int32_t>::iterator i = list.begin(); i!=list.end(); ++i) {
        m_indices.push_back(*i);
    }
    return true;
}