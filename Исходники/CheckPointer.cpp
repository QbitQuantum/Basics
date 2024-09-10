void CheckPointer::checkPointDir(const shared_ptr<DirINode> &dirINode)
{
	/* checkpoint the information of the dir */
	fprintf(fout_, "%d %s %ld %ld %ld %d %d %d %d\n", 0, dirINode->key().c_str(),
				dirINode->atime(), dirINode->mtime(), dirINode->ctime(),
				dirINode->size(), dirINode->auth(), dirINode->uid(), dirINode->gid());
	/* push the subdir and subfile to the queue */
	list<INodePtr> children = dirINode->children();
	for (list<INodePtr>::iterator lit = children.begin(); lit != children.end(); lit++) {
		QueueEntity queueEntity;
		queueEntity.node_ = *lit;
		queueEntity.parentDir_ = dirINode->key();
		checkPointQueue_.push(queueEntity);
	}
}