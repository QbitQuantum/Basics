void OBB::SetUpValue()
{
  /*   V1      V4  */
  /*   --------    */
  /*   |   .  |    */
  /*   --------    */
  /*   V2      V3  */

  // update mHalfextend
  static Matrix Tran;
  static Matrix InvRot;
  static Matrix InvTran;
  static Vector3 scale;
  mRotation = cphysics->gameObject->transform->GetGlobalRotationMatrix();
  Tran = cphysics->gameObject->transform->mTranslation;
  Tran.m03 += cphysics->GetOffSetX(); 
  Tran.m13 += cphysics->GetOffSetY();
  InvRot = mRotation.Inverted();
  InvTran = Tran.Inverted();
  mWorld = Tran * mRotation;
  mInvWorld = InvRot * InvTran;
  scale = cphysics->gameObject->transform->scale;
  float scalex = cphysics->mWidthScale;
  float scaley = cphysics->mHeightScale;
  mHalfextend[0].x = abs(scale.x) * 0.5f * scalex;
  mHalfextend[1].y = abs(scale.y) * 0.5f * scaley;
  
  // update center
	mCenter	   = cphysics->GetPosition();
  // update axis
  Vector AxisX(1.0f,0,0,0);
  Vector AxisY(0,1.0f,0,0);
  static Vector newAxisX; 
  static Vector newAxisY;
  newAxisX = mRotation * AxisX;
  newAxisY = mRotation * AxisY;
  newAxisX.Normalize();
  newAxisY.Normalize();
  mAxis[0] = newAxisX;
  mAxis[1] = newAxisY;


   // update four points
  float halfX = GetHalfExtendX().x;
  float halfY = GetHalfExtendY().y;

  mPoints[0] = mCenter - mAxis[0] * halfX + mAxis[1] * halfY;
  mPoints[1] = mCenter - mAxis[0] * halfX - mAxis[1] * halfY;
  mPoints[2] = mCenter + mAxis[0] * halfX - mAxis[1] * halfY;
  mPoints[3] = mCenter + mAxis[0] * halfX + mAxis[1] * halfY;
}