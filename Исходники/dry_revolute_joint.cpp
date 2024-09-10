void dry_revolute_joint_2D::doForce(kte_pass_flag aFlag, const shared_ptr<frame_storage>& aStorage) {
  if((!mEnd) || (!mBase))
    return;
  
  using std::fabs;
  
  if(!mAngle) {
    mBase->Force += mEnd->Force;
    mBase->Torque += mEnd->Torque;
  } else {
    vect<double,2> tmp_f = rot_mat_2D<double>(mAngle->q) * mEnd->Force;
    mBase->Force += tmp_f;
    if(fabs(mAngle->q_dot) > mSlipVelocity) 
      mAngle->f += mEnd->Torque - mAngle->q_dot / fabs(mAngle->q_dot) * mSlipCoef * norm_2(tmp_f);
    else {
      mAngle->f += mEnd->Torque - mAngle->q_dot / mSlipVelocity * mStictionCoef * norm_2(tmp_f);
    };
  };
  
  if((aFlag == store_dynamics) && (aStorage)) {
    if(aStorage->frame_2D_mapping[mEnd]) {
      aStorage->frame_2D_mapping[mEnd]->Force = mEnd->Force;
      aStorage->frame_2D_mapping[mEnd]->Torque = mEnd->Torque;
    };
  };  
};