 PathCleanupIterator(PyObject* path, agg::trans_affine trans,
                     bool remove_nans, bool do_clip,
                     const agg::rect_base<double>& rect,
                     e_snap_mode snap_mode, double stroke_width,
                     bool do_simplify) :
     m_path_obj(path, true),
     m_path_iter(m_path_obj),
     m_transform(trans),
     m_transformed(m_path_iter, m_transform),
     m_nan_removed(m_transformed, remove_nans, m_path_iter.has_curves()),
     m_clipped(m_nan_removed, do_clip, rect),
     m_snapped(m_clipped, snap_mode, m_path_iter.total_vertices(),
               stroke_width),
     m_simplify(m_snapped, do_simplify && m_path_iter.should_simplify(),
                m_path_iter.simplify_threshold())
 {
     Py_INCREF(path);
     m_path_iter.rewind(0);
 }