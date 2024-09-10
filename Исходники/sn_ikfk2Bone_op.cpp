///////////////////////////////////////////////////////////////
// METHODS
///////////////////////////////////////////////////////////////
// GetIKTransform =============================================
CTransformation GetIKTransform(s_GetIKTransform values, CString outportName)
{
   // prepare all variables
   CTransformation result;
   CVector3 bonePos,rootPos,effPos,upvPos,rootEff, xAxis,yAxis,zAxis, rollAxis;

   rootPos = values.root.GetTranslation();
   effPos = values.eff.GetTranslation();
   upvPos = values.upv.GetTranslation();
   rootEff.Sub(effPos,rootPos);
   rollAxis.Normalize(rootEff);

   CMatrix4 rootMatrix = values.root.GetMatrix4();
   CMatrix4 rootMatrixNeg;
   rootMatrixNeg.Invert(rootMatrix);

   double rootEffDistance = rootEff.GetLength();

   // init the scaling
   double global_scale = values.root.GetScaling().GetX();
   result.SetScaling(values.root.GetScaling());

   // Distance with MaxStretch ---------------------
   double restLength = values.lengthA * values.scaleA + values.lengthB * values.scaleB;
   CVector3 distanceVector;
   distanceVector.MulByMatrix4(effPos, rootMatrixNeg);
   double distance = distanceVector.GetLength();
   double distance2 = distance;
   if (distance > (restLength * (values.maxstretch)))
   {
      distanceVector.NormalizeInPlace();
      distanceVector.ScaleInPlace(restLength * (values.maxstretch) );
      distance = restLength * (values.maxstretch);
   }

   // Adapt Softness value to chain length --------
   values.softness = values.softness * restLength *.1;

   // Stretch and softness ------------------------
   // We use the real distance from root to controler to calculate the softness
   // This way we have softness working even when there is no stretch
   double stretch = max(1, distance / restLength);
   double da = restLength - values.softness;
   if (values.softness > 0 && distance2 > da)
   {
      double newlen = values.softness*(1.0 - exp(-(distance2 -da)/values.softness)) + da;
      stretch = distance / newlen;
   }

   values.lengthA = values.lengthA * stretch * values.scaleA * global_scale;
   values.lengthB = values.lengthB * stretch * values.scaleB * global_scale;

   // Reverse -------------------------------------
   double d = distance / (values.lengthA + values.lengthB);

   double reverse_scale;
   if (values.reverse < 0.5)
      reverse_scale = 1-(values.reverse*2 * (1-d));
   else
      reverse_scale = 1-((1-values.reverse)*2 * (1-d));

   values.lengthA *= reverse_scale;
   values.lengthB *= reverse_scale;

   bool invert = values.reverse > 0.5;

   // Slide ---------------------------------------
   double slide_add;
   if (values.slide < .5)
      slide_add = (values.lengthA * (values.slide * 2)) - (values.lengthA);
   else
      slide_add = (values.lengthB * (values.slide * 2)) - (values.lengthB);

   values.lengthA += slide_add;
   values.lengthB -= slide_add;

   // calculate the angle inside the triangle!
   double angleA = 0;
   double angleB = 0;

   // check if the divider is not null otherwise the result is nan
   // and the output disapear from xsi, that breaks constraints
   if((rootEffDistance < values.lengthA + values.lengthB) && (rootEffDistance > fabs(values.lengthA - values.lengthB) + 1E-6))
   {
      // use the law of cosine for lengthA
      double a = values.lengthA;
      double b = rootEffDistance;
      double c = values.lengthB;

         angleA = acos(min(1, (a * a + b * b - c * c ) / ( 2 * a * b)));

      // use the law of cosine for lengthB
      a = values.lengthB;
      b = values.lengthA;
      c = rootEffDistance;
      angleB = acos(min(1, (a * a + b * b - c * c ) / ( 2 * a * b)));

      // invert the angles if need be
      if(invert)
      {
         angleA = -angleA;
         angleB = -angleB;
      }
   }

   // start with the X and Z axis
   xAxis = rootEff;
   yAxis.LinearlyInterpolate(rootPos,effPos,.5);
   yAxis.Sub(upvPos,yAxis);
   yAxis = rotateVectorAlongAxis(yAxis, rollAxis, values.roll);
   zAxis.Cross(xAxis,yAxis);
   xAxis.NormalizeInPlace();
   zAxis.NormalizeInPlace();

   // switch depending on our mode
   if(outportName == "OutBoneA")  // Bone A
   {
      // check if we need to rotate the bone
      if(angleA != 0.0)
      {
         CRotation rot;
         rot.SetFromAxisAngle(zAxis,angleA);
         xAxis.MulByMatrix3InPlace(rot.GetMatrix());
      }

      if (values.negate)
         xAxis.NegateInPlace();

      // cross the yAxis and normalize
      yAxis.Cross(zAxis,xAxis);
      yAxis.NormalizeInPlace();

      // output the rotation
      result.SetRotationFromXYZAxes(xAxis,yAxis,zAxis);

      // set the scaling + the position
      result.SetSclX(values.lengthA);
      result.SetTranslation(rootPos);
   }
   else if(outportName == "OutBoneB")  // Bone B
   {
      // check if we need to rotate the bone
      if(angleA != 0.0)
      {
         CRotation rot;
         rot.SetFromAxisAngle(zAxis,angleA);
         xAxis.MulByMatrix3InPlace(rot.GetMatrix());
      }

      // calculate the position of the elbow!
      bonePos.Scale(values.lengthA,xAxis);
      bonePos.AddInPlace(rootPos);

      // check if we need to rotate the bone
      if(angleB != 0.0)
      {
         CRotation rot;
         rot.SetFromAxisAngle(zAxis,angleB-XSI::MATH::PI);
         xAxis.MulByMatrix3InPlace(rot.GetMatrix());
      }

      if (values.negate)
         xAxis.NegateInPlace();

      // cross the yAxis and normalize
      yAxis.Cross(zAxis,xAxis);
      yAxis.NormalizeInPlace();

      // output the rotation
      result.SetRotationFromXYZAxes(xAxis,yAxis,zAxis);

      // set the scaling + the position
      result.SetSclX(values.lengthB);
      result.SetTranslation(bonePos);
   }
   else if(outportName == "OutCenter")  // center
   {
      // check if we need to rotate the bone
      bonePos.Scale(values.lengthA,xAxis);
      if(angleA != 0.0)
      {
         CRotation rot;
         rot.SetFromAxisAngle(zAxis,angleA);
         bonePos.MulByMatrix3InPlace(rot.GetMatrix());
      }
      bonePos.AddInPlace(rootPos);

      // cross the yAxis and normalize
      yAxis.Sub(upvPos,bonePos);
      zAxis.Cross(xAxis,yAxis);
      zAxis.NormalizeInPlace();

      if (values.negate)
         xAxis.NegateInPlace();

      yAxis.Cross(zAxis,xAxis);
      yAxis.NormalizeInPlace();

      // output the rotation
      result.SetRotationFromXYZAxes(xAxis,yAxis,zAxis);

      // set the scaling + the position
      result.SetSclX(stretch * values.root.GetSclX());

      result.SetTranslation(bonePos);
   }
   else if(outportName == "OutCenterN")  // center normalized
   {
      // check if we need to rotate the bone
      if(angleA != 0.0)
      {
         CRotation rot;
         rot.SetFromAxisAngle(zAxis,angleA);
         xAxis.MulByMatrix3InPlace(rot.GetMatrix());
      }

      // calculate the position of the elbow!
      bonePos.Scale(values.lengthA,xAxis);
      bonePos.AddInPlace(rootPos);

      // check if we need to rotate the bone
      if(angleB != 0.0)
      {
         if(invert)
            angleB += XSI::MATH::PI * 2;
         CRotation rot;
         rot.SetFromAxisAngle(zAxis,angleB*.5-XSI::MATH::PI*.5);
         xAxis.MulByMatrix3InPlace(rot.GetMatrix());
      }      // cross the yAxis and normalize
      // yAxis.Sub(upvPos,bonePos); // this was flipping the centerN when the elbow/upv was aligned to root/eff
      zAxis.Cross(xAxis,yAxis);
      zAxis.NormalizeInPlace();

      if (values.negate)
         xAxis.NegateInPlace();

      yAxis.Cross(zAxis,xAxis);
      yAxis.NormalizeInPlace();

      // output the rotation
      result.SetRotationFromXYZAxes(xAxis,yAxis,zAxis);

      // set the scaling + the position
      // result.SetSclX(stretch * values.root.GetSclX());

      result.SetTranslation(bonePos);
   }
   else if(outportName == "OutEff")  // effector
   {
      // check if we need to rotate the bone
      effPos = rootPos;
      if(angleA != 0.0)
      {
         CRotation rot;
         rot.SetFromAxisAngle(zAxis,angleA);
         xAxis.MulByMatrix3InPlace(rot.GetMatrix());
      }

      // calculate the position of the elbow!
      bonePos.Scale(values.lengthA,xAxis);
      effPos.AddInPlace(bonePos);

      // check if we need to rotate the bone
      if(angleB != 0.0)
      {
         CRotation rot;
         rot.SetFromAxisAngle(zAxis,angleB-XSI::MATH::PI);
         xAxis.MulByMatrix3InPlace(rot.GetMatrix());
      }

      // calculate the position of the effector!
      bonePos.Scale(values.lengthB,xAxis);
      effPos.AddInPlace(bonePos);

      // cross the yAxis and normalize
      yAxis.Cross(zAxis,xAxis);
      yAxis.NormalizeInPlace();

      // output the rotation
      result = values.eff;
      result.SetTranslation(effPos);
   }


   CRotation r = result.GetRotation();
   CVector3 eulerAngles = r.GetXYZAngles();

   double rx = eulerAngles.GetX();
   double ry = eulerAngles.GetY();
   double rz = eulerAngles.GetZ();

   return result;
}