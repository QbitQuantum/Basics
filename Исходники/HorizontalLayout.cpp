void HorizontalLayout::AddChild(const std::shared_ptr<UIElement>& element)
{
    POMDOG_ASSERT(!element->GetParent());

    children.push_back(element);

    element->MarkParentDrawOrderDirty();
    element->MarkParentTransformDirty();

    POMDOG_ASSERT(shared_from_this());
    element->SetParent(shared_from_this());
    element->OnEnter();

    needToUpdateLayout = true;
}