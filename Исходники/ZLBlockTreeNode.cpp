void ZLBlockTreeNode::addHyperlink(std::size_t left, std::size_t top, std::size_t right, std::size_t bottom, shared_ptr<ZLRunnableWithKey> action) {
	myHyperlinks[Rectangle(left, top, right, bottom)] = action;
}