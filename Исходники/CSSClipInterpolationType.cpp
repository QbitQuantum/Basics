static PassOwnPtr<InterpolableValue> convertClipComponent(const Length& length, double zoom)
{
    if (length.isAuto())
        return InterpolableList::create(0);
    return CSSLengthInterpolationType::maybeConvertLength(length, zoom).interpolableValue.release();
}