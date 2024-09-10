int main(int argc, char* argv[])
{
  /*define variables*/
  int nx,nx1,nt;
  int n1,n2;
  float d1,o1,d2,o2;
  int padt,padx;
  int ntfft,*n,nw,nk;
  float **d,*wavelet,**shot,**ds,**vel,**vmig,**M,v_ave;
  float *kx,*omega,dkx,dw;
  sf_complex **m,**ms,**mr,*in2a,*in2b,*cs,*cr,*c,czero;
  sf_complex Ls;
  float fmin,fmax,f_low,f_high;
  int if_low,if_high;
  int ix,iw,ik;
  float dt,dx,ox,dz,zmax;
  fftwf_plan p2a,p2b;
  sf_file in,out,velfile,source_wavelet;
  int iz,nz;
  int ishot,max_num_shot,ig,ng,it,index;
  int iswavelet;
  /*define sf input output*/
  sf_init (argc,argv);
  in = sf_input("in");
  out = sf_output("out");
  velfile = sf_input("velfile");
  if (!sf_histint(in,"n1",&n1)) sf_error("No n1= in input");
  if (!sf_histfloat(in,"d1",&d1)) sf_error("No d1= in input");
  if (!sf_histfloat(in,"o1",&o1)) o1=0.;
  if (!sf_histint(in,"n2",&n2)) sf_error("No n2= in vel");
  if (!sf_histfloat(in,"d2",&d2)) sf_error("No d2= in input");
  if (!sf_histfloat(in,"o2",&o2)) o2=0.;

  dt = d1;
  dx = d2;
  ox = o2;
  nx1 = n2;
  nt = n1;
  if (!sf_histint(velfile,"n1",&nz)) sf_error("No n1= in vel");
  if (!sf_histfloat(velfile,"d1",&dz)) sf_error("No n1= in vel");
  if (!sf_histint(velfile,"n2",&n2)) sf_error("No n2= in vel");	
   if (!sf_getint("iswavelet",&iswavelet)) iswavelet = 0;
  source_wavelet=sf_input("source_wavelet");

  max_num_shot=100;
  ng=700;
  nx=n2;
  padt = 2;
  padx = 2;
  ntfft = padt*nt;
  nw=ntfft/2+1;
  nk = padx*nx;
  dw = 2*PI/ntfft/dt;
  dkx = 2*PI/nk/dx;

  sf_putint(out,"n1",nz);
  sf_putint(out,"n2",nx);
  sf_putfloat(out,"d1",dz);
  sf_putstring(out,"label1","z");
  sf_putstring(out,"unit1","m");
  sf_putstring(out,"title","migrated");

  if (!sf_getfloat("fmax",&fmax)) fmax = 0.5/d1; /* max frequency to process */
  if (fmax > 0.5/d1) fmax = 0.5/d1;
  if (!sf_getfloat("fmin",&fmin)) fmin = 0.1; /* min frequency to process */
  if (!sf_getfloat("Zmax",&zmax)) zmax = (nz-1)*dz; /* max Depth to migrate */

  
  /*define axis variables*/
 
  dkx=(float) 2*PI/nk/dx;
  dw=(float) 2*PI/ntfft/dt;
  /*allocate memory to dynamic arrays*/
  d = sf_floatalloc2(nt,nx1);
  shot=sf_floatalloc2(nt,ng);
  ds=sf_floatalloc2(nt,nx);
  vel = sf_floatalloc2(nz,nx);
  wavelet=sf_floatalloc(nt);
  vmig = sf_floatalloc2(nz,nx);
  m = sf_complexalloc2(nw,nx);
  ms = sf_complexalloc2(nw,nx);
  mr = sf_complexalloc2(nw,nx);
  kx= sf_floatalloc (nk);
  omega= sf_floatalloc (nw);
  in2a = sf_complexalloc(nk);
  in2b = sf_complexalloc(nk);
  n = sf_intalloc(1);
  M= sf_floatalloc2(nz,nx);
  c = sf_complexalloc(nx);
  cs = sf_complexalloc(nx);
  cr = sf_complexalloc(nx);
  /*read input files*/ 
  sf_floatread(d[0],nx1*nt,in);
  sf_floatread(vel[0],nx*nz,velfile);
/* If there is no wavelet use delta as default
If there is a wavelet use it*/
   if (iswavelet==0) {
	for (it=0; it<nt; it++) wavelet[it] = 0.0;
	wavelet[0]=1;
 	 }

   if (iswavelet==1) sf_floatread(wavelet,nt,source_wavelet);

  /* This part is important: we need to define the horizontal wavenumber and frequency axes right.*/

dw = 2*PI/ntfft/dt;

 dkx = 2*PI/nk/dx;

for (iw=0;iw<nw;iw++){

    omega[iw] = dw*iw;

}
for (ik=0;ik<nk;ik++){ 

  if (ik<nk/2) kx[ik] = dkx*ik;

  else         kx[ik] = -(dkx*nk - dkx*ik);

}

  /* Define minimum and maximum frequency index to process*/   
  
  f_low = fmin;   /* min frequency to process */
  f_high = fmax;  /* max frequency to process */
  
  if(f_low>0){
  	if_low = trunc(f_low*dt*ntfft);
  }	
  else{ 
  	if_low = 0;
  }
  if(f_high*dt*ntfft+1<nw){
  	if_high = trunc(f_high*dt*ntfft)+1;
  }
  else{
 	 if_high = nw;
  }
  
  
  __real__ czero = 0;
  __imag__ czero = 0;
  n[0] = nk;
  p2a = fftwf_plan_dft(1, n, (fftwf_complex*)in2a, (fftwf_complex*)in2a, FFTW_FORWARD, FFTW_ESTIMATE);
  p2b = fftwf_plan_dft(1, n, (fftwf_complex*)in2b, (fftwf_complex*)in2b, FFTW_BACKWARD, FFTW_ESTIMATE);

fftwf_execute(p2a); /* FFT x to k */
fftwf_execute(p2b); /* FFT x to k */

  /* Define initial migrated model and source field as zeros*/
 
  for (iz=0; iz<nz; iz++) {	
    for (ix=0; ix<nx; ix++) M[ix][iz] = 0.0;
  }

   for (it=0; it<nt; it++) {	
    for (ix=0; ix<nx; ix++) ds[ix][it] = 0.0;
  }

  for (iz=0; iz<nz;iz++){
    for (ix=0;ix<nx;ix++) vmig[ix][iz]=vel[ix][iz];
    }
  
  /* loop over shots*/
for (ishot=0;ishot<max_num_shot;ishot++){
	for (ig=0;ig<ng;ig++){
		for (it=0; it<nt; it++)
		shot[ig][it]=d[ishot*ng+ig][it];
	}
	 for (it=0; it<nt; it++) {	
    		for (ix=0; ix<nx; ix++) ds[ix][it] = 0.0;
 	 }
	index=ishot*nx/max_num_shot;
	for (it=0; it<nt; it++) ds[index][it]=wavelet[it];
/* apply fourier transform in time direction t-x ---> w-x*/
  my_forward_fft(ms,mr,shot,ds,nt,dt,nx,padt);

  for (iw=if_low;iw<if_high;iw++){
     for (iz=0; iz<nz;iz++){
		v_ave=vmig[0][iz];	
	        my_v_ave (v_ave,vmig,iz,nx);
/*Apply phase shift to source side*/
	        my_phase_shift(ms,czero,iw,iz,omega,kx,nk,nx,v_ave,in2a,in2b,p2a,p2b,dz,0);
			for (ix=0;ix<nx;ix++) {
					cs[ix]= in2b[ix];
					}
/*Apply phase shift to receiver side*/
		 my_phase_shift(mr,czero,iw,iz,omega,kx,nk,nx,v_ave,in2a,in2b,p2a,p2b,dz,1);
			for (ix=0;ix<nx;ix++) {
					cr[ix]= in2b[ix];
					}
/*Apply split step correction to source and receiver side wavefields*/
         	my_split_step_correction (ms,cs,vmig,v_ave,iz,dz,iw,dw,nx,0);
		my_split_step_correction (mr,cr,vmig,v_ave,iz,dz,iw,dw,nx,1);
	/* Apply cross corrolation as an imaging condition*/
		for (ix=0;ix<nx;ix++){
		__real__ Ls=crealf(ms[ix][iw]);
		__imag__ Ls=- cimagf(ms[ix][iw]);
		m[ix][iw]=mr[ix][iw]*Ls;
		}
   			/* Update migrated model by stacking*/	
		for (ix=0;ix<nx;ix++) M[ix][iz]=M[ix][iz]+2*crealf(m[ix][iw]);
      }
   }
fprintf(stderr,"\r progress = %6.2f%%",(float) 100*(ishot)/(max_num_shot));
  }


  sf_floatwrite(M[0],nz*nx,out);

  
  fftwf_destroy_plan(p2a);
  fftwf_free(in2a); 
  fftwf_destroy_plan(p2b);
  fftwf_free(in2b);	
  
  exit (0);
}