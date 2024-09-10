void seissol::model::getFaceRotationMatrix( VrtxCoords const i_normal,
                                            VrtxCoords const i_tangent1,
                                            VrtxCoords const i_tangent2,
                                            DenseMatrixView<NUMBER_OF_QUANTITIES, NUMBER_OF_QUANTITIES> o_T,
                                            DenseMatrixView<NUMBER_OF_QUANTITIES, NUMBER_OF_QUANTITIES> o_Tinv )
{
  o_T.setZero();
  o_Tinv.setZero();
  
  seissol::transformations::symmetricTensor2RotationMatrix(i_normal, i_tangent1, i_tangent2, o_T.block<6,6>(0, 0));
  seissol::transformations::inverseSymmetricTensor2RotationMatrix(i_normal, i_tangent1, i_tangent2, o_Tinv.block<6,6>(0, 0));
  
  seissol::transformations::tensor1RotationMatrix(i_normal, i_tangent1, i_tangent2, o_T.block<3,3>(6, 6));
  seissol::transformations::inverseTensor1RotationMatrix(i_normal, i_tangent1, i_tangent2, o_Tinv.block<3,3>(6, 6));
  
  for (unsigned mech = 0; mech < NUMBER_OF_RELAXATION_MECHANISMS; ++mech) {
    unsigned origin = 9 + mech * 6;
    seissol::transformations::symmetricTensor2RotationMatrix(i_normal, i_tangent1, i_tangent2, o_T.block<6,6>(origin, origin));
    seissol::transformations::inverseSymmetricTensor2RotationMatrix(i_normal, i_tangent1, i_tangent2, o_Tinv.block<6,6>(origin, origin));
  }
}