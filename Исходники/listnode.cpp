sListNode::~sListNode()
{
	if (head==this) FlushAll();
}