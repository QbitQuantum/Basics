const VectorXd &AniEditDM::getInputU(const int frame, const bool translate)const{
  
  static VectorXd tempt_u0;
  assert_in (frame, 0, totalFrameNum() );
  if (interpolator != NULL && totalFrameNum() > 0){
	if (!translate){
	  return interpolator->getInputU(frame);
	}else{
	  tempt_u0 = interpolator->getInputU(frame);
	  this->translate(tempt_u0, frame);
	  return tempt_u0;
	}
  }else{
	if (tempt_u0.size() != fullDim()){
	  tempt_u0.resize(fullDim());
	  tempt_u0.setZero();
	}
	return tempt_u0;
  }
}