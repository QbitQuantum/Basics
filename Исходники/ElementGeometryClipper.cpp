void ElementGeometryClipper::clipAndCall(const Element& element, const QuadKey& quadKey, const BoundingBox& quadKeyBbox)
{
    quadKey_ = quadKey;
    quadKeyBbox_ = quadKeyBbox;
    element.accept(*this);
}