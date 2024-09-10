void CGraphStatic::DrawPixcel(CDC& memdc,double x, double y)
{
#if 0
	 double MultiplyOnX = m_xpixel/1440.0;	

	 double MultiplyOnY = m_ypixel/30.0;

	 double r_y = -((y-30)*MultiplyOnY);
	 double r_x = x * MultiplyOnX;
	 TRACE("r_x = %f,r_y=%f\n",r_x,r_y);
	 memdc.SetPixel(round(r_x),round(r_y),RGB(0,0,255));
#else
	CPen DataPen,*pOldPen;
    DataPen.CreatePen(PS_SOLID,1, RGB(0, 0, 255));
	pOldPen=memdc.SelectObject(&DataPen);

     if(x == 0)
     {

	        GetPoint(x,y);
            memdc.MoveTo(x,y);

     }
     else
     {
	        GetPoint(x,y);
            memdc.LineTo(x,y);
     }


//	 TRACE("r_x = %f,r_y=%f\n",x,y);
     for(int i = -2;i<3;i++)
     {
        for(int j = -2;j<3;j++)
        {
	        memdc.SetPixel(round(x+i),round(y+j),RGB(0,0,255));
        }
     }
     memdc.SelectObject(pOldPen);

#endif	 
}