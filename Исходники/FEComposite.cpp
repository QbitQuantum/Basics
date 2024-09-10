FloatRect FEComposite::determineAbsolutePaintRect(const FloatRect& originalRequestedRect)
{
    FloatRect requestedRect = originalRequestedRect;
    if (clipsToBounds())
        requestedRect.intersect(maxEffectRect());

    // We may be called multiple times if result is used more than once. Return
    // quickly if nothing new is required.
    if (absolutePaintRect().contains(enclosingIntRect(requestedRect)))
        return requestedRect;

    // No mapPaintRect required for FEComposite.
    FloatRect input1Rect = inputEffect(1)->determineAbsolutePaintRect(requestedRect);
    FloatRect affectedRect;
    switch (m_type) {
    case FECOMPOSITE_OPERATOR_IN:
        // 'in' has output only in the intersection of both inputs.
        affectedRect = intersection(input1Rect, inputEffect(0)->determineAbsolutePaintRect(input1Rect));
        break;
    case FECOMPOSITE_OPERATOR_ATOP:
        // 'atop' has output only in the extents of the second input.
        // Make sure first input knows where it needs to produce output.
        inputEffect(0)->determineAbsolutePaintRect(input1Rect);
        affectedRect = input1Rect;
        break;
    case FECOMPOSITE_OPERATOR_ARITHMETIC:
        if (k4() > 0) {
            // Make sure first input knows where it needs to produce output.
            inputEffect(0)->determineAbsolutePaintRect(requestedRect);
            // Arithmetic with non-zero k4 may influnce the complete filter primitive
            // region. So we can't optimize the paint region here.
            affectedRect = requestedRect;
            break;
        }
        if (k2() <= 0) {
            // Input 0 does not appear where input 1 is not present.
            FloatRect input0Rect = inputEffect(0)->determineAbsolutePaintRect(input1Rect);
            if (k3() > 0) {
                affectedRect = input1Rect;
            } else {
                // Just k1 is positive. Use intersection.
                affectedRect = intersection(input1Rect, input0Rect);
            }
            break;
        }
        // else fall through to use union
    default:
        // Take the union of both input effects.
        affectedRect = unionRect(input1Rect, inputEffect(0)->determineAbsolutePaintRect(requestedRect));
        break;
    }

    affectedRect.intersect(requestedRect);
    addAbsolutePaintRect(affectedRect);
    return affectedRect;
}