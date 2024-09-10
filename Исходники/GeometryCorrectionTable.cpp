void GeometryCorrectionTable::apply_z_correction(
        const Vector3F& edge_dir, MatrixFr& loop) {
    //const Float max_z_error = 0.125;
    //const Float max_z_error = 0.09;
    const Float max_z_error = 0.00;
    VectorF bbox_min = loop.colwise().minCoeff();
    VectorF bbox_max = loop.colwise().maxCoeff();
    VectorF bbox_center = 0.5 * (bbox_min + bbox_max);

    Vector3F side_dir = edge_dir.cross(Vector3F::UnitZ());
    Float sin_val = side_dir.norm();
    if (sin_val < 1e-3) return;

    const size_t num_vts = loop.rows();
    for (size_t i=0; i<num_vts; i++) {
        Vector3F v = loop.row(i) - bbox_center.transpose();
        Float side_component = side_dir.dot(v) / sin_val;
        Vector3F proj_v = v - side_component * side_dir / sin_val;
        Float proj_component = proj_v.norm();
        if (proj_component > 1e-3) {
            proj_v -= proj_v / proj_component * (sin_val * max_z_error);
        }
        loop.row(i) = bbox_center + proj_v + side_component * side_dir / sin_val;
    }
}