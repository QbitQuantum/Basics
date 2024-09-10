/* snaps the keyframe to the nearest frame */
static short snap_bezier_nearest(KeyframeEditData *UNUSED(ked), BezTriple *bezt)
{
	if (bezt->f2 & SELECT)
		bezt->vec[1][0] = (float)(floorf(bezt->vec[1][0] + 0.5f));
	return 0;
}