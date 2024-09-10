float Myron::getTriangleArea(float x0,float y0,float x1,float y1,float x2,float y2){
#define DISTANCE(x,y,xx,yy) (sqrt((x-xx)*(x-xx)+(y-yy)*(y-yy)))
  double a = DISTANCE(x0,y0,x1,y1);
  double b = DISTANCE(x1,y1,x2,y2);
  double c = DISTANCE(x2,y2,x0,y0);
  double s = 0.5*(a+b+c);
  return (float)sqrt(s*(s-a)*(s-b)*(s-c));
}