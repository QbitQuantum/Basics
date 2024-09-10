void MapObject::ScreenPos2MapPos(int ScreenX, int ScreenY, Matrix MVP, float &MapX, float &MapY)
{
	__UINT32 W = VIEWCLASS::GetInstance()->GetWidth();
	__UINT32 H = VIEWCLASS::GetInstance()->GetHeight();
	SPosition2D<float> fpos;
	SPosition2D<float> fpos2;
	MVP.Inverse();

	fpos.X = (float(ScreenX)*2 - W)/W;
	fpos.Y = (float(ScreenY)*2 - H)/H;

	//Use ray to detect the point that cursor point to
	Vector v1(	fpos.X,
				fpos.Y,
				0,
				1);

	Vector v2(	fpos.X,
				fpos.Y,
				10,
				1);

	float* v1data = v1.GetData();
	float* v2data = v2.GetData();
	//Mult inverse matrix
	v1 = MVP.MultVector(v1);v1.Normalize();
	v2 = MVP.MultVector(v2);v2.Normalize();
	v1data = v1.GetData();
	v2data = v2.GetData();

	//Calculate position in object coordinate
	float t = (v1data[2])/(v1data[2]-v2data[2]);
	fpos2.X = v1data[0] + (v2data[0]-v1data[0])*t;
	fpos2.Y = v1data[1] + (v2data[1]-v1data[1])*t;


	MapX = fpos2.X;
	MapY = fpos2.Y;
}