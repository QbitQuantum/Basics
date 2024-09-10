// Rotation kring godtycklig axel (enbart rotationen)
void ArbRotate(Point3D *axis, GLfloat fi, GLfloat *m)
{
	Point3D x, y, z, a;
	GLfloat R[16], Rt[16], Raxel[16], RtRx[16];
	
// Kolla ocksŒ om parallell med Z-axel!
	if (axis->x < 0.0000001) // Under nŒgon tillrŠckligt liten grŠns
	if (axis->x > -0.0000001)
	if (axis->y < 0.0000001)
	if (axis->y > -0.0000001)
		if (axis->z > 0)
		{
			Rz(fi, m);
			return;
		}
		else
		{
			Rz(-fi, m);
			return;
		}

	x = *axis;
	Normalize(&x); // |x|
	SetVector(0,0,1, &z); // Temp z
	CrossProduct(&z, &x, &y);
	Normalize(&y); // y' = z^ x x'
	CrossProduct(&x, &y, &z); // z' = x x y

	R[0] = x.x; R[4] = x.y; R[8] = x.z;  R[12] = 0.0;
	R[1] = y.x; R[5] = y.y; R[9] = y.z;  R[13] = 0.0;
	R[2] = z.x; R[6] = z.y; R[10] = z.z;  R[14] = 0.0;

	R[3] = 0.0; R[7] = 0.0; R[11] = 0.0;  R[15] = 1.0;

	Transpose(&R, &Rt); // Transpose = Invert -> felet ej i Transpose, och det Šr en ortonormal matris
	
	Rx(fi, &Raxel); // Rotate around x axis
	
	// m := Rt * Rx * R
	Mult(&Rt, &Raxel, &RtRx);
	Mult(&RtRx, &R, m);
}