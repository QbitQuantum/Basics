void CSMFReadMap::UpdateVertexNormalsUnsynced(const SRectangle& update)
{
	#ifdef USE_UNSYNCED_HEIGHTMAP
	const float*  shm = &cornerHeightMapSynced[0];
		  float*  uhm = &cornerHeightMapUnsynced[0];
		  float3* vvn = &visVertexNormals[0];

	const int W = mapDims.mapxp1;
	const int H = mapDims.mapyp1;
	static const int SS = SQUARE_SIZE;

	// a heightmap update over (x1, y1) - (x2, y2) implies the
	// normals change over (x1 - 1, y1 - 1) - (x2 + 1, y2 + 1)
	const int minx = std::max(update.x1 - 1,     0);
	const int minz = std::max(update.y1 - 1,     0);
	const int maxx = std::min(update.x2 + 1, W - 1);
	const int maxz = std::min(update.y2 + 1, H - 1);

	for_mt(minz, maxz+1, [&](const int z) {
		for (int x = minx; x <= maxx; x++) {
			const int vIdxTL = (z    ) * W + x;

			const int xOffL = (x >     0)? 1: 0;
			const int xOffR = (x < W - 1)? 1: 0;
			const int zOffT = (z >     0)? 1: 0;
			const int zOffB = (z < H - 1)? 1: 0;

			const float sxm1 = (x - 1) * SS;
			const float sx   =       x * SS;
			const float sxp1 = (x + 1) * SS;

			const float szm1 = (z - 1) * SS;
			const float sz   =       z * SS;
			const float szp1 = (z + 1) * SS;

			const int shxm1 = x - xOffL;
			const int shx   = x;
			const int shxp1 = x + xOffR;

			const int shzm1 = (z - zOffT) * W;
			const int shz   =           z * W;
			const int shzp1 = (z + zOffB) * W;

			// pretend there are 8 incident triangle faces per vertex
			// for each these triangles, calculate the surface normal,
			// then average the 8 normals (this stays closest to the
			// heightmap data)
			// if edge vertex, don't add virtual neighbor normals to vn
			const float3 vmm = float3(sx  ,  shm[shz   + shx  ],  sz  );

			const float3 vtl = float3(sxm1,  shm[shzm1 + shxm1],  szm1) - vmm;
			const float3 vtm = float3(sx  ,  shm[shzm1 + shx  ],  szm1) - vmm;
			const float3 vtr = float3(sxp1,  shm[shzm1 + shxp1],  szm1) - vmm;

			const float3 vml = float3(sxm1,  shm[shz   + shxm1],  sz  ) - vmm;
			const float3 vmr = float3(sxp1,  shm[shz   + shxp1],  sz  ) - vmm;

			const float3 vbl = float3(sxm1,  shm[shzp1 + shxm1],  szp1) - vmm;
			const float3 vbm = float3(sx  ,  shm[shzp1 + shx  ],  szp1) - vmm;
			const float3 vbr = float3(sxp1,  shm[shzp1 + shxp1],  szp1) - vmm;

			float3 vn(0.0f, 0.0f, 0.0f);
			vn += vtm.cross(vtl) * (zOffT & xOffL); assert(vtm.cross(vtl).y >= 0.0f);
			vn += vtr.cross(vtm) * (zOffT        ); assert(vtr.cross(vtm).y >= 0.0f);
			vn += vmr.cross(vtr) * (zOffT & xOffR); assert(vmr.cross(vtr).y >= 0.0f);
			vn += vbr.cross(vmr) * (        xOffR); assert(vbr.cross(vmr).y >= 0.0f);
			vn += vtl.cross(vml) * (        xOffL); assert(vtl.cross(vml).y >= 0.0f);
			vn += vbm.cross(vbr) * (zOffB & xOffR); assert(vbm.cross(vbr).y >= 0.0f);
			vn += vbl.cross(vbm) * (zOffB        ); assert(vbl.cross(vbm).y >= 0.0f);
			vn += vml.cross(vbl) * (zOffB & xOffL); assert(vml.cross(vbl).y >= 0.0f);

			// update the visible vertex/face height/normal
			uhm[vIdxTL] = shm[vIdxTL];
			vvn[vIdxTL] = vn.ANormalize();
		}
	});
	#endif
}