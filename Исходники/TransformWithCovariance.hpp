 const base::Affine3d getTransform() const
 {
     Affine3d trans (this->orientation);
     trans.translation() = this->translation;
     return trans;
 }