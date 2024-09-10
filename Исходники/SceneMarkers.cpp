BoundingBoxMarker::BoundingBoxMarker(const BoundingBox& bbox, const Vector3f& color, float transparency)
{
    double h = bbox.max().x() - bbox.min().x();
    double w = bbox.max().y() - bbox.min().y();
    double d = bbox.max().z() - bbox.min().z();
    double width = (h + w + d) / 3.0 / 10.0;
    create(bbox, color, transparency, width);
}