//----------------------------------------------------------------------------
bool SizeNode::IsIntersectSizeRange(const SizeNode *node) const
{
	Rectf worldRect = GetWorldRect();
	Rectf nodeWorldRect = node->GetWorldRect();

	return  worldRect.IsIntersect(nodeWorldRect);
}