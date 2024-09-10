///  Draw 3D
void Demos::Hedrons(Adafruit_SSD1306& d)
{
	if (hdtOn)
	{	++hdt;
		if (hdt >= hdtMax)
		{	hdt = 0;  ++hdCur;  // next type
			if (hdCur >= hdA)  hdCur = 0;
	}	}
	const int u = hdCur;

	const float SC = SCa[u];  // scale
	float rx=0.f,ry=0.f,rz=0.f, s = SC, ss=1.f;
	switch (hdRot)  //par rot speed
	{	case 0:  rx = t*0.0055f;  ry = t*0.0065f;  rz = t*0.0075f;  break;
		case 1:  rx = t*0.0061f;  ry = t*0.0084f;  rz = t*0.0077f;  break;
		case 2:  rx = t*0.0067f;  ry = t*0.0098f;  rz = t*0.0083f;
			ss = 1.0f - 0.4f * (abs(cos(t*0.0125f)));  break;
		case 3:  ry = t*0.0060f;  rz = t*0.0020f;  break;
	}

	const int NP = NPa[u], NE = NEa[u], NF = NFa[u];
	const float* pp = ppA[u];
	const uint8_t* ee = eeA[u], *ff = ffA[u];

	const float  ///par  z pos  screen scale
		fovy = 30.f, zz = 3.f, se = 2.f,
		fv = 1.f/tan(fovy*0.5f),  // const
		cx = cos(rx), sx = sin(rx), cy = cos(ry), sy = sin(ry),
		cz = cos(rz), sz = sin(rz),
		mx[3][3] = {{1.f,0.f,0.f},{0.f,cx,-sx},{0.f,sx,cx}},  // rot x
		my[3][3] = {{cy,0.f,sy},{0.f,1.f,0.f},{-sy,0.f,cy}},  // y
		mz[3][3] = {{cz,-sz,0.f},{sz,cz,0.f},{0.f,0.f,1.f}};  // z


	//  transform all points
	int16_t px[NP], py[NP];  int8_t c[NP];
	int i, a;
	for (i=0,a=0; i < NP; ++i)
	{
		float x = pp[a++], y = pp[a++], z = pp[a++];
		float v[3];
		v[0] = mx[0][0]*x +mx[0][1]*y +mx[0][2]*z;  // rotate
		v[1] = mx[1][0]*x +mx[1][1]*y +mx[1][2]*z;
		v[2] = mx[2][0]*x +mx[2][1]*y +mx[2][2]*z;
		x = v[0];  y = v[1];  z = v[2];
		v[0] = my[0][0]*x +my[0][1]*y +my[0][2]*z;
		v[1] = my[1][0]*x +my[1][1]*y +my[1][2]*z;
		v[2] = my[2][0]*x +my[2][1]*y +my[2][2]*z;
		x = v[0];  y = v[1];  z = v[2];
		v[0] = mz[0][0]*x +mz[0][1]*y +mz[0][2]*z;
		v[1] = mz[1][0]*x +mz[1][1]*y +mz[1][2]*z;
		v[2] = mz[2][0]*x +mz[2][1]*y +mz[2][2]*z;
		x = v[0] * s;  y = v[1] * s;  z = v[2] * s + ss*zz;

		px[i] = H/2 * se * (fv * x / -z) +W/2;  // pos 3d to 2d
		py[i] = H/2 * se * (fv * y / -z) +H/2;

		c[i] = z < 0.9f ? -1 : (z < zz ? 1 : 0);
		if (px[i]<0 || px[i]>=W || py[i]<0 || py[i]>=H)
			c[i] = -1;  // outside
		//c[i] = z < zz ? 1 : 0;
		//d.drawPixel(px[i], py[i],WHITE);
	}
	
	//  draw far/covered edges  --
	for (i=0,a=0; i < NE; ++i)
	{
		int e0 = ee[a++], e1 = ee[a++];
		int8_t cc = max(c[e0],c[e1]);
		if (cc==0)
			d.drawLine( px[e0],py[e0], px[e1],py[e1], WHITE);
	}

	//  draw far faces  /|
	if (ff)
	for (i=0,a=0; i < NF; ++i)
	{
		int f0 = ff[a++], f1 = ff[a++], f2 = ff[a++];
		int8_t cc = min(c[f0],c[f1]);  cc = min(cc,c[f2]);
		if (cc==0)
			d.fillTriangle( px[f0],py[f0], px[f1],py[f1], px[f2],py[f2], WHITE);
	}

	//  dither 2 full screen  --------
	uint8_t* buf = d.getBuffer();
	for (i=0; i < W*H/8; i+=2)  buf[i] &= 0xAA;
	for (i=1; i < W*H/8; i+=2)  buf[i] &= 0x55;

	//  draw near/visible edges  --
	for (i=0,a=0; i < NE; ++i)
	{
		int e0 = ee[a++], e1 = ee[a++];
		int8_t cc = max(c[e0],c[e1]);
		if (cc>0)
			d.drawLine( px[e0],py[e0], px[e1],py[e1], WHITE);
	}
	
	//  draw near faces  /|
	if (ff)
	for (i=0,a=0; i < NF; ++i)
	{
		int f0 = ff[a++], f1 = ff[a++], f2 = ff[a++];
		int8_t cc = min(c[f0],c[f1]);  cc = min(cc,c[f2]);
		if (cc>0)
			d.fillTriangle( px[f0],py[f0], px[f1],py[f1], px[f2],py[f2], WHITE);
	}

	if (iInfo > 0)
	{
		d.setCursor(0,8);
		d.print("Cur ");  d.println(hdCur);
		d.print("Rot ");  d.println(hdRot);
		if (hdtOn)  d.println("On");
	}
	++t;
	delay(8);
}