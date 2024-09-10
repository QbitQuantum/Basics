/**
   Transforms this lifting surface.
   
   @param[in]   transformation   Affine transformation.
*/
void
LiftingSurface::transform(const Eigen::Transform<double, 3, Eigen::Affine> &transformation)
{
    // Call super:
    this->Surface::transform(transformation);
    
    // Transform bisectors and wake normals:
    for (int i = 0; i < n_spanwise_nodes(); i++) {
        Vector3d trailing_edge_bisector = trailing_edge_bisectors.row(i);
        trailing_edge_bisectors.row(i) = transformation.linear() * trailing_edge_bisector;
        
        Vector3d wake_normal = wake_normals.row(i);
        wake_normals.row(i) = transformation.linear() * wake_normal;
    }
}