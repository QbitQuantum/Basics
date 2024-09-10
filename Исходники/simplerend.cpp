bool
SimpleRenderer::get_inverse_matrix (Matrix44 &result, ustring to, float time)
{
    if (to == u_camera || to == u_screen || to == u_NDC || to == u_raster) {
        Matrix44 M = m_world_to_camera;
        if (to == u_screen || to == u_NDC || to == u_raster) {
            // arbitrary clip planes because renderer doesn't do any clipping
            float yon = 0.01f;
            float hither = 1e5f;
            float depthrange = yon - hither;
            float tanhalffov = tanf (m_fov * float(M_PI/360.0));
            Matrix44 camera_to_screen (1/tanhalffov, 0, 0, 0,
                                       0, 1/tanhalffov, 0, 0,
                                       0, 0, yon/depthrange, 1,
                                       0, 0, -yon*hither/depthrange, 0);
            M = M * camera_to_screen;
            if (to == u_NDC || to == u_raster) {
                Matrix44 screen_to_ndc (0.5f, 0, 0, 0,
                                        0, 0.5f, 0, 0,
                                        0, 0, 1.0f, 0,
                                        -0.5f, -0.5f, 0, 1);
                M = M * screen_to_ndc;
                if (to == u_raster) {
                    Matrix44 ndc_to_raster (m_xres, 0, 0, 0,
                                            0, m_yres, 0, 0,
                                            0, 0, 1, 0,
                                            0, 0, 0, 1);
                    M = M * ndc_to_raster;
                }
            }
        }
        result = M;
        return true;
    }

    TransformMap::const_iterator found = m_named_xforms.find (to);
    if (found == m_named_xforms.end())
        return false;
    result = found->second;
    result.invert();
    return true;
}