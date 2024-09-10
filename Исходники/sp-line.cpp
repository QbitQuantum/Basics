void SPLine::set_shape() {
    SPCurve *c = new SPCurve();

    c->moveto(this->x1.computed, this->y1.computed);
    c->lineto(this->x2.computed, this->y2.computed);

    this->setCurveInsync(c, TRUE); // *_insync does not call update, avoiding infinite recursion when set_shape is called by update
    this->setCurveBeforeLPE(c);

    // LPE's cannot be applied to lines. (the result can (generally) not be represented as SPLine)

    c->unref();
}