nsresult
BoxObject::GetOffsetRect(nsIntRect& aRect)
{
    aRect.SetRect(0, 0, 0, 0);

    if (!mContent)
        return NS_ERROR_NOT_INITIALIZED;

    // Get the Frame for our content
    nsIFrame* frame = GetFrame(true);
    if (frame) {
        // Get its origin
        nsPoint origin = frame->GetPositionIgnoringScrolling();

        // Find the frame parent whose content is the document element.
        Element* docElement = mContent->GetComposedDoc()->GetRootElement();
        nsIFrame* parent = frame->GetParent();
        for (;;) {
            // If we've hit the document element, break here
            if (parent->GetContent() == docElement) {
                break;
            }

            nsIFrame* next = parent->GetParent();
            if (!next) {
                NS_WARNING("We should have hit the document element...");
                origin += parent->GetPosition();
                break;
            }

            // Add the parent's origin to our own to get to the
            // right coordinate system
            origin += next->GetPositionOfChildIgnoringScrolling(parent);
            parent = next;
        }

        // For the origin, add in the border for the frame
        const nsStyleBorder* border = frame->StyleBorder();
        origin.x += border->GetComputedBorderWidth(NS_SIDE_LEFT);
        origin.y += border->GetComputedBorderWidth(NS_SIDE_TOP);

        // And subtract out the border for the parent
        const nsStyleBorder* parentBorder = parent->StyleBorder();
        origin.x -= parentBorder->GetComputedBorderWidth(NS_SIDE_LEFT);
        origin.y -= parentBorder->GetComputedBorderWidth(NS_SIDE_TOP);

        aRect.x = nsPresContext::AppUnitsToIntCSSPixels(origin.x);
        aRect.y = nsPresContext::AppUnitsToIntCSSPixels(origin.y);

        // Get the union of all rectangles in this and continuation frames.
        // It doesn't really matter what we use as aRelativeTo here, since
        // we only care about the size. Using 'parent' might make things
        // a bit faster by speeding up the internal GetOffsetTo operations.
        nsRect rcFrame = nsLayoutUtils::GetAllInFlowRectsUnion(frame, parent);
        aRect.width = nsPresContext::AppUnitsToIntCSSPixels(rcFrame.width);
        aRect.height = nsPresContext::AppUnitsToIntCSSPixels(rcFrame.height);
    }

    return NS_OK;
}