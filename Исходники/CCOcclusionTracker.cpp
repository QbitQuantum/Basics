static inline IntRect computeUnoccludedContentRect(const IntRect& contentRect, const TransformationMatrix& contentSpaceTransform, const IntRect& scissorRect, const Region& occlusion)
{
    if (!contentSpaceTransform.isInvertible())
        return contentRect;

    // Take the enclosingIntRect at each step, as we want to contain any unoccluded partial pixels in the resulting IntRect.
    FloatRect transformedRect = CCMathUtil::mapClippedRect(contentSpaceTransform, FloatRect(contentRect));
    IntRect shrunkRect = rectSubtractRegion(intersection(enclosingIntRect(transformedRect), scissorRect), occlusion);
    IntRect unoccludedRect = enclosingIntRect(CCMathUtil::projectClippedRect(contentSpaceTransform.inverse(), FloatRect(shrunkRect)));
    // The rect back in content space is a bounding box and may extend outside of the original contentRect, so clamp it to the contentRectBounds.
    return intersection(unoccludedRect, contentRect);
}