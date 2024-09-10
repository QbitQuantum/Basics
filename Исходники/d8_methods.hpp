void d8_flats_alter_dem(
  const int_2d &flat_mask,
  const int_2d &labels,
  array2d<U> &elevations
){
  ProgressBar progress;

  diagnostic("%%Calculating D8 flow directions using flat mask...\n");
  progress.start( flat_mask.width()*flat_mask.height() );
  #pragma omp parallel for
  for(int x=1;x<flat_mask.width()-1;x++){
    progress.update( x*flat_mask.height() );
    for(int y=1;y<flat_mask.height()-1;y++){
      if(labels(x,y)==0)
        continue;

      bool higher[9];
      for(int n=1;n<=8;++n)
        higher[n]=elevations(x,y)>elevations(x+dx[n],y+dy[n]);
      //TODO: nextafterf is the floating point version; should use an
      //overloaded version instead to be able to handle both double and float
      for(int i=0;i<flat_mask(x,y);++i)
        elevations(x,y)=nextafterf(elevations(x,y),std::numeric_limits<U>::infinity());
      for(int n=1;n<=8;++n){
        int nx=x+dx[n];
        int ny=y+dy[n];      
        if(labels(nx,ny)==labels(x,y))
          continue;
        if(elevations(x,y)<elevations(nx,ny))
          continue;
        if(!higher[n])
          diagnostic_arg("Attempting to raise (%d,%d) resulted in an invalid alteration of the DEM!\n",x,y);
      }
    }
  }
  diagnostic_arg(SUCCEEDED_IN,progress.stop());
}