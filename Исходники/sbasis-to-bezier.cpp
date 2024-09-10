/** Make a path from a d2 sbasis.
 \param p the d2 Symmetric basis polynomial
 \returns a Path

  If only_cubicbeziers is true, the resulting path may only contain CubicBezier curves.
*/
void build_from_sbasis(Geom::PathBuilder &pb, D2<SBasis> const &B, double tol, bool only_cubicbeziers) {
    if (!B.isFinite()) {
        THROW_EXCEPTION("assertion failed: B.isFinite()");
    }
    if(tail_error(B, 2) < tol || sbasis_size(B) == 2) { // nearly cubic enough
        if( !only_cubicbeziers && (sbasis_size(B) <= 1) ) {
            pb.lineTo(B.at1());
        } else {
            std::vector<Geom::Point> bez;
            sbasis_to_bezier(bez, B, 4);
            pb.curveTo(bez[1], bez[2], bez[3]);
        }
    } else {
        build_from_sbasis(pb, compose(B, Linear(0, 0.5)), tol, only_cubicbeziers);
        build_from_sbasis(pb, compose(B, Linear(0.5, 1)), tol, only_cubicbeziers);
    }
}