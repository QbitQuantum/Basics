/*
 * rectfi
 *
 * draw a filled rectangle given two opposite corners (expressed as integers)
 */
void
rectfi(Icoord x1, Icoord y1, Icoord x2, Icoord y2)
{
	rectf((Coord)x1, (Coord)y1, (Coord)x2, (Coord)y2);
}