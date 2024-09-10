  void jacTransform(MXD& J, const mtInput& input) const{
    J.setZero();
    const int& camID = input.CfP(ID_).camID_;
    if(camID != outputCamID_){
      input.updateMultiCameraExtrinsics(mpMultiCamera_);
      const QPD qDC = input.qCM(outputCamID_)*input.qCM(camID).inverted(); // TODO: avoid double computation
      const V3D CrCD = input.qCM(camID).rotate(V3D(input.MrMC(outputCamID_)-input.MrMC(camID)));
      const V3D CrCP = input.dep(ID_).getDistance()*input.CfP(ID_).get_nor().getVec();
      const V3D DrDP = qDC.rotate(V3D(CrCP-CrCD));
      const double d_out = DrDP.norm();
      const LWF::NormalVectorElement nor_out(DrDP); // TODO: test if Jacobian works, this new setting of vector is dangerous

      const Eigen::Matrix<double,1,3> J_d_DrDP = nor_out.getVec().transpose();
      const Eigen::Matrix<double,2,3> J_nor_DrDP = nor_out.getM().transpose()/d_out;
      const Eigen::Matrix<double,3,3> J_DrDP_qDC = gSM(DrDP);
      const Eigen::Matrix<double,3,3> J_DrDP_CrCP = MPD(qDC).matrix();
      const Eigen::Matrix<double,3,3> J_DrDP_CrCD = -MPD(qDC).matrix();

      const Eigen::Matrix<double,3,3> J_qDC_qDB = Eigen::Matrix3d::Identity();
      const Eigen::Matrix<double,3,3> J_qDC_qCB = -MPD(qDC).matrix();
      const Eigen::Matrix<double,3,3> J_CrCD_qCB = gSM(CrCD);
      const Eigen::Matrix<double,3,3> J_CrCD_BrBC = -MPD(input.qCM(camID)).matrix();
      const Eigen::Matrix<double,3,3> J_CrCD_BrBD = MPD(input.qCM(camID)).matrix();

      const Eigen::Matrix<double,3,1> J_CrCP_d = input.CfP(ID_).get_nor().getVec()*input.dep(ID_).getDistanceDerivative();
      const Eigen::Matrix<double,3,2> J_CrCP_nor = input.dep(ID_).getDistance()*input.CfP(ID_).get_nor().getM();

      J.template block<2,2>(mtOutput::template getId<mtOutput::_fea>(),mtInput::template getId<mtInput::_fea>(ID_)) = J_nor_DrDP*J_DrDP_CrCP*J_CrCP_nor;
      J.template block<2,1>(mtOutput::template getId<mtOutput::_fea>(),mtInput::template getId<mtInput::_fea>(ID_)+2) = J_nor_DrDP*J_DrDP_CrCP*J_CrCP_d;
      if(!ignoreDistanceOutput_){
        J.template block<1,2>(mtOutput::template getId<mtOutput::_fea>()+2,mtInput::template getId<mtInput::_fea>(ID_)) = J_d_DrDP*J_DrDP_CrCP*J_CrCP_nor;
        J.template block<1,1>(mtOutput::template getId<mtOutput::_fea>()+2,mtInput::template getId<mtInput::_fea>(ID_)+2) = J_d_DrDP*J_DrDP_CrCP*J_CrCP_d;
      }

      if(input.aux().doVECalibration_ && camID != outputCamID_){
        J.template block<2,3>(mtOutput::template getId<mtOutput::_fea>(),mtInput::template getId<mtInput::_vea>(camID)) = J_nor_DrDP*(J_DrDP_qDC*J_qDC_qCB+J_DrDP_CrCD*J_CrCD_qCB);
        J.template block<2,3>(mtOutput::template getId<mtOutput::_fea>(),mtInput::template getId<mtInput::_vea>(outputCamID_)) = J_nor_DrDP*J_DrDP_qDC*J_qDC_qDB;
        J.template block<2,3>(mtOutput::template getId<mtOutput::_fea>(),mtInput::template getId<mtInput::_vep>(camID)) = J_nor_DrDP*J_DrDP_CrCD*J_CrCD_BrBC;
        J.template block<2,3>(mtOutput::template getId<mtOutput::_fea>(),mtInput::template getId<mtInput::_vep>(outputCamID_)) = J_nor_DrDP*J_DrDP_CrCD*J_CrCD_BrBD;
        if(!ignoreDistanceOutput_){
          J.template block<1,3>(mtOutput::template getId<mtOutput::_fea>()+2,mtInput::template getId<mtInput::_vea>(camID)) = J_d_DrDP*(J_DrDP_qDC*J_qDC_qCB+J_DrDP_CrCD*J_CrCD_qCB);
          J.template block<1,3>(mtOutput::template getId<mtOutput::_fea>()+2,mtInput::template getId<mtInput::_vea>(outputCamID_)) = J_d_DrDP*J_DrDP_qDC*J_qDC_qDB;
          J.template block<1,3>(mtOutput::template getId<mtOutput::_fea>()+2,mtInput::template getId<mtInput::_vep>(camID)) = J_d_DrDP*J_DrDP_CrCD*J_CrCD_BrBC;
          J.template block<1,3>(mtOutput::template getId<mtOutput::_fea>()+2,mtInput::template getId<mtInput::_vep>(outputCamID_)) = J_d_DrDP*J_DrDP_CrCD*J_CrCD_BrBD;
        }
      }
    } else {
      J.template block<2,2>(mtOutput::template getId<mtOutput::_fea>(),mtInput::template getId<mtInput::_fea>(ID_)) = Eigen::Matrix2d::Identity();
      J.template block<1,1>(mtOutput::template getId<mtOutput::_fea>()+2,mtInput::template getId<mtInput::_fea>(ID_)+2) = Eigen::Matrix<double,1,1>::Identity();
    }
  }