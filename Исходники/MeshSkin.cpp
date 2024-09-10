void MeshSkin::setRootJoint(Joint* joint)
{
    if (_rootJoint)
    {
        if (_rootJoint->getParent())
        {
            _rootJoint->getParent()->removeListener(this);
        }
    }

    _rootJoint = joint;

    // If the root joint has a parent node, register for its transformChanged event
    if (_rootJoint && _rootJoint->getParent())
    {
        _rootJoint->getParent()->addListener(this, 1);
    }

    Node* newRootNode = _rootJoint;
    if (newRootNode)
    {
        // Find the top level parent node of the root joint
        for (Node* node = newRootNode->getParent(); node != NULL; node = node->getParent())
        {
            if (node->getParent() == NULL)
            {
                newRootNode = node;
                break;
            }
        }
    }
    setRootNode(newRootNode);
}