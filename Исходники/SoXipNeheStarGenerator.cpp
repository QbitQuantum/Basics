void
SoXipNeheStarGenerator::GLRender(SoGLRenderAction *action)
{
  float yawAngle = 0;
  static float spinAngle = 0;
  float distance = 0;
  float pitchAngle = M_PI /2; // tilt the view
  SbRotation pitch(SbVec3f(1, 0, 0), pitchAngle); // rotation around X
  SbMatrix pitchM;
  pitch.getValue(pitchM);

  SbRotation yaw = SbRotation::identity(); 
  SbMatrix yawM = SbMatrix::identity();
  SbRotation spin = SbRotation::identity(); 
  SbMatrix spinM = SbMatrix::identity();

  for (int i = 0; i < MAX_STARS; i++)
  {
     SoXipNeheStar* star = static_cast<SoXipNeheStar*>(this->getChild(i));

     // spin angle for this star
     spin.setValue(SbVec3f(0,0,1), spinAngle); // rotation around Z
     spin.getValue(spinM);


     // yaw angle for this star
     //_starInfos[i].angle += ((float(i)/MAX_STARS) * (180 / M_PI));
     yawAngle =  _starInfos[i].angle;
     yaw.setValue(SbVec3f(0,1,0), yawAngle); // rotation around Y 
     yaw.getValue(yawM);
     
     
     // let's compose all matrices once to position each star
     SbMatrix transM = SbMatrix::identity();
     transM.setTranslate(SbVec3f(_starInfos[i].distance,0,0));
     SbMatrix transform = spinM * pitchM.inverse() * yawM.inverse() * transM * yawM * pitchM ;

     // position the star
     star->trans.setValue(transform);
     unsigned int color = convertRGBtoHex(_starInfos[i].r, _starInfos[i].g, _starInfos[i].b);
     star->color.set1Value(0, color);
     star->color.set1Value(1, color);
     star->color.set1Value(2, color);
     star->color.set1Value(3, color);
         
     spinAngle += ( 0.01f * (M_PI / 180));
      
     
     // change setting of all stars except the very first one (index 0)
     if (i)
     {
         _starInfos[i].angle += ((float(i)/MAX_STARS) * ( M_PI / 180));
         _starInfos[i].distance -= 0.01f;
         if (_starInfos[i].distance < 0.0f)
         {
           _starInfos[i].distance += 5.0f;
           _starInfos[i].r= rand() % 255 + 1 ;
           _starInfos[i].g= rand() % 255 + 1;
           _starInfos[i].b= rand() % 255 + 1;
         }
     }
  }

  SoXipKit::GLRender(action);
  
}