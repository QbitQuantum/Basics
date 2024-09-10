int createOctTree(octNode * root,const geBitmap_Info * Info,const void * Bits,geBoolean doYUV)
{
int nLeaves;
int w,h,xtra,bpp,x,y;
gePixelFormat Format;
const gePixelFormat_Operations * ops;
int R,G,B,A;
gePixelFormat_Decomposer Decompose;

	assert(Bits);

	nLeaves = 0;

	Format = Info->Format;
	w = Info->Width;
	h = Info->Height;
	xtra = Info->Stride - Info->Width;
	bpp = gePixelFormat_BytesPerPel(Format);

	ops = gePixelFormat_GetOperations(Format);
	assert(ops);
	Decompose = ops->DecomposePixel;
	assert(Decompose);

//	pushTSC();

	if ( doYUV )
	{
		switch(bpp)
		{
			default:
			case 0:
				return GE_FALSE;
			case 1:
			{
			const uint8 *ptr;
				ptr = Bits;
				for(y=h;y--;)
				{
					for(x=w;x--;)
					{
						Decompose(*ptr++,&R,&G,&B,&A);
						RGBi_to_YUVi(R,G,B,&R,&G,&B);
						addOctNode(root,R,G,B,&nLeaves);
					}
					ptr += xtra;
				}
				break;
			}
			case 2:
			{
			const uint16 *ptr;
			uint32 R,G,B,A;
				ptr = Bits;
				for(y=h;y--;)
				{
					for(x=w;x--;)
					{
						Decompose(*ptr++,&R,&G,&B,&A);
						RGBi_to_YUVi(R,G,B,&R,&G,&B);
						addOctNode(root,R,G,B,&nLeaves);
					}
					ptr += xtra;
				}
				break;
			}

			case 3:
			{
			const uint8 *ptr;
			uint32 R,G,B,A,Pixel;

				ptr = Bits;
				xtra *= 3;

				switch(Format)
				{
				case GE_PIXELFORMAT_24BIT_RGB :
					for(y=h;y--;)
					{
						for(x=w;x--;)
						{
							RGBb_to_YUVi(ptr,&R,&G,&B);
							ptr += 3;
							addOctNode(root,R,G,B,&nLeaves);
						}
						ptr += xtra;
					}
					break;
				case GE_PIXELFORMAT_24BIT_BGR :
					for(y=h;y--;)
					{
						for(x=w;x--;)
						{
							B = *ptr++;
							G = *ptr++;
							R = *ptr++;
							RGBi_to_YUVi(R,G,B,&R,&G,&B);
							addOctNode(root,R,G,B,&nLeaves);
						}
						ptr += xtra;
					}
					break;
				default:
					// can't get here now
					for(y=h;y--;)
					{
						for(x=w;x--;)
						{
							Pixel = (ptr[0]<<16) + (ptr[1]<<8) + ptr[2]; ptr += 3;
							Decompose(Pixel,&R,&G,&B,&A);
							RGBi_to_YUVi(R,G,B,&R,&G,&B);
							addOctNode(root,R,G,B,&nLeaves);
						}
						ptr += xtra;
					}
					break;
				}
				break;  // Thanks Bobtree
			}

			case 4:
			{
			const uint32 *ptr;
			uint32 R,G,B,A;
				ptr = Bits;
				for(y=h;y--;)
				{
					for(x=w;x--;)
					{
						Decompose(*ptr++,&R,&G,&B,&A);
						RGBi_to_YUVi(R,G,B,&R,&G,&B);
						addOctNode(root,R,G,B,&nLeaves);
					}
					ptr += xtra;
				}
				break;
			}
		}
	}
	else
	{
		switch(bpp)
		{
			default:
			case 0:
				return GE_FALSE;
			case 1:
			{
			const uint8 *ptr;
				ptr = Bits;
				for(y=h;y--;)
				{
					for(x=w;x--;)
					{
						Decompose(*ptr++,&R,&G,&B,&A);
						addOctNode(root,R,G,B,&nLeaves);
					}
					ptr += xtra;
				}
				break;
			}
			case 2:
			{
			const uint16 *ptr;
			uint32 R,G,B,A;
				ptr = Bits;
				for(y=h;y--;)
				{
					for(x=w;x--;)
					{
						Decompose(*ptr++,&R,&G,&B,&A);
						addOctNode(root,R,G,B,&nLeaves);
					}
					ptr += xtra;
				}
				break;
			}

			case 3:
			{
			const uint8 *ptr;
			uint32 R,G,B,A,Pixel;

				ptr = Bits;
				xtra *= 3;

				switch(Format)
				{
				case GE_PIXELFORMAT_24BIT_RGB :
					for(y=h;y--;)
					{
						for(x=w;x--;)
						{
							R = *ptr++;
							G = *ptr++;
							B = *ptr++;
							addOctNode(root,R,G,B,&nLeaves);
						}
						ptr += xtra;
					}
					break;
				case GE_PIXELFORMAT_24BIT_BGR :
					for(y=h;y--;)
					{
						for(x=w;x--;)
						{
							B = *ptr++;
							G = *ptr++;
							R = *ptr++;
							addOctNode(root,R,G,B,&nLeaves);
						}
						ptr += xtra;
					}
					break;
				default:
					// can't get here now
					for(y=h;y--;)
					{
						for(x=w;x--;)
						{
							Pixel = (ptr[0]<<16) + (ptr[1]<<8) + ptr[2]; ptr += 3;
							Decompose(Pixel,&R,&G,&B,&A);
							addOctNode(root,R,G,B,&nLeaves);
						}
						ptr += xtra;
					}
					break;
				}
				break;		// Thanks Bobtree
			}

			case 4:
			{
			const uint32 *ptr;
			uint32 R,G,B,A;
				ptr = Bits;
				for(y=h;y--;)
				{
					for(x=w;x--;)
					{
						Decompose(*ptr++,&R,&G,&B,&A);
						addOctNode(root,R,G,B,&nLeaves);
					}
					ptr += xtra;
				}
				break;
			}
		}
	}

//	showPopTSC("create Pal OctTree");

return nLeaves;
}