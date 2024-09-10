BOOL CTyBase::PointRgn(float x, float y, int Numble, PointStruct *PointList, float blc)
{
	CRgn rgn; 
	int x1,y1,i;
	CPoint bbcc[MAXPOINTNUM];
	
	if(Numble < 3) 
		return 0;//如果点的数目<3即不是一个区域返回不成功标志

	ASSERT(Numble <= MAXPOINTNUM);

	//将点的坐标转变成屏幕坐标
	x1 = (int)(x/blc);
	y1 = (int)(y/blc);

	//将封闭区域各点的坐标转成屏幕坐标
	for(i = 0;i < Numble;i++)
	{
		bbcc[i].x = (int)((PointList[i].x)/blc);
		bbcc[i].y = (int)((PointList[i].y)/blc);
	}

	rgn.CreatePolygonRgn(bbcc,Numble,1);//初试化一个多边形区域
	i = (rgn.PtInRegion(x1,y1)!=0);		//如果在区域内j=1,否则j=0;
	rgn.DeleteObject();					        //删除定义的rgn对象

	return i;
}