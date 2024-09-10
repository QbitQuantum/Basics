static void sp_offset_move_compensate(Geom::Affine const *mp, SPItem */*original*/, SPOffset *self)
{
    Inkscape::Preferences *prefs = Inkscape::Preferences::get();
    guint mode = prefs->getInt("/options/clonecompensation/value", SP_CLONE_COMPENSATION_PARALLEL);

    Geom::Affine m(*mp);

    if (!(m.isTranslation()) || mode == SP_CLONE_COMPENSATION_NONE) {
        self->sourceDirty=true;
        self->requestDisplayUpdate(SP_OBJECT_MODIFIED_FLAG);
        return;
    }

    // calculate the compensation matrix and the advertized movement matrix
    self->readAttr("transform");

    Geom::Affine t = self->transform;
    Geom::Affine offset_move = t.inverse() * m * t;

    Geom::Affine advertized_move;
    if (mode == SP_CLONE_COMPENSATION_PARALLEL) {
        offset_move = offset_move.inverse() * m;
        advertized_move = m;
    } else if (mode == SP_CLONE_COMPENSATION_UNMOVED) {
        offset_move = offset_move.inverse();
        advertized_move.setIdentity();
    } else {
        g_assert_not_reached();
    }

    self->sourceDirty=true;

    // commit the compensation
    self->transform *= offset_move;
    self->doWriteTransform(self->getRepr(), self->transform, &advertized_move);
    self->requestDisplayUpdate(SP_OBJECT_MODIFIED_FLAG);
}