CTransformation InterpolateTransform(CTransformation xf1, CTransformation xf2, double blend)
{
   if(blend == 1.0)
      return xf2;
   else if(blend == 0.0)
      return xf1;

   CTransformation result;
   CVector3 resultPos,resultScl;
   CQuaternion resultQuat;
   resultPos.LinearlyInterpolate(xf1.GetTranslation(),xf2.GetTranslation(),blend);
   resultScl.LinearlyInterpolate(xf1.GetScaling(),xf2.GetScaling(),blend);
   resultQuat.Slerp(xf1.GetRotationQuaternion(),xf2.GetRotationQuaternion(),blend);
   result.SetScaling(resultScl);
   result.SetRotationFromQuaternion(resultQuat);
   result.SetTranslation(resultPos);
   return result;
}