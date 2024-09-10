TreeIterator::TreeIterator(BPlusTree* tree, struct btrfs_key &key)
	:
	fTree(tree),
	fCurrentKey(key)
{
	Rewind();
	tree->_AddIterator(this);
}