void TreeNode::removeChild(boost::shared_ptr<TreeNode> objectPtr,bool callback)
{
    if(isChild(objectPtr))
    {
        this->children.erase(std::find(this->children.begin(), this->children.end(), objectPtr));
        this->childrenNames.erase(std::find(this->childrenNames.begin(), this->childrenNames.end(), objectPtr->getName()));
	if(callback)
	  objectPtr->setParent();

    }
}