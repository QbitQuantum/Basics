/**
* Add a child drawable to this drawable
* \param child The child to add
*/
void CDrawable::AddChild(std::shared_ptr<CDrawable> child)
{
	mChildren.push_back(child); //aded
	child->SetParent(this);

}