 /** \brief Computes and sets the multilevel Shi-Tomasi Score \ref s_, considering a defined pyramid level interval.
  *
  * @param l1 - Start level (l1<l2)
  * @param l2 - End level (l1<l2)
  */
 void computeMultilevelShiTomasiScore(const int l1 = 0, const int l2 = nLevels_-1) const{
   H_.setZero();
   int count = 0;
   for(int i=l1;i<=l2;i++){
     if(isValidPatch_[i]){
       H_ += pow(0.25,i)*patches_[i].getHessian();
       count++;
     }
   }
   if(count > 0){
     const float dXX = H_(0,0)/(count*patchSize*patchSize);
     const float dYY = H_(1,1)/(count*patchSize*patchSize);
     const float dXY = H_(0,1)/(count*patchSize*patchSize);
     e0_ = 0.5 * (dXX + dYY - sqrtf((dXX + dYY) * (dXX + dYY) - 4 * (dXX * dYY - dXY * dXY)));
     e1_ = 0.5 * (dXX + dYY + sqrtf((dXX + dYY) * (dXX + dYY) - 4 * (dXX * dYY - dXY * dXY)));
     s_ = e0_;
   } else {
     e0_ = 0;
     e1_ = 0;
     s_ = -1;
   }
 }