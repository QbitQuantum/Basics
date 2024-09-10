void Tartet::Sizer(void)
{
	dx = manager->CashedDx();
//
// Current version of TARTET is restricted to cubic lattices
	real s = shpar[0];
//
// Set XOFF (and IMIN,IMAX):
	minJx = -(int)(s * Sqrt(onex_ / (real)24.));
	xoff = half_ - s * Sqrt(onex_ / (real)24.) - minJx;
	maxJx = minJx + (int)(s * Sqrt(twox_ / (real)3.) + half_) - 1;
//
// Set YOFF (and JMIN,JMAX):
	minJy = -(int)(s / Sqrt(12.));
	yoff = half_ - s / Sqrt(12.) - minJy;
	maxJy = minJy + (int)(s * Sqrt(0.75) + half_) - 1;
//
// Set ZOFF (and KMIN,KMAX): Determine whether S is closest to even or odd int. (Temporarily let KMIN be int which S is closest to)
	minJz = (int)(s + half_);
//
// If KMIN is even, then ZOFF=0.5
// If KMIN is odd, then ZOFF=0.
	zoff = zero_;
	if (minJz % 2 == 0) 
		zoff = half_;
	minJz = -(int)(half_ * s + zoff);
	maxJz = minJz + (int)(s + half_) - 1;
	AllocateArrays(maxJx - minJx + 1, maxJy - minJy + 1, maxJz - minJz + 1);
}