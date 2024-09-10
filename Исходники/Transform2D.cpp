void Transform2D::AddChild(std::shared_ptr<Transform2DIF> child)
{
	for (auto& c : Children)
	{
		if (c == child)
			return;
	}
	Children.push_back(child);
	child->SetParent(shared_from_this());
}