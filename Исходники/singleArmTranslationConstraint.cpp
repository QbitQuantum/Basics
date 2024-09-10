void singleArmTranslationConstraint:: constraintUpdate(const Eigen::Matrix<double, 3, 1> &currentTranslation,
						       const Eigen::Matrix<double, 3, 1> &desiredTranslation,
						       const Eigen::Matrix<double, 3, 1> &timeDerivative,
						       const Eigen::Matrix<double, 6, DOF> &gradient
						       ){

  // update function measure
  Eigen::Matrix<double, 3, 1> measure;
  measure.setZero();
  measure = currentTranslation - desiredTranslation;
  


  measureNorm_ = measure.norm();

  // update the constraint gradient
  Eigen::Matrix<double, 3, DOF> tempGradient;
  tempGradient.setZero();
  tempGradient = gradient.block<3,DOF>(0,0);
    
  // set up the gradient
  for(int j = 0; j<dim_; j++){
    for(int i = 0; i<DOF; i++){
      // int k = i + sIndex_;
      modelPointer_->chgCoeff(
			      *constrPArray_[j],
			      *(*jointVVarPArrayPointer_)[i],
			      tempGradient(j, i)
			      // gradient(j, i)
			      );	
    }// finish one constraint
  }// finish all constraints


  Eigen::Matrix<double, 3, 1> rhs;
  rhs.setZero();
  // update the rhs
  for(int j = 0; j<dim_; j++){
    
    rhs(j) =  - gain_*( currentTranslation(j) - desiredTranslation(j) ); 

    constrPArray_[j]->set(GRB_DoubleAttr_RHS, 
			  rhs(j)
			  );

  }

  // std::cout<<"error   X: "<<measure(0)           <<" error   Y: "<<measure(1)           <<" error   Z: "<<measure(2)<<std::endl;
  // std::cout<<"error   norm: "<<measureNorm_<<std::endl;
  // std::cout<<"seperation line:---------------------------- "<<std::endl;

}