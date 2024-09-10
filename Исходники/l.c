int main()


{

long double Cx;
long double l;

// setup 
dC = CxMax - CxMin;  
dl = lMax - lMin;
step_l = dl/iPixelsNumber;
eMin = expl(lMin); // = expl(lMin); // 0.0 < eMin < 1.0 
eMax = expl(lMax); // 1.0
de = eMax - eMin;

// go along real axis from CxMin to CxMax using nonlinear scale 
l = lMin;
Cx = GiveC(l);
printf("c = %.20Lf \n",Cx);
while (l<lMax)
{ 
  // info message
  Cx = GiveC(l);
  printf("c = %.20Lf \n",Cx);
  // next  point 
  l += step_l;
}

  printf("nonlinear scale \n" );
return 0;
}