// Based on Paul Bourke's triangulate.c
//  http://astronomy.swin.edu.au/~pbourke/terrain/triangulate/triangulate.c
static void delaunay(const int nv, float *verts, rcIntArray& idx, rcIntArray& tris, rcIntArray& edges)
{
	// Sort vertices
	idx.resize(nv);
	for (int i = 0; i < nv; ++i)
		idx[i] = i;
#ifdef WIN32
	qsort_s(&idx[0], idx.size(), sizeof(int), ptcmp, verts);
#else
	qsort_r(&idx[0], idx.size(), sizeof(int), verts, ptcmp);
#endif

	// Find the maximum and minimum vertex bounds.
	// This is to allow calculation of the bounding triangle
	float xmin = verts[0];
	float ymin = verts[2];
	float xmax = xmin;
	float ymax = ymin;
	for (int i = 1; i < nv; ++i)
	{
		xmin = rcMin(xmin, verts[i*3+0]);
		xmax = rcMax(xmax, verts[i*3+0]);
		ymin = rcMin(ymin, verts[i*3+2]);
		ymax = rcMax(ymax, verts[i*3+2]);
	}
	float dx = xmax - xmin;
	float dy = ymax - ymin;
	float dmax = (dx > dy) ? dx : dy;
	float xmid = (xmax + xmin) / 2.0f;
	float ymid = (ymax + ymin) / 2.0f;
	
	// Set up the supertriangle
	// This is a triangle which encompasses all the sample points.
	// The supertriangle coordinates are added to the end of the
	// vertex list. The supertriangle is the first triangle in
	// the triangle list.
	float sv[3*3];
	
	sv[0] = xmid - 20 * dmax;
	sv[1] = 0;
	sv[2] = ymid - dmax;
	
	sv[3] = xmid;
	sv[4] = 0;
	sv[5] = ymid + 20 * dmax;
	
	sv[6] = xmid + 20 * dmax;
	sv[7] = 0;
	sv[8] = ymid - dmax;
	
	tris.push(-3);
	tris.push(-2);
	tris.push(-1);
	tris.push(0); // not completed
	
	for (int i = 0; i < nv; ++i)
	{
		const float xp = verts[idx[i]*3+0];
		const float yp = verts[idx[i]*3+2];
		
		edges.resize(0);
		
		// Set up the edge buffer.
		// If the point (xp,yp) lies inside the circumcircle then the
		// three edges of that triangle are added to the edge buffer
		// and that triangle is removed.
		for (int j = 0; j < tris.size()/4; ++j)
		{
			int* t = &tris[j*4];
			if (t[3]) // completed?
				continue;
			const float* v1 = t[0] < 0 ? &sv[(t[0]+3)*3] : &verts[idx[t[0]]*3];
			const float* v2 = t[1] < 0 ? &sv[(t[1]+3)*3] : &verts[idx[t[1]]*3];
			const float* v3 = t[2] < 0 ? &sv[(t[2]+3)*3] : &verts[idx[t[2]]*3];
			float xc,yc,rsqr;
			int inside = circumCircle(xp,yp, v1[0],v1[2], v2[0],v2[2], v3[0],v3[2], xc,yc,rsqr);
			if (xc < xp && rcSqr(xp-xc) > rsqr)
				t[3] = 1;
			if (inside)
			{
				// Collect triangle edges.
				edges.push(t[0]);
				edges.push(t[1]);
				edges.push(t[1]);
				edges.push(t[2]);
				edges.push(t[2]);
				edges.push(t[0]);
				// Remove triangle j.
				t[0] = tris[tris.size()-4];
				t[1] = tris[tris.size()-3];
				t[2] = tris[tris.size()-2];
				t[3] = tris[tris.size()-1];
				tris.resize(tris.size()-4);
				j--;
			}
		}
		
		// Remove duplicate edges.
		const int ne = edges.size()/2;
		for (int j = 0; j < ne-1; ++j)
		{
			for (int k = j+1; k < ne; ++k)
			{
				// Dupe?, make null.
				if ((edges[j*2+0] == edges[k*2+1]) && (edges[j*2+1] == edges[k*2+0]))
				{
					edges[j*2+0] = 0;
					edges[j*2+1] = 0;
					edges[k*2+0] = 0;
					edges[k*2+1] = 0;
				}
			}
		}
		
		// Form new triangles for the current point
		// Skipping over any null.
		// All edges are arranged in clockwise order.
		for (int j = 0; j < ne; ++j)
		{
			if (edges[j*2+0] == edges[j*2+1]) continue;
			tris.push(edges[j*2+0]);
			tris.push(edges[j*2+1]);
			tris.push(i);
			tris.push(0); // not completed
		}
	}
	
	// Remove triangles with supertriangle vertices
	// These are triangles which have a vertex number greater than nv
	for (int i = 0; i < tris.size()/4; ++i)
	{
		int* t = &tris[i*4];
		if (t[0] < 0 || t[1] < 0 || t[2] < 0)
		{
			t[0] = tris[tris.size()-4];
			t[1] = tris[tris.size()-3];
			t[2] = tris[tris.size()-2];
			t[3] = tris[tris.size()-1];
			tris.resize(tris.size()-4);
			i--;
		}
	}
	// Triangle vertices are pointing to sorted vertices, remap indices.
	for (int i = 0; i < tris.size(); ++i)
		tris[i] = idx[tris[i]];
}