//红黑树删除操作
void RBTree::TreeDelete(int key)
{
	Node* z = &TreeSearch(key);
	Node* y = z;
	Node* x;
	bool y_original_colour = y->getColour();

	if (z->getLeft() == NIL)
	{
		x = z->getRight();
		transplant(z, z->getRight());
	}
	else if (z->getRight() == NIL)
	{
		x = z->getLeft();
		transplant(z, z->getLeft());
	}
	else
	{
		y = &(TreeMinimum(z->getRight(), 0));
		y_original_colour = y->getColour();
		x = y->getRight();
		if (y->getParent() == z)
			x->setParent(y);
		else
		{
			transplant(y, y->getRight());
			y->setRight(z->getRight());
			y->getRight()->setParent(y);
		}
		transplant(z, y);
		y->setLeft(z->getLeft());
		y->getLeft()->setParent(y);
		y->setColour(z->getColour());
	}
	if (y_original_colour == BLACK)
		deleteFixup(x);
	delete z;
}