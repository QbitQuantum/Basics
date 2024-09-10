bool LayoutPart::setWidgetGeometry(const LayoutRect& frame)
{
    if (!node())
        return false;

    Widget* widget = this->widget();
    ASSERT(widget);

    IntRect newFrame = roundedIntRect(frame);

    if (widget->frameRect() == newFrame)
        return false;

    RefPtr<LayoutPart> protector(this);
    RawPtr<Node> protectedNode(node());
    widget->setFrameRect(newFrame);
    return widget->frameRect().size() != newFrame.size();
}