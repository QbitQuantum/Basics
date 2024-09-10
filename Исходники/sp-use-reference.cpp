static void
sp_usepath_move_compensate(Geom::Affine const *mp, SPItem *original, SPUsePath *self)
{
    Inkscape::Preferences *prefs = Inkscape::Preferences::get();
    guint mode = prefs->getInt("/options/clonecompensation/value", SP_CLONE_COMPENSATION_PARALLEL);
    if (mode == SP_CLONE_COMPENSATION_NONE) {
        return;
    }
    SPItem *item = SP_ITEM(self->owner);

// TODO kill naughty naughty #if 0
#if 0
    Geom::Affine m(*mp);
    if (!(m.is_translation())) {
        return;
    }
    Geom::Affine const t(item->transform);
    Geom::Affine clone_move = t.inverse() * m * t;

    // Calculate the compensation matrix and the advertized movement matrix.
    Geom::Affine advertized_move;
    if (mode == SP_CLONE_COMPENSATION_PARALLEL) {
        //clone_move = clone_move.inverse();
        advertized_move.set_identity();
    } else if (mode == SP_CLONE_COMPENSATION_UNMOVED) {
        clone_move = clone_move.inverse() * m;
        advertized_move = m;
    } else {
        g_assert_not_reached();
    }

    // Commit the compensation.
    item->transform *= clone_move;
    sp_item_write_transform(item, item->getRepr(), item->transform, &advertized_move);
#else
    (void)mp;
    (void)original;
#endif

    self->sourceDirty = true;
    item->requestDisplayUpdate(SP_OBJECT_MODIFIED_FLAG);
}