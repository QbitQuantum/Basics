//---------------------
int fdct_wrapping_invsepangle(double XL1, double XL2, int nbangle, vector<CpxNumMat>& csc, CpxOffMat& Xhgh)
{
  typedef pair<int,int> intpair;
  map<intpair, fftwnd_plan> planmap;
  
  int XS1, XS2;  int XF1, XF2;  double XR1, XR2;	 fdct_wrapping_rangecompute(XL1, XL2, XS1, XS2, XF1, XF2, XR1, XR2);
  Xhgh.resize(XS1, XS2);
  
  int nbquadrants = 4;
  int nd = nbangle / 4;
  int wcnt = 0;
  
  //backup
  CpxOffMat Xhghb(Xhgh);
  double XL1b = XL1;  double XL2b = XL2;

  int qvec[] = {2,1,0,3};
  for(int qi=0; qi<nbquadrants; qi++) {
	 int q = qvec[qi];
	 //ROTATE data to its right position
	 fdct_wrapping_rotate_forward(q, XL1b, XL2b, XL1, XL2);	 XL1 = abs(XL1);	 XL2 = abs(XL2);
	 fdct_wrapping_rotate_forward(q, Xhghb, Xhgh);
	 //figure out XS, XF, XR
	 double XW1 = XL1/nd;	 double XW2 = XL2/nd;
	 int XS1, XS2;  int XF1, XF2;  double XR1, XR2;  fdct_wrapping_rangecompute(XL1, XL2, XS1, XS2, XF1, XF2, XR1, XR2);
	 for(int w=nd-1; w>=0; w--) {
		double xs = XR1/4 - (XW1/2)/4;
		double xe = XR1;
		double ys = -XR2 + (w-0.5)*XW2;
		double ye = -XR2 + (w+1.5)*XW2; //x range
		int xn = int(ceil(xe-xs));			 int yn = int(ceil(ye-ys));
		//MAKE THEM ODD
		if(xn%2==0) xn++;		if(yn%2==0) yn++;
		int xf = int(ceil(xs));			 //int yf = int(ceil(ys));
		//theta
		double thts, thtm, thte; //y direction
		if(w==0) {
		  thts = atan2(-1.0, 1.0-1.0/nd);
		  thtm = atan2(-1.0+1.0/nd, 1.0);
		  thte = atan2(-1.0+3.0/nd, 1.0);
		} else if(w==nd-1) {
		  thts = atan2(-1.0+(2.0*w-1.0)/nd, 1.0);
		  thtm = atan2(-1.0+(2.0*w+1.0)/nd, 1.0);
		  thte = atan2(1.0, 1.0-1.0/nd);
		} else {
		  thts = atan2(-1.0+(2.0*w-1.0)/nd, 1.0);
		  thtm = atan2(-1.0+(2.0*w+1.0)/nd, 1.0);
		  thte = atan2(-1.0+(2.0*w+3.0)/nd, 1.0);
		}
		int xh = xn/2;		int yh = yn/2; //half length
		CpxOffMat wpdata(xn,yn);

		{
		  //load
		  int xn = csc[wcnt].m();		  int yn = csc[wcnt].n();
		  CpxNumMat tpdata(csc[wcnt]);
		  //fft
		  fftwnd_plan p = NULL;
		  map<intpair, fftwnd_plan>::iterator mit=planmap.find( intpair(xn,yn) );
		  if(mit!=planmap.end()) {
			 p = (*mit).second;
		  } else {
			 p = fftw2d_create_plan(yn, xn, FFTW_FORWARD, FFTW_ESTIMATE | FFTW_IN_PLACE);
			 planmap[ intpair(xn, yn) ] = p;
		  }
		  fftwnd_one(p, (fftw_complex*)tpdata.data(), NULL);
		  double sqrtprod = sqrt(double(xn*yn));
		  for(int i=0; i<xn; i++)		  for(int j=0; j<yn; j++)			 tpdata(i,j) /= sqrtprod;
		  //fftshift
		  CpxOffMat rpdata;
		  fdct_wrapping_fftshift(tpdata,rpdata);
		  //rotate forward
		  fdct_wrapping_rotate_forward(q, rpdata, wpdata);
		}
		
		double R21 = XR2/XR1; //ratio
		for(int xcur=xf; xcur<xe; xcur++) { //for each layer
		  int yfm = (int)ceil( max(-XR2, R21*xcur*tan(thts)) );
		  int yto = (int)floor( min(XR2, R21*xcur*tan(thte)) );
		  for(int ycur=yfm; ycur<=yto; ycur++) {
			 int tmpx = xcur%xn;				  if(tmpx<-xh) tmpx+=xn;				  if(tmpx>=-xh+xn) tmpx-=xn;
			 int tmpy = ycur%yn;				  if(tmpy<-yh) tmpy+=yn;				  if(tmpy>=-yh+yn) tmpy-=yn;
			 //partition of unity
			 double thtcur = atan2(ycur/XR2, xcur/XR1);
			 double wtht;
			 if(thtcur<thtm) {
				double l,r; fdct_wrapping_window((thtcur-thts)/(thtm-thts), l, r);
				wtht = l;
			 } else {
				double l,r; fdct_wrapping_window((thtcur-thtm)/(thte-thtm), l, r);
				wtht = r;
			 }
			 double pou = wtht;
			 wpdata(tmpx,tmpy) *= pou;
			 Xhgh(xcur,ycur) += wpdata(tmpx,tmpy);
		  }
		}
		
		wcnt++;
	 }//w loop
	 fdct_wrapping_rotate_backward(q, Xhgh, Xhghb);
  } //q loop
  Xhgh = Xhghb;
  XL1 = XL1b;  XL2 = XL2b;

  assert(wcnt==nbangle);
  
  for(map<intpair, fftwnd_plan>::iterator mit=planmap.begin(); mit!=planmap.end(); mit++) {
	 fftwnd_plan p = (*mit).second;
	 fftwnd_destroy_plan(p);
  }
  return 0;
}