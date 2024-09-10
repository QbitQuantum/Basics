     /**
      * p = R*x + T
      * if inverse:
      *  x = R^1*(p - T)
      */
 inline Eigen::Affine3f
 RT2Transform(cv::Mat& R, cv::Mat& T, bool inverse)
 {
   //convert the tranform from our fiducial markers to
   //the Eigen
   Eigen::Matrix<float, 3, 3> eR;
   Eigen::Vector3f eT;
   cv::cv2eigen(R, eR);
   cv::cv2eigen(T, eT);
   // p = R*x + T
   Eigen::Affine3f transform;
   if (inverse)
   {
     //x = R^1*(p - T)
     transform = Eigen::Translation3f(-eT);
     transform.prerotate(eR.transpose());
   }
   else
   {
     //p = R*x + T
     transform = Eigen::AngleAxisf(eR);
     transform.translate(eT);
   }
   return transform;
 }