void Box3DSide::set_shape() {
    if (!this->document->getRoot()) {
        // avoid a warning caused by sp_document_height() (which is called from sp_item_i2d_affine() below)
        // when reading a file containing 3D boxes
        return;
    }

    SPObject *parent = this->parent;

    if (!SP_IS_BOX3D(parent)) {
        g_warning("Parent of 3D box side is not a 3D box.\n");
        return;
    }

    SPBox3D *box = SP_BOX3D(parent);

    Persp3D *persp = box3d_side_perspective(this);

    if (!persp) {
        return;
    }

    // TODO: Draw the correct quadrangle here
    //       To do this, determine the perspective of the box, the orientation of the side (e.g., XY-FRONT)
    //       compute the coordinates of the corners in P^3, project them onto the canvas, and draw the
    //       resulting path.

    unsigned int corners[4];
    box3d_side_compute_corner_ids(this, corners);

    SPCurve *c = new SPCurve();

    if (!box3d_get_corner_screen(box, corners[0]).isFinite() ||
        !box3d_get_corner_screen(box, corners[1]).isFinite() ||
        !box3d_get_corner_screen(box, corners[2]).isFinite() ||
        !box3d_get_corner_screen(box, corners[3]).isFinite() )
    {
        g_warning ("Trying to draw a 3D box side with invalid coordinates.\n");
        return;
    }

    c->moveto(box3d_get_corner_screen(box, corners[0]));
    c->lineto(box3d_get_corner_screen(box, corners[1]));
    c->lineto(box3d_get_corner_screen(box, corners[2]));
    c->lineto(box3d_get_corner_screen(box, corners[3]));
    c->closepath();

    /* Reset the this'scurve to the "original_curve"
     * This is very important for LPEs to work properly! (the bbox might be recalculated depending on the curve in shape)*/
    this->setCurveInsync( c, TRUE);

    if (hasPathEffect() && pathEffectsEnabled()) {
        SPCurve *c_lpe = c->copy();
        bool success = this->performPathEffect(c_lpe);

        if (success) {
            this->setCurveInsync(c_lpe, TRUE);
        }

        c_lpe->unref();
    }

    c->unref();
}