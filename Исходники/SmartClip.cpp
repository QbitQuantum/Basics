void SmartClip::collectOverlappingChildNodes(Node* parentNode, const IntRect& cropRect, WillBeHeapVector<RawPtrWillBeMember<Node> >& hitNodes)
{
    if (!parentNode)
        return;
    IntRect resizedCropRect = parentNode->document().view()->windowToContents(cropRect);
    for (Node* child = parentNode->firstChild(); child; child = child->nextSibling()) {
        IntRect childRect = child->pixelSnappedBoundingBox();
        if (resizedCropRect.intersects(childRect))
            hitNodes.append(child);
    }
}