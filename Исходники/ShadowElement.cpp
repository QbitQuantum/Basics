void ShadowBlockElement::layoutAsPart(const IntRect& partRect)
{
    RenderBox* parentRenderer = toRenderBox(renderer()->parent());
    RenderBox* selfRenderer = toRenderBox(renderer());
    IntRect oldRect = selfRenderer->frameRect();

    LayoutStateMaintainer statePusher(parentRenderer->view(), parentRenderer, parentRenderer->size(), parentRenderer->style()->isFlippedBlocksWritingMode());

    if (oldRect.size() != partRect.size())
        selfRenderer->setChildNeedsLayout(true, false);

    selfRenderer->layoutIfNeeded();
    selfRenderer->setFrameRect(partRect);

    if (selfRenderer->checkForRepaintDuringLayout())
        selfRenderer->repaintDuringLayoutIfMoved(oldRect);
        
    statePusher.pop();
    parentRenderer->addOverflowFromChild(selfRenderer);
}