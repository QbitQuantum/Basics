HTTP2PriorityQueue::Handle
HTTP2PriorityQueue::updatePriority(HTTP2PriorityQueue::Handle handle,
                                   http2::PriorityUpdate pri) {
  Node* node = handle;
  pendingWeightChange_ = true;
  VLOG(4) << "Updating id=" << node->getID() << " with parent=" <<
    pri.streamDependency << " and weight=" << ((uint16_t)pri.weight + 1);
  node->updateWeight(pri.weight);
  CHECK_NE(pri.streamDependency, node->getID()) <<
    "Tried to create a loop in the tree";;
  if (pri.streamDependency == node->parentID() && !pri.exclusive) {
    // no move
    return handle;
  }

  Node* newParent = find(pri.streamDependency);
  if (!newParent) {
    newParent = &root_;
    VLOG(4) << "updatePriority missing parent, assigning root for txn="
            << node->getID();

  }

  if (newParent->isDescendantOf(node)) {
    newParent = newParent->reparent(node->getParent(), false);
  }
  return node->reparent(newParent, pri.exclusive);
}