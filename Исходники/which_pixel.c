int pixel_start(int res, char scheme){

  //int res1;
  //long double res_d;
  
  if(res<0){
    fprintf(stderr, "error in pixel_start: %d not a valid resolution.\n", res);
    return(-1);
  }
  
  if(scheme=='s'){
    return ((int)((powl(4,res)-1)/3));
  }
  else if(scheme=='d'){
    //res_d = (long double)(logl((long double)res)/logl(2.0))+1;
    //res1 = (int)(res_d + 0.1);
    //printf("pixel_start: res = %d\n", res);
    if(res==0) return(0);
    else if(res==1) return(1);
    else return (468*(((int)powl(4,res-1)-4)/12)+118);
  }
  else{
    fprintf(stderr, "error in pixel_start: pixel scheme %c not recognized.\n", scheme);
    return(-1);  
  }
  
}  