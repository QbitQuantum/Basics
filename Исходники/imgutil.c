void luv2rgb(int *RGB,float *LUV,int size)
{
  int i,k;
  double x,y,X,Y,Z,den,u2,v2,X0,Z0,Y0,u20,v20,vec[3];

  X0 = (0.607+0.174+0.201);
  Y0 = (0.299+0.587+0.114);
  Z0 = (      0.066+1.117);

/* Y0 = 1.0 */
  u20 = 4*X0/(X0+15*Y0+3*Z0);
  v20 = 9*Y0/(X0+15*Y0+3*Z0);

  for (i=0;i<size;i+=3)
  {
    if (LUV[i]>0)
    {
      if (LUV[i]<8.0) Y=((double) LUV[i])/903.3;
      else Y=pow(( ((double) LUV[i]) +16)/116.0,3.0);
      u2=((double) LUV[i+1])/13.0/((double) LUV[i])+u20;
      v2=((double) LUV[i+2])/13.0/((double) LUV[i])+v20;

      den = 6+3*u2-8*v2;
      if (den<0) printf("den<0\n");
      if (den==0) printf("den==0\n");
      x = 4.5*u2/den;
      y = 2.0*v2/den;

      X=x/y*Y;
      Z=(1-x-y)/y*Y;
    }
    else { X=0.0; Y=0.0; Z=0.0; }

    vec[0] = ( 3.240479*X-1.537150*Y-0.498536*Z);
    vec[1] = (-0.969256*X+1.875992*Y+0.041556*Z);
    vec[2] = ( 0.055648*X-0.204043*Y+1.057311*Z);
    for (k=0;k<3;k++)
    {
      if  (vec[k]<=0.018) vec[k] = 255*4.5*vec[k];
      else vec[k] = 255*(1.099*pow(vec[k],0.45)-0.099);
      if (vec[k]>255) vec[k] = 255;
      else if (vec[k]<0) vec[k] = 0;
      RGB[i+k] = lroundf((float)vec[k]);
    }
  }
}