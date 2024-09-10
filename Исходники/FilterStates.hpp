 /** \brief Constructor
  */
 FilterState():fsm_(nullptr), transformFeatureOutputCT_(nullptr), featureOutputCov_((int)(FeatureOutput::D_),(int)(FeatureOutput::D_)){
   usePredictionMerge_ = true;
   imgTime_ = 0.0;
   imageCounter_ = 0;
   groundtruth_qCJ_.setIdentity();
   groundtruth_JrJC_.setZero();
   groundtruth_qJI_.setIdentity();
   groundtruth_IrIJ_.setZero();
   groundtruth_qCB_.setIdentity();
   groundtruth_BrBC_.setZero();
   plotGroundtruth_ = true;
   state_.initFeatureManagers(fsm_);
   fsm_.allocateMissing();
   drawPB_ = 1;
   drawPS_ = mtState::patchSize_*pow(2,mtState::nLevels_-1)+2*drawPB_;
 }