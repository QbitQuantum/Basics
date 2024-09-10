//----------------------------------------------------------------------------
bool Node::DetachChildByName (const std::string &name)
{
	for (int i=0; i<(int)mChild.size(); i++)
	{
		MovablePtr child = mChild[i];

		if (child != 0 && child->GetName() == name)
		{
			child->SetParent(0);
			OnChildRemoved(child);
			mChild[i] = 0;

			mIsNeedCalUpdateChild = true;

			return true;
		}

	}

	return false;
}