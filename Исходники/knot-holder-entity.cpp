Geom::Point
KnotHolderEntity::snap_knot_position_constrained(Geom::Point const &p, Inkscape::Snapper::SnapConstraint const &constraint, guint state)
{
    if (state & GDK_SHIFT_MASK) { // Don't snap when shift-key is held
        return p;
    }

    Geom::Affine const i2d (item->i2dt_affine());
    Geom::Point s = p * i2d;

    SnapManager &m = desktop->namedview->snap_manager;
    m.setup(desktop, true, item);

    // constrainedSnap() will first project the point p onto the constraint line and then try to snap along that line.
    // This way the constraint is already enforced, no need to worry about that later on
    Inkscape::Snapper::SnapConstraint transformed_constraint = Inkscape::Snapper::SnapConstraint(constraint.getPoint() * i2d, (constraint.getPoint() + constraint.getDirection()) * i2d - constraint.getPoint() * i2d);
    m.constrainedSnapReturnByRef(s, Inkscape::SNAPSOURCE_NODE_HANDLE, transformed_constraint);
    m.unSetup();

    return s * i2d.inverse();
}