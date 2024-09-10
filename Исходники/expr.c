int decode_function(char *ptr,int argnum,double *argptr,
                    double *value,void *data) {


  int i; 
 
  for (i=0;fnlist[i] !=0;i++) if (strcmp(ptr,fnlist[i])==0) break;

  switch(i) {
    case 0:
      *value=fabs(argptr[0]);
      break;
    case 1: 
      *value=acos(argptr[0]);
      break;
    case 2: 
      *value=acosh(argptr[0]);
      break;
    case 3: 
      *value=asin(argptr[0]);
      break;
    case 4: 
      *value=asinh(argptr[0]);
      break;
    case 5: 
      *value=atan(argptr[0]);
      break;
    case 6: 
      *value=atan2(argptr[0],argptr[1]);
      break;
    case 7: 
      *value=atanh(argptr[0]);
      break;
   case 8: 
      *value=ceil(argptr[0]);
      break;
   case 9: 
      *value=cos(argptr[0]);
      break;
  case 10: 
      *value=cosh(argptr[0]);
      break;
  case 11: 
      *value=exp(argptr[0]);
      break;
  case 12: 
      *value=floor(argptr[0]);
      break;
  case 13: 
      *value=(int) argptr[0];
      break;
  case 14: 
      *value=log(argptr[0]);
      break;
  case 15: 
      *value=log10(argptr[0]);
      break;
  case 16: 
      *value=sin(argptr[0]);
      break;
  case 17: 
      *value=sinh(argptr[0]);
      break;
  case 18: 
      *value=sqrt(argptr[0]);
      break;
  case 19: 
      *value=tan(argptr[0]);
      break;
  case 20: 
      *value=tanh(argptr[0]);
      break;
      
  }
  return 0;
}