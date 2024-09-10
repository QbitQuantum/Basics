/**
 * Exports a circle with the current attributes.
 * The default implementation calls exportArc with a full circle arc.
 */
void RExporter::exportCircle(const RCircle& circle) {
    RArc arc(circle.center, circle.radius, 0.0, 2*M_PI, false);
    exportArc(arc);
}