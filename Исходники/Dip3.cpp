/*
src:    input image
kernel:  filter kernel
return:  convolution result
*/
Mat Dip3::spatialConvolution(Mat& src, Mat& kernel){

   auto forEachMat = [](Mat img, int xstep, int ystep, function<Mat (Mat orig, Mat copy, int x, int y)> func) -> Mat {
      
      Mat copy = img.clone();

      for (int x = 0; x < img.cols; x+=xstep) {
         for (int y = 0; y < img.rows; y+=ystep) {
            func(img, copy, x, y);
         }
      }

      return copy;
   };
  
  auto convolution = [kernel](Mat orig, Mat copy, int x, int y) -> Mat {

    Mat defaultMat = Mat::ones(kernel.rows, kernel.cols, CV_32FC1);

    int center = kernel.rows/2;

    // border handling using default values
    for (int i = 0; i < kernel.rows; i++) for (int j = 0; j < kernel.cols; j++) {
     
     if ((x + i) >= center && (x + i) < (orig.rows + center) &&
         (y + j) >= center && (y + j) < (orig.cols + center)) {
       defaultMat.at<float>(i, j) = orig.at<float>(x + i - center, y + j - center);
     }
    
    }

    Mat flippedKernel;
    flip(kernel, flippedKernel, -1);

    float result = sum(defaultMat.dot(flippedKernel)).val[0];

    copy.at<float>(x, y) = result;

    return copy;

  };
  
  Mat copy = src.clone();

  Mat result = forEachMat(copy, 1, 1, convolution);

  return result;

}