std::shared_ptr<Spatial> Node::SetChild(int i,
    std::shared_ptr<Spatial> const& child)
{
    if (child)
    {
        LogAssert(!child->GetParent(), "The child already has a parent.");
    }

    int const numChildren = static_cast<int>(mChild.size());
    if (0 <= i && i < numChildren)
    {
        // Remove the child currently in the slot.
        std::shared_ptr<Spatial> previousChild = mChild[i];
        if (previousChild)
        {
            previousChild->SetParent(nullptr);
        }

        // Insert the new child in the slot.
        if (child)
        {
            child->SetParent(this);
        }

        mChild[i] = child;
        return previousChild;
    }

    // The index is out of range, so append the child to the array.
    if (child)
    {
        child->SetParent(this);
    }
    mChild.push_back(child);
    return nullptr;
}