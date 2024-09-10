/**
* \brief Add a child drawable to this drawable
* \param child The child to add
*/
void CPartDrawable::AddChild(std::shared_ptr<CPartDrawable> child)
{
	this->mChildren.push_back(child);
	child->SetParent(this);
	child->SetTree(this->GetTree());
}