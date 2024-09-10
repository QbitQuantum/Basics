/*===============================================================*/
void DrawFractalImage(void)
{ int i,x,step,number;
number=(int) pow(2.0,(double)MAX_LEVEL);
step=getmaxx()/number*3/2;
moveto(0,(int)Array[0]);
for(i=1,x=step;i<number;x+=step,i++) lineto(x,(int)Array[i]);
}