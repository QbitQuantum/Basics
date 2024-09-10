//remaining delete
void runbar(int x,int y,int wid,int hei){
	ACL_Image bar;
	char src[]=".\\image.bmp";
	beginPaint();
	//clearDevice();
	loadImage(src,&bar);
	putImageScale(&bar,x,y,wid,hei);
	endPaint();
}