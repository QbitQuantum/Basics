void
vpSimulator::moveInternalCamera(vpHomogeneousMatrix &cMf)
{

  SbMatrix matrix;
  SbRotation rotCam;
  SbMatrix rotX;
  rotX.setRotate (SbRotation (SbVec3f(1.0f, 0.0f, 0.0f), (float)M_PI));
  for(unsigned int i=0;i<4;i++)
    for(unsigned int j=0;j<4;j++)
      matrix[(int)j][(int)i]=(float)cMf[i][j];

  matrix= matrix.inverse();
  matrix.multLeft (rotX);
  rotCam.setValue(matrix);


  internalCamera->ref() ;
  internalCamera->orientation.setValue(rotCam);
  internalCamera->position.setValue(matrix[3][0],matrix[3][1],matrix[3][2]);
  internalCamera->unref() ;

  rotX.setRotate (SbRotation (SbVec3f(-1.0f, 0.0f, 0.0f), (float)M_PI));
  matrix.multLeft (rotX);
  rotCam.setValue(matrix);
  internalCameraPosition->ref() ;
  internalCameraPosition->rotation.setValue(rotCam);
  internalCameraPosition->translation.setValue(matrix[3][0],matrix[3][1],matrix[3][2]);
  internalCameraPosition->unref() ;
}