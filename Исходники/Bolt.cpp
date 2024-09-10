void
Bolt::Render(Video* video, DWORD flags)
{
	if ((flags & RENDER_ADDITIVE) == 0)
	return;

	if (visible && !hidden && video && life) {
		const Camera*  camera = video->GetCamera();

		Point head  = loc;
		Point tail  = origin;
		Point vtail = tail - head;
		Point vcam  = camera->Pos() - loc;
		Point vtmp  = vcam.cross(vtail);
		vtmp.Normalize();
		Point vlat  = vtmp * -width;
		Vec3  vnrm  = camera->vpn() * -1;

		vset.loc[0] = head + vlat;
		vset.loc[1] = tail + vlat;
		vset.loc[2] = tail - vlat;
		vset.loc[3] = head - vlat;

		vset.nrm[0] = vnrm;
		vset.nrm[1] = vnrm;
		vset.nrm[2] = vnrm;
		vset.nrm[3] = vnrm;

		ColorValue  white((float) shade, (float) shade, (float) shade);
		mtl.Ka = white;
		mtl.Kd = white;
		mtl.Ks = Color::Black;
		mtl.Ke = white;

		video->DrawPolys(1, &poly);
	}
}