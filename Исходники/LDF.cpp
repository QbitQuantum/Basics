int noCloudLdfBlend(LDF& ldf1, LDF& ldf2, int min, int max, 
	double Xmin, double Xmax, double Xres,
	double Ymin, double Ymax, double Yres)
{
	ldf1.getPixel(1, 0, 0);
	for (int iy = 0; iy < ldf1.m_Line; iy++){
		for (int ix = 0; ix < ldf1.m_Sample; ix++){
			double gx, gy;
			ldf1.pix2geo(ix, iy, gx, gy);
			for (int ib = 3; ib < 5; ib++){
				unsigned short t1 = ldf1.getPixel(ib, ix, iy);
				unsigned short t2 = ldf2.getPixelGeo(ib, ix, iy);
				if (t2 > t1 && t2 < max){
					ldf1.setPixel(ib, ix, iy, t2);
				}
			}
		}
	}
	return 0;
}