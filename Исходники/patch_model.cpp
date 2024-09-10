//==============================================================================
void 
patch_model::
train(const vector<Mat> &images,
      const Size psize,
      const float var,
      const float lambda,
      const float mu_init,
      const int nsamples,
      const bool visi)
{
  int N = images.size(),n = psize.width*psize.height;

  //compute desired response map
  Size wsize = images[0].size();
  if((wsize.width < psize.width) || (wsize.height < psize.height)){
    cerr << "Invalid image size < patch size!" << endl; throw std::exception();
  }
  int dx = wsize.width-psize.width,dy = wsize.height-psize.height;
  Mat F(dy,dx,CV_32F);
  for(int y = 0; y < dy; y++){   float vy = (dy-1)/2 - y;
    for(int x = 0; x < dx; x++){ float vx = (dx-1)/2 - x;
      F.fl(y,x) = exp(-0.5*(vx*vx+vy*vy)/var);
    }
  }
  normalize(F,F,0,1,NORM_MINMAX);

  //allocate memory
  Mat I(wsize.height,wsize.width,CV_32F);
  Mat dP(psize.height,psize.width,CV_32F);
  Mat O = Mat::ones(psize.height,psize.width,CV_32F)/n;
  P = Mat::zeros(psize.height,psize.width,CV_32F);

  //optimise using stochastic gradient descent
  RNG rn(getTickCount()); double mu=mu_init,step=pow(1e-8/mu_init,1.0/nsamples);
  for(int sample = 0; sample < nsamples; sample++){ int i = rn.uniform(0,N);
    I = this->convert_image(images[i]); dP = 0.0;
    for(int y = 0; y < dy; y++){
      for(int x = 0; x < dx; x++){
    Mat Wi = I(Rect(x,y,psize.width,psize.height)).clone();
    Wi -= Wi.dot(O); normalize(Wi,Wi);
    dP += (F.fl(y,x) - P.dot(Wi))*Wi;
      }
    }    
    P += mu*(dP - lambda*P); mu *= step;
    if(visi){
      Mat R; matchTemplate(I,P,R,CV_TM_CCOEFF_NORMED);
      Mat PP; normalize(P,PP,0,1,NORM_MINMAX);
      normalize(dP,dP,0,1,NORM_MINMAX);
      normalize(R,R,0,1,NORM_MINMAX);
      imshow("P",PP); imshow("dP",dP); imshow("R",R); 
      if(waitKey(10) == 27)break;
    }
  }return;
}