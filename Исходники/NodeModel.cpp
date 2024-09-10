void touchmind::model::node::NodeModel::AddChild(const std::shared_ptr<touchmind::model::node::NodeModel> &node) {
  if (std::find(m_children.begin(), m_children.end(), node) != m_children.end()) {
    return;
  }
  m_children.push_back(node);
  node->SetParent(shared_from_this());
  IncrementRepaintRequiredCounter();
  IncrementSaveRequiredCounter();
}