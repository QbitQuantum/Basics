// Tao hinh sao voi
// iIdentity > 2: nhan dang hinh sao, = 5: hinh sao 5 canh, = 6: hinh sao 6 canh ...
// dAlpha: diem bat dau cua hinh sao co goc la dAlpha
// (x,y) tam cua hinh sao
// iRadius: ban kinh
// iColor: mau cua duong bien hinh sao
void _Polygon::CreateStar(int iIdentity, double dAlpha, int x, int y, int iRadius, int iColor)
{
	CString _strError("");

	if (iIdentity <= 2)
	{
		_strError = "_Polygon::CreateStar() --> iIdentity: Khong du canh de tao hinh sao";
		iIdentity = 3;
	}	

	CArray<POINT> arrTemp;
	POINT temp;
	double dAngle = PI / iIdentity; // goc quay
	double dBeta = (1 - 3.0 / (2*iIdentity)) * PI;
	double dGamma = PI / (2 * iIdentity);
	int iRadius2 = iRadius * (sin(dGamma) / sin(dBeta));

	// Tao cac dinh cua hinh sao
	for (int i = 0; i < 2 * iIdentity; ++i)
	{
		if (i % 2 == 0)
		{		
			temp.x = iRadius * cos(dAlpha + dAngle * i) + x;
			temp.y = iRadius * sin(dAlpha + dAngle * i) + y;
		}
		else
		{
			temp.x = iRadius2 * cos(dAlpha + dAngle * i) + x;
			temp.y = iRadius2 * sin(dAlpha + dAngle * i) + y;
		}
		arrTemp.Add(temp);
	}

	CreatePolygon(arrTemp, iColor);
	strError += _strError; // Gan loi
}