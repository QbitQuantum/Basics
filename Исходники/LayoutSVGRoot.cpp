bool LayoutSVGRoot::nodeAtPoint(HitTestResult& result, const HitTestLocation& locationInContainer, const LayoutPoint& accumulatedOffset, HitTestAction hitTestAction)
{
    LayoutPoint pointInParent = locationInContainer.point() - toLayoutSize(accumulatedOffset);
    LayoutPoint pointInBorderBox = pointInParent - toLayoutSize(location());

    // Only test SVG content if the point is in our content box, or in case we
    // don't clip to the viewport, the visual overflow rect.
    // FIXME: This should be an intersection when rect-based hit tests are supported by nodeAtFloatPoint.
    if (contentBoxRect().contains(pointInBorderBox) || (!shouldApplyViewportClip() && visualOverflowRect().contains(pointInBorderBox))) {
        const AffineTransform& localToParentTransform = this->localToParentTransform();
        if (localToParentTransform.isInvertible()) {
            FloatPoint localPoint = localToParentTransform.inverse().mapPoint(FloatPoint(pointInParent));

            for (LayoutObject* child = lastChild(); child; child = child->previousSibling()) {
                // FIXME: nodeAtFloatPoint() doesn't handle rect-based hit tests yet.
                if (child->nodeAtFloatPoint(result, localPoint, hitTestAction)) {
                    updateHitTestResult(result, pointInBorderBox);
                    if (result.addNodeToListBasedTestResult(child->node(), locationInContainer) == StopHitTesting)
                        return true;
                }
            }
        }
    }

    // If we didn't early exit above, we've just hit the container <svg> element. Unlike SVG 1.1, 2nd Edition allows container elements to be hit.
    if ((hitTestAction == HitTestBlockBackground || hitTestAction == HitTestChildBlockBackground) && visibleToHitTestRequest(result.hitTestRequest())) {
        // Only return true here, if the last hit testing phase 'BlockBackground' (or 'ChildBlockBackground' - depending on context) is executed.
        // If we'd return true in the 'Foreground' phase, hit testing would stop immediately. For SVG only trees this doesn't matter.
        // Though when we have a <foreignObject> subtree we need to be able to detect hits on the background of a <div> element.
        // If we'd return true here in the 'Foreground' phase, we are not able to detect these hits anymore.
        LayoutRect boundsRect(accumulatedOffset + location(), size());
        if (locationInContainer.intersects(boundsRect)) {
            updateHitTestResult(result, pointInBorderBox);
            if (result.addNodeToListBasedTestResult(node(), locationInContainer, boundsRect) == StopHitTesting)
                return true;
        }
    }

    return false;
}