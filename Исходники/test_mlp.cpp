  MLPTesting(): c_(&camera_){
    static_assert(imgSize_*dx_*dy_<255,"imgSize to large for gradients");
    pixel_ = cv::Point2f(patchSize_/2+1,patchSize_/2+1);
    bearing_ = V3D(patchSize_/2+1,patchSize_/2+1,1);
    bearing_.normalize();
    c_.set_c(pixel_);
    warp_c_ << 0.1, 0.5, 0.7, -0.2;
    c_.set_warp_c(warp_c_);
    warp_nor_ = c_.get_warp_nor();

    stat_.localQualityRange_ = 3;
    stat_.localVisibilityRange_ = 4;
    stat_.minGlobalQualityRange_ = 5;

    img1_ = cv::Mat::zeros(imgSize_,imgSize_,CV_8UC1);
    uint8_t* img_ptr = (uint8_t*) img1_.data;
    for(int i=0;i<imgSize_;i++){
      for(int j=0;j<imgSize_;j++, ++img_ptr){
        *img_ptr = i*dy_+j*dx_;
      }
    }
    img2_ = cv::Mat::zeros(imgSize_,imgSize_,CV_8UC1);
    img_ptr = (uint8_t*) img2_.data;
    for(int i=0;i<imgSize_;i++){
      for(int j=0;j<imgSize_;j++, ++img_ptr){
        if(j<imgSize_/2 & i<imgSize_/2){
          *img_ptr = 0;
        } else {
          *img_ptr = 255;
        }
      }
    }
    pyr1_.computeFromImage(img1_);
    pyr2_.computeFromImage(img2_);
  }