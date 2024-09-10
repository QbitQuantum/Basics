void ScrollingTree::updateTreeFromStateNode(ScrollingStateNode* stateNode)
{
    // This fuction recurses through the ScrollingStateTree and updates the corresponding ScrollingTreeNodes.
    // Find the ScrollingTreeNode associated with the current stateNode using the shared ID and our HashMap.
    ScrollingTreeNodeMap::const_iterator it = m_nodeMap.find(stateNode->scrollingNodeID());

    if (it != m_nodeMap.end()) {
        ScrollingTreeNode* node = it->value;
        node->update(stateNode);
    } else {
        // If the node isn't found, it's either new and needs to be added to the tree, or there is a new ID for our
        // root node.
        if (!stateNode->parent()) {
            // This is the root node.
            m_rootNode->setScrollingNodeID(stateNode->scrollingNodeID());
            m_nodeMap.set(stateNode->scrollingNodeID(), m_rootNode.get());
            m_rootNode->update(stateNode);
        } else {
            // FIXME: In the future, we will have more than just ScrollingTreeScrollingNode, so we'll have to
            // figure out which type of node to create.
            OwnPtr<ScrollingTreeNode> newNode = ScrollingTreeScrollingNode::create(this);
            ScrollingTreeNode* newNodeRawPtr = newNode.get();
            m_nodeMap.set(stateNode->scrollingNodeID(), newNodeRawPtr);
            ScrollingTreeNodeMap::const_iterator it = m_nodeMap.find(stateNode->parent()->scrollingNodeID());
            ASSERT(it != m_nodeMap.end());
            if (it != m_nodeMap.end()) {
                ScrollingTreeNode* parent = it->value;
                newNode->setParent(parent);
                parent->appendChild(newNode.release());
            }
            newNodeRawPtr->update(stateNode);
        }
    }

    // Now update the children if we have any.
    Vector<OwnPtr<ScrollingStateNode> >* stateNodeChildren = stateNode->children();
    if (!stateNodeChildren)
        return;

    size_t size = stateNodeChildren->size();
    for (size_t i = 0; i < size; ++i)
        updateTreeFromStateNode(stateNodeChildren->at(i).get());
}