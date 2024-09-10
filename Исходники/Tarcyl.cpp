void Tarcyl::Allocator(void) // A=cylinder length/d, B=cylinder diameter/d
{
	int jlo, jhi;
	int curSize  = nx * ny;
	ixyz.Dimension(curSize, 3);
	real r2 = (real)0.25 * shpar[1] * shpar[1];
//
	switch((int)shpar[2])
	{
		case 1:
			jlo = maxJx;
			jhi = minJx;
			nat0 = 0;
			for(int jx=minJx; jx<=maxJx; ++jx)
			{
				real rx2 = twox_ * Fabs(jx * dx.data[0] - xcm);
				if (rx2 <= shpar[0])
				{
					for(int jy=minJy; jy<=maxJy; ++jy)
					{
						real ry2 = jy * dx.data[1] - ycm;
						ry2 = ry2 * ry2;
						for(int jz=minJz; jz<=maxJz; ++jz)
						{
							real rz2 = jz * dx.data[2] - zcm;
							rz2 = rz2 * rz2;
							if (ry2 + rz2 <= r2)
							{
								if (nat0 >= curSize)
								{
									ixyz.Extend(nz);
									curSize = ixyz.GetSize(0);
								}
								ixyz.Fill3(nat0, jx, jy, jz);
								int index = GetLinearAddress(nat0);
								Composer(index, 0);
								iocc[index] = true;
								if (jx < jlo) 
									jlo = jx;
								if (jx > jhi) 
									jhi = jx;
								++nat0;
							}
						}
					}
				}
			}
			break;

		case 2:
			jlo = maxJy;
			jhi = minJy;
			nat0 = 0;
			for(int jx=minJx; jx<=maxJx; ++jx)
			{
				real rx2 = jx * dx.data[0] - xcm;
				rx2 = rx2 * rx2;
				for(int jy=minJy; jy<=maxJy; ++jy)
				{
					real ry2 = twox_ * Fabs(jy * dx.data[1] - ycm);
					if (ry2 <= shpar[0])
					{
						for(int jz=minJz; jz<=maxJz; ++jz)
						{
							real rz2 = jz * dx.data[2] - zcm;
							rz2 = rz2 * rz2;
							if (rx2 + rz2 <= r2)
							{
								if (nat0 >= curSize)
								{
									ixyz.Extend(nz);
									curSize = ixyz.GetSize(0);
								}
								ixyz.Fill3(nat0, jx, jy, jz);
								int index = GetLinearAddress(nat0);
								Composer(index, 0);
								iocc[index] = true;
								if (jy < jlo)
									jlo = jy;
								if (jy > jhi) 
									jhi = jy;
								++nat0;
							}
						}
					}
				}
			}
			break;

		case 3:
			jlo = maxJz;
			jhi = minJz;
			nat0 = 0;
			for(int jx=minJx; jx<=maxJx; ++jx)
			{
				real rx2 = jx * dx.data[0] - xcm;
				rx2 = rx2 * rx2;
				for(int jy=minJy; jy<=maxJy; ++jy)
				{
					real ry2 = jy * dx.data[1] - ycm;
					ry2 = ry2 * ry2;
					if (rx2 + ry2 <= r2)
					{
						for(int jz=minJz; jz<=maxJz; ++jz)
						{
							real rz2 = twox_ * Fabs(jz * dx.data[2] - zcm);
							if (rz2 <= shpar[0])
							{
								if (nat0 >= curSize)
								{
									ixyz.Extend(nz);
									curSize = ixyz.GetSize(0);
								}
								ixyz.Fill3(nat0, jx, jy, jz);
								int index = GetLinearAddress(nat0);
								Composer(index, 0);
								iocc[index] = true;
								if (jz < jlo) 
									jlo = jz;
								if (jz > jhi) 
									jhi = jz;
			                    ++nat0;
							}
						}
					}
				}
			}
			break;

		default:
			break;
	}
	int nlay = jhi - jlo + 1;
	ixyz.Close(nat0);
//
// NLAY = number of layers in cylinder
// NFAC = number of atoms in slice
	int nfac = nat0 / nlay;
//
// REFF2=effective radius**2 of disk
	real reff2 = (real)nfac / Pi;
//
// ASPR=aspect ratio (length/diameter)
	real aspr = half_ * (real)nlay / Sqrt(reff2);
//
// Description
	sprintf(freeDescr, " Cyl.prism, NAT=%7d NFAC=%4d NLAY=%4d asp.ratio=%lf", nat0, nfac, nlay, aspr);
}