void GraphicsContextPlatformPrivate::concatCTM(const TransformationMatrix& transform)
{
    cairo_surface_t* surface = cairo_get_target(cr);
    HDC hdc = cairo_win32_surface_get_dc(surface);   
    SaveDC(hdc);

    const cairo_matrix_t* matrix = reinterpret_cast<const cairo_matrix_t*>(&transform);

    XFORM xform;
    xform.eM11 = matrix->xx;
    xform.eM12 = matrix->xy;
    xform.eM21 = matrix->yx;
    xform.eM22 = matrix->yy;
    xform.eDx = matrix->x0;
    xform.eDy = matrix->y0;

    ModifyWorldTransform(hdc, &xform, MWT_LEFTMULTIPLY);
}