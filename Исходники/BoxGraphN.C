// Set the box.
void BoxGraphNode::setBox(Box *b)
{
    assert(b == 0 || b->OK());

    setHighlight(0);

    Box *old = _box;
    if (b)
	_box = b->link();
    else
	_box = 0;

    if (old)
	old->unlink();

    if (b)
	resize(b->size());
}