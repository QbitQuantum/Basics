void PacMan::Draw( HDC& memDC)
{
	if(frame%2 ==0)//第4祯动画与第2祯动画
	{
		int x1=0,x2=0,y1=0,y2=0;
		int offsetX =  DISTANCE/2+D_OFFSET;//弧弦交点
		int offsetY =  DISTANCE/2+D_OFFSET;//弧弦交点
		switch(tw) //优弧
		{
		case UP: 
		    x1 = point.x - offsetX;
			x2 = point.x + offsetX;
			y2 = y1 = point.y-offsetY;
			break;
		case DOWN:
		    x1 = point.x + offsetX;
			x2 = point.x - offsetX;
			y2 = y1 = point.y+offsetY;
			break;
		case LEFT:
			x2 = x1 = point.x-offsetX;
			y1 = point.y + offsetY;
			y2 = point.y - offsetY;
			break;
		case RIGHT:
			x2 = x1 =point.x + offsetX;
			y1 = point.y - offsetY;
			y2 = point.y + offsetY;
			break;

		}
		Arc(memDC,point.x-DISTANCE,point.y-DISTANCE,
		point.x+DISTANCE,point.y+DISTANCE,
		x1,y1,
		x2,y2);
		MoveToEx(memDC,x1,y1,NULL);
		LineTo(memDC,point.x,point.y);
		LineTo(memDC,x2,y2);
	}
	else if(frame%3 ==0)  //圆形
	{
		Ellipse(memDC,point.x-DISTANCE,point.y-DISTANCE,
		point.x+DISTANCE,point.y+DISTANCE);
	}
	else {
		int x1=0,x2=0,y1=0,y2=0;
		switch(tw)  //半圆形
		{
		case UP: 
		    x1 = point.x - DISTANCE;
			x2 = point.x + DISTANCE;
			y2 = y1 = point.y;
			break;
		case DOWN:
		    x1 = point.x + DISTANCE;
			x2 = point.x - DISTANCE;
			y2 = y1 = point.y;
			break;
		case LEFT:
			x2 = x1 = point.x;
			y1 = point.y + DISTANCE;
			y2 = point.y - DISTANCE;
			break;
		case RIGHT:
			x2 = x1 =point.x ;
			y1 = point.y - DISTANCE;
			y2 = point.y + DISTANCE;
			break;
		
		}
		
		Arc(memDC,point.x-DISTANCE,point.y-DISTANCE,
		point.x+DISTANCE,point.y+DISTANCE,
		x1,y1,
		x2,y2);
		MoveToEx(memDC,x1,y1,NULL);
		LineTo(memDC,point.x,point.y);
		LineTo(memDC,x2,y2);
	}

		frame++;//绘制下一祯
}