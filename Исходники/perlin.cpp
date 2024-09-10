static real64 PerlinNoise3DFunction(real64 x, real64 y, real64 z) 
{
	// Compute noise cell coordinates and offsets
	int32_t ix = Floor2Int(x);
	int32_t iy = Floor2Int(y);
	int32_t iz = Floor2Int(z);
	real64 dx = x - ix, dy = y - iy, dz = z - iz;
	// Compute gradient weights
	ix &= (NOISE_PERM_SIZE-1);
	iy &= (NOISE_PERM_SIZE-1);
	iz &= (NOISE_PERM_SIZE-1);
	real64 w000 = Grad3d(ix,   iy,   iz,   dx,   dy,   dz);
	real64 w100 = Grad3d(ix+1, iy,   iz,   dx-1, dy,   dz);
	real64 w010 = Grad3d(ix,   iy+1, iz,   dx,   dy-1, dz);
	real64 w110 = Grad3d(ix+1, iy+1, iz,   dx-1, dy-1, dz);
	real64 w001 = Grad3d(ix,   iy,   iz+1, dx,   dy,   dz-1);
	real64 w101 = Grad3d(ix+1, iy,   iz+1, dx-1, dy,   dz-1);
	real64 w011 = Grad3d(ix,   iy+1, iz+1, dx,   dy-1, dz-1);
	real64 w111 = Grad3d(ix+1, iy+1, iz+1, dx-1, dy-1, dz-1);
	// Compute trilinear interpolation of weights
	real64 wx = PerlinFade(dx);
	real64 wy = PerlinFade(dy);
	real64 wz = PerlinFade(dz);
	real64 x00 = Lerp(wx, w000, w100);
	real64 x10 = Lerp(wx, w010, w110);
	real64 x01 = Lerp(wx, w001, w101);
	real64 x11 = Lerp(wx, w011, w111);
	real64 y0 = Lerp(wy, x00, x10);
	real64 y1 = Lerp(wy, x01, x11);
	return Lerp(wz, y0, y1);
}