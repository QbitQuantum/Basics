Matrix4x4f BoneBridgeCAL3D::CalculateBoneSpaceTransform() const
{
   Matrix4x4f boneSpaceTransform = Matrix4x4f::Identity();

   // set up bone space geometry transform
   {
      // transform forward by half the box length
      const Vec3f& dimensions = GetDimensions();
      boneSpaceTransform.SetTranslation(Vec3f(dimensions[Y] / 2.0f, 0.0f, 0.0f));

      // set rotational offset (the inversion of the core bone absolute rotation)
      {
         CalCoreBone* coreBone = mpCalBone->getCoreBone();

         CalQuaternion calRotAbsolute = coreBone->getRotationAbsolute();
         calRotAbsolute.invert();

         Quaternionf kernelRot = ConvertCAL3DtoKernel(calRotAbsolute);

         boneSpaceTransform.SetRotate(kernelRot);
      }
   }

   return boneSpaceTransform;
}