FloatRect FEBoxReflect::mapRect(const FloatRect& rect, bool forward)
{
    SkMatrix flipMatrix = SkiaImageFilterBuilder().matrixForBoxReflectFilter(
        m_reflectionDirection, m_offset);
    if (!forward) {
        bool inverted = flipMatrix.invert(&flipMatrix);
        DCHECK(inverted) << "box reflect matrix must be invertible";
    }

    SkRect reflection(rect);
    flipMatrix.mapRect(&reflection);

    FloatRect result = rect;
    result.unite(reflection);
    return result;
}