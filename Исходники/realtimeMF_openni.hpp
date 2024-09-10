void RealtimeMF_openni::normals_cb(float* d_normals, uint8_t* haveData,
    uint32_t w, uint32_t h)
{
  tLog_.tic(-1); // reset all timers
  int32_t nComp = 0;
  float* d_nComp = this->normalExtract->d_normalsComp(nComp);
  Matrix3f kRwBefore = kRw_;
  tLog_.toctic(0,1);

  optSO3_->updateExternalGpuNormals(d_nComp,nComp,3,0);
  double residual = optSO3_->conjugateGradientCUDA(kRw_,nCGIter_);
  double D_KL = optSO3_->D_KL_axisUnif();
  tLog_.toctic(1,2);

  {
    boost::mutex::scoped_lock updateLock(this->updateModelMutex);
    this->normalsImg_ = this->normalExtract->normalsImg();
    if(z_.rows() != w*h) z_.resize(w*h);
    this->normalExtract->uncompressCpu(optSO3_->z().data(), optSO3_->z().rows(),
        z_.data(), z_.rows());

    mfAxes_ = MatrixXf::Zero(3,6);
    for(uint32_t k=0; k<6; ++k){
      int j = k/2; // which of the rotation columns does this belong to
      float sign = (- float(k%2) +0.5f)*2.0f; // sign of the axis
      mfAxes_.col(k) = sign*kRw_.col(j);
    }
    D_KL_= D_KL;
    residual_ = residual;
    this->update_ = true;
    updateLock.unlock();
  }

  tLog_.toc(2); // total time
  tLog_.logCycle();
  cout<<"delta rotation kRw_ = \n"<<kRwBefore*kRw_.transpose()<<endl;
  cout<<"---------------------------------------------------------------------------"<<endl;
  tLog_.printStats();
  cout<<" residual="<<residual_<<"\t D_KL="<<D_KL_<<endl;
  cout<<"---------------------------------------------------------------------------"<<endl;
  fout_<<D_KL_<<" "<<residual_<<endl; fout_.flush();

////  return kRw_;
//  {
//    boost::mutex::scoped_lock updateLock(this->updateModelMutex);
////    pcl::PointCloud<pcl::PointXYZRGB>::ConstPtr nDispPtr =
////      normalExtract->normalsPc();
////    nDisp_ = pcl::PointCloud<pcl::PointXYZRGB>::Ptr( new
////        pcl::PointCloud<pcl::PointXYZRGB>(*nDispPtr));
////    this->normalsImg_ = this->normalExtract->normalsImg();
//    this->update_ = true;
//  }
};