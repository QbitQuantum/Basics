CCAffineTransform CCNode::nodeToWorldTransform()
{
	CCAffineTransform t = this->nodeToParentTransform();

	for (CCNode *p = m_pParent; p != NULL; p = p->getParent())
		t = CCAffineTransformConcat(t, p->nodeToParentTransform());

	return t;
}