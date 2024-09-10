void Node::AddChild(Node& child)
{
	child.DetachNode();
	m_members.push_back(&child);
	child.SetParent(this);
	child.SetRoot(GetRoot());
}