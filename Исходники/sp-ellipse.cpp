// Create path for rendering shape on screen
void SPGenericEllipse::set_shape()
{
    // std::cout << "SPGenericEllipse::set_shape: Entrance" << std::endl;
    if (hasBrokenPathEffect()) {
        g_warning("The ellipse shape has unknown LPE on it! Convert to path to make it editable preserving the appearance; editing it as ellipse will remove the bad LPE");

        if (this->getRepr()->attribute("d")) {
            // unconditionally read the curve from d, if any, to preserve appearance
            Geom::PathVector pv = sp_svg_read_pathv(this->getRepr()->attribute("d"));
            SPCurve *cold = new SPCurve(pv);
            this->setCurveInsync(cold, TRUE);
            cold->unref();
        }

        return;
    }
    if (Geom::are_near(this->rx.computed, 0) || Geom::are_near(this->ry.computed, 0)) {
        return;
    }

    this->normalize();

    SPCurve *curve = NULL;

    // For simplicity, we use a circle with center (0, 0) and radius 1 for our calculations.
    Geom::Circle circle(0, 0, 1);

    if (!this->_isSlice()) {
        start = 0.0;
        end = 2.0*M_PI;
    }
    double incr = end - start; // arc angle
    if (incr < 0.0) incr += 2.0*M_PI;    

    int numsegs = 1 + int(incr*2.0/M_PI); // number of arc segments
    if (numsegs > 4) numsegs = 4;

    incr = incr/numsegs; // limit arc angle to less than 90 degrees
    Geom::Path path(Geom::Point::polar(start));
    Geom::EllipticalArc* arc;
    for (int seg = 0; seg < numsegs; seg++) {
        arc = circle.arc(Geom::Point::polar(start + seg*incr), Geom::Point::polar(start + (seg + 0.5)*incr), Geom::Point::polar(start + (seg + 1.0)*incr));
        path.append(*arc);
        delete arc;
    }
    Geom::PathBuilder pb;
    pb.append(path);
    if (this->_isSlice() && this->_closed) {
        pb.lineTo(Geom::Point(0, 0));
    }
    if (this->_closed) {
        pb.closePath();
    } else {
        pb.flush();
    }
    curve = new SPCurve(pb.peek());

    // gchar *str = sp_svg_write_path(curve->get_pathvector());
    // std::cout << "  path: " << str << std::endl;
    // g_free(str);

    // Stretching / moving the calculated shape to fit the actual dimensions.
    Geom::Affine aff = Geom::Scale(rx.computed, ry.computed) * Geom::Translate(cx.computed, cy.computed);
    curve->transform(aff);

    /* Reset the shape's curve to the "original_curve"
     * This is very important for LPEs to work properly! (the bbox might be recalculated depending on the curve in shape)*/
    this->setCurveInsync(curve, TRUE);
    this->setCurveBeforeLPE(curve);

    if (hasPathEffect() && pathEffectsEnabled()) {
        SPCurve *c_lpe = curve->copy();
        bool success = this->performPathEffect(c_lpe);

        if (success) {
            this->setCurveInsync(c_lpe, TRUE);
        }

        c_lpe->unref();
    }

    curve->unref();
    // std::cout << "SPGenericEllipse::set_shape: Exit" << std::endl;
}