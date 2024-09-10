void
Trail::UpdateVerts(const Point& cam_pos)
{
	if (ntrail < 2) return;

	int bright = 255 - dim*ntrail;

	Point head  = trail[1] + loc;
	Point tail  = trail[0] + loc;
	Point vcam  = cam_pos - head;
	Point vtmp  = vcam.cross(head-tail);
	vtmp.Normalize();
	Point vlat  = vtmp * (width + (0.1 * width * ntrail));

	verts->loc[0]     = tail - vlat;
	verts->loc[1]     = tail + vlat;
	verts->diffuse[0] = 0;
	verts->diffuse[1] = 0;

	for (int i = 0; i < ntrail-1; i++) {
		bright+=dim;
		Point head  = trail[i+1] + loc;
		Point tail  = trail[i] + loc;
		Point vcam  = cam_pos - head;
		Point vtmp  = vcam.cross(head-tail);
		vtmp.Normalize();
		
		float trail_width = (float) (width + (ntrail-i) * width * 0.1);
		if (i == ntrail-2) trail_width = (float) (width * 0.7);
		Point vlat  = vtmp * trail_width;

		verts->loc[2*i+2] = head - vlat;
		verts->loc[2*i+3] = head + vlat;

		if (bright <= 0) {
			verts->diffuse[2*i+2] = 0;
			verts->diffuse[2*i+3] = 0;
		}
		else {
			verts->diffuse[2*i+2] = D3DCOLOR_RGBA(bright,bright,bright,bright);
			verts->diffuse[2*i+3] = D3DCOLOR_RGBA(bright,bright,bright,bright);
		}
	}
}