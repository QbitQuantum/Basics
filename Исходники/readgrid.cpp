extern "C" int readgrid_(float *vdata, int *nx, int *ny, int *nz,
  float *x0, float *y0, float *z0, float *xx, float *yy, float *zz,
  char *file, int fsize) {

  float dx,dy,dz;
  int gsize;
  float v, vmin, vmax, vavg;
  int navg = 0;

  OBMol mol;
  OBConversion conv;
  conv.SetInFormat("cube");
 
  std::string fname = file;
  int blank = fname.find(" ");
  //printf("%d,'%s'\n", blank, fname.substr(0,blank).c_str());
  conv.ReadFile(&mol, fname.substr(0,blank).c_str());
  //cout << mol.NumAtoms() << " atoms." << endl;
  if (mol.HasData(OBGenericDataType::GridData)) {
    std::vector<OBGenericData*> grids = mol.GetAllData(OBGenericDataType::GridData);
    OBGridData *grid = dynamic_cast<OBGridData *> (grids[0]);
    gsize = grid->GetNumberOfPoints();
    grid->GetNumberOfPoints(*nx, *ny, *nz);
    vector3 origin = grid->GetOriginVector();
    *x0 = origin[0]; *y0 = origin[1]; *z0 = origin[2];
    vector3 maxv = grid->GetMaxVector();
    *xx = maxv[0]; *yy = maxv[1]; *zz = maxv[2];
    dx=(*xx-*x0)/(*nx-1);
    dy=(*yy-*y0)/(*ny-1);
    dz=(*zz-*z0)/(*nz-1);
    printf("%s %d=%d*%d*%d\n", grid->GetAttribute().c_str(), gsize, *nx, *ny, *nz);
    printf("%f %f\n", grid->GetMinValue(), grid->GetMaxValue());
    printf("%f,%f,%f\n", *x0,*y0,*z0);
    printf("%f,%f,%f\n", *xx,*yy,*zz);
    printf("%f,%f,%f\n", dx,dy,dz);
 
    //vdata = (float *)calloc(gsize, sizeof(float));
/* this is for fortran, so reverse sense of slowest/fastest moving dimensions */
    //for (int i=0; i<*nx; ++i) {
    vmin = grid->GetValue(0,0,0);
    vmax = vmin;
    for (int i=0; i<*nz; ++i) {
      for (int j=0; j<*ny; ++j) {
        //for (int k=0; k<*nz; ++k) {
        for (int k=0; k<*nx; ++k) {
          //*vdata++ = grid->GetValue(i,j,k);
          v = grid->GetValue(k,j,i);
          if (v < 1e30 && v > -1e30) {
            if (v < vmin) vmin = v;
            if (v > vmax) vmax = v;
            ++navg;
            vavg += v;
          } else {
            v = vmax * 1000; // just a guess
          }
          *vdata++ = v;
        }
      }
    }
  }
  vavg = vavg/navg;
  printf("min/avg/max = %f/%f/%f\n", vmin, vavg, vmax);
  return 0;
}