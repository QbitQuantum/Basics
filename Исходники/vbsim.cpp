int
VBSim::Go(int argc,char *argv[])
{
  tokenlist args;
  rng=NULL;
  dimx=0;
  dimy=0;
  dimz=0;
  dimt=0;
  n_mean=10.0;
  n_variance=5.0;
  n_fwhm=0.0;
  float vx=1.0;
  float vy=1.0;
  float vz=1.0;
  float vt=2000;
  uint32 rngseed=VBRandom();

  args.Transfer(argc,argv);

  if (args.size() == 0) {
    vbsim_help();
    exit(0);
  }

  for (size_t i=0; i<args.size(); i++) {
    // -d x y z for dims
    if (args[i]=="-d" && i<args.size()-4) {
      dimx=strtol(args[i+1]);
      dimy=strtol(args[i+2]);
      dimz=strtol(args[i+3]);
      dimt=strtol(args[i+4]);
      i+=4;
    }
    // -c for loading anatomy
    else if (args[i]=="-c" && i<args.size()-1) {
      anatname=args[i+1];
      i++;
    }
    // -z for voxel sizes
    else if (args[i]=="-z" && i<args.size()-3) {
      vx=strtod(args[++i]);
      vy=strtod(args[++i]);
      vz=strtod(args[++i]);
      vt=strtod(args[++i]);
    }
    // -n for per-volume noise
    else if (args[i]=="-n" && i<args.size()-3) {
      n_mean=strtod(args[i+1]);
      n_variance=strtod(args[i+2]);
      n_fwhm=strtod(args[i+3]);
      i+=3;
    }
    else if (args[i]=="-s" && i<args.size()-1)
      rngseed=strtol(args[++i]);
    else if (args[i]=="-o" && i<args.size()-1) {
      outfile=args[i+1];
      i++;
    }
    else {
      printf("[E] vbsim: unrecognized argument %s\n",args(i));
      return 140;
    }
  }
  if (dimx<1 || dimy<0 || dimz<0 || dimt<0) {
    printf("[E] vbsim: bad dimensions\n");
    return 110;
  }

  // initialize RNG
  rng=gsl_rng_alloc(gsl_rng_mt19937);
  assert(rng);
  gsl_rng_set(rng,rngseed);

  // FIXME tell the user here what we're doing

  // CREATE ANATOMY (constant image)
  if (anatname.size()) {
    if (anat.ReadFile(anatname)) {
      printf("[E] vbsim: couldn't read %s\n",anatname.c_str());
      return 101;
    }
    if (anat.dimx!=dimx || anat.dimy!=dimy || anat.dimz != dimz) {
      printf("[E] vbsim: %s doesn't match your dimensions\n",anatname.c_str());
      return 102;
    }
  }
  else {
    // create volume according to dimensions, add random noise if requested
    anat.SetVolume(dimx,dimy,dimz,vb_float);
  }

  // SPECIAL CASE-- vecs if dimy=dimz=dimt==0
  if (dimt==0 && dimy==0 && dimz==0) {
    printf("[I] vbsim: creating a vector with %d elements with N(%g,%g)\n",dimx,
           n_mean,sqrt(n_variance));
    if (outfile=="")
      outfile="data.ref";
    VB_Vector vv(dimx);
    
    if (!(isnan(n_mean))) {
      for (int32 i=0; i<dimx; i++)
        vv[i]=n_mean+gaussian_random(sqrt(abs(n_variance)));
    }
    if (vv.WriteFile(outfile)) {
      printf("[E] vbsim: error writing 1D file %s\n",outfile.c_str());
      exit(120);
    }
    printf("[I] vbsim: wrote 1D file %s\n",outfile.c_str());
    exit(0);
  }


  // SPECIAL CASE-- cubes if dimt==0
  if (dimt==0) {
    printf("[I] vbsim: creating a %dx%dx%d 3D volume with N(%g,%g)\n",dimx,dimy,dimz,
           n_mean,sqrt(n_variance));
    if (outfile=="")
      outfile="data.cub";
    Cube vol(dimx,dimy,dimz,vb_float);
    if (!(isnan(n_mean)))
      AddGaussian(vol,n_mean,n_variance,n_fwhm,n_fwhm,n_fwhm);
    vol+=anat;
    vol.setVoxSizes(vx,vy,vz,vt);
    if (vol.WriteFile(outfile)) {
      printf("[E] vbsim: error writing 3D volume %s\n",outfile.c_str());
      exit(120);
    }
    printf("[I] vbsim: wrote 3D volume %s\n",outfile.c_str());
    exit(0);
  }

  printf("[I] vbsim: creating a %dx%dx%dx%d 4D volume with N(%g,%g)\n",dimx,dimy,dimz,dimt,
         n_mean,sqrt(n_variance));
  if (outfile=="")
    outfile="data.tes";
  // CREATE FUNCTIONALS (variable images, one per time point)
  mytes.SetVolume(dimx,dimy,dimz,dimt,vb_float);
  for (int i=0; i<dimt; i++) {
    Cube vol(dimx,dimy,dimz,vb_float);
    if (!(isnan(n_mean)))
      AddGaussian(vol,n_mean,n_variance,n_fwhm,n_fwhm,n_fwhm);
    vol+=anat;
    mytes.SetCube(i,vol);
  }
  mytes.setVoxSizes(vx,vy,vz,vt);
  if (mytes.WriteFile(outfile)) {
    printf("[E] vbsim: error writing 4D volume %s\n",outfile.c_str());
    return 120;
  }
  printf("[I] vbsim: wrote 4D volume %s\n",outfile.c_str());
  return 0;
}