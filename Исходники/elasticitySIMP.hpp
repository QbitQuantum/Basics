  void Construct_CBmats(const bool ifInitial) {
    if(ifInitial)
      CBMat0_->initialize(0.0);

     this->CBMat_->initialize(0.0);
     Real SIMPScale;
     for (int i=0; i<this->numCells_; ++i) {
      
      SIMPScale = SIMPmaterial_[i]->getSIMPScaleFactor();
      Teuchos::RCP<Intrepid::FieldContainer<Real> > materialMat = SIMPmaterial_[i]->GetMaterialTensor();
      for (int j=0; j<this->numCubPoints_; ++j) {
        for (int m=0; m<this->lfs_*this->spaceDim_; m++) {
          for (int n=0; n<this->materialTensorDim_; n++) {
            for (int k=0; k<this->materialTensorDim_; k++) {
              if(ifInitial)
                (*CBMat0_)(i, m, j, n) += (*this->BMat_)(i, m, j, k) * (*materialMat)(k, n);
              (*this->CBMat_)(i, m, j, n) += SIMPScale * (*this->BMat_)(i, m, j, k) * (*materialMat)(k, n);
            }
          }
        }
      }
    }
  }