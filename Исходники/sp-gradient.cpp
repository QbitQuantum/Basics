void
sp_gradient_set_gs2d_matrix(SPGradient *gr, Geom::Affine const &ctm,
                            Geom::Rect const &bbox, Geom::Affine const &gs2d)
{
    gr->gradientTransform = gs2d * ctm.inverse();
    if (gr->getUnits() == SP_GRADIENT_UNITS_OBJECTBOUNDINGBOX ) {
        gr->gradientTransform = ( gr->gradientTransform
                                  * Geom::Translate(-bbox.min())
                                  * Geom::Scale(bbox.dimensions()).inverse() );
    }
    gr->gradientTransform_set = TRUE;

    gr->requestModified(SP_OBJECT_MODIFIED_FLAG);
}