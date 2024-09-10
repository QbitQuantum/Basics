void DrawCursor(int x,int y)    /* 在鼠标当前位置画鼠标指针 和 跟随鼠标移动的直线 */
{  int color;
   char str[50];
  line(x-6,y,x-2,y);
  line(x,y-6,x,y-3);
  line(x+2,y,x+6,y);
  line(x,y+3,x,y+6);

 if(LineDrawFlag==TRUE)
  {

  line(x_New,y_New,x,y);

  }
  color=getcolor();
  setcolor(getbkcolor());
  outtextxy(10,20,str);
  sprintf(str,"(%d,%d)",x,y);  /* 显示鼠标当前的坐标值 */
  setcolor(WHITE);
  outtextxy(10,20,str);
  setcolor(color);
}