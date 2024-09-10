//\fn void ExtrinsicParam::changePanTilt(double pan, double tilt);
///\brief This function computes the new rotation matrix and the new translation vector of the extrinsic parameters when the camera has changed its position.
///\param pan Value of the new camera panoramique.
///\param tilt Value of the new camera tilt.
void ExtrinsicParam::changePanTilt(double pan, double tilt)
{
  // Compute the rotation matrices with the new values of pan and tilt
  Eigen::Matrix3d Rx, Ry;
  Rx.setZero();
  Ry.setZero();
  Rx(0,0) = 1;
  Rx(1,1) = cos((-(tilt-this->tilt))*PI/180.);
  Rx(1,2) = -sin((-(tilt-this->tilt))*PI/180.);
  Rx(2,1) = sin((-(tilt-this->tilt))*PI/180.);
  Rx(2,2) = cos((-(tilt-this->tilt))*PI/180.);
  Ry(0,0) = cos((-(pan-this->pan))*PI/180.);
  Ry(0,2) = sin((-(pan-this->pan))*PI/180.);
  Ry(1,1) = 1;
  Ry(2,0) = -sin((-(pan-this->pan))*PI/180.);
  Ry(2,2) = cos((-(pan-this->pan))*PI/180.);

  Eigen::Vector3d Tx, Ty;
  Tx.setZero();
  Ty.setZero();
  Tx(0) = 2*3.3*sin(0.5*(this->pan-pan)*PI/180.)*cos(0.5*(this->pan-pan)*PI/180.);
  Tx(2) = -2*3.3*sin(0.5*(this->pan-pan)*PI/180.)*cos((90.-0.5*(this->pan-pan))*PI/180.);
  Ty(1) = 2*3.3*sin(0.5*(this->tilt-tilt)*PI/180.)*cos(0.5*(this->tilt-tilt)*PI/180.);
  Ty(2) = -2*3.3*sin(0.5*(this->tilt-tilt)*PI/180.)*cos((90.-0.5*(this->tilt-tilt))*PI/180.);

  // Compute the new values of the extrinsic parameters
  Eigen::Matrix4d Rx1, Ry1, Rt;
  Rt << initial_rotation, initial_translation,
    0,0,0,1;
  Rx1 << Rx, Tx,
    0,0,0,1;
  Ry1 << Ry, Ty,
    0,0,0,1;
  Rt.noalias() = Rx1*Ry1*Rt;
  rotation(0,0) = Rt(0,0);rotation(0,1) = Rt(0,1);rotation(0,2) = Rt(0,2);
  rotation(1,0) = Rt(1,0);rotation(1,1) = Rt(1,1);rotation(1,2) = Rt(1,2);
  rotation(2,0) = Rt(2,0);rotation(2,1) = Rt(2,1);rotation(2,2) = Rt(2,2);
  translation(0) = Rt(0,3);
  translation(1) = Rt(1,3);
  translation(2) = Rt(2,3);
}