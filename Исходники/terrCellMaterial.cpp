void TerrainCellMaterial::setTransformAndEye(   const MatrixF &modelXfm, 
                                                const MatrixF &viewXfm,
                                                const MatrixF &projectXfm,
                                                F32 farPlane )
{
   PROFILE_SCOPE( TerrainCellMaterial_SetTransformAndEye );

   MatrixF modelViewProj = projectXfm * viewXfm * modelXfm;
  
   MatrixF invViewXfm( viewXfm );
   invViewXfm.inverse();
   Point3F eyePos = invViewXfm.getPosition();
   
   MatrixF invModelXfm( modelXfm );
   invModelXfm.inverse();

   Point3F objEyePos = eyePos;
   invModelXfm.mulP( objEyePos );
   
   VectorF vEye = invViewXfm.getForwardVector();
   vEye.normalize( 1.0f / farPlane );

   for ( U32 i=0; i < mPasses.size(); i++ )
   {
      Pass &pass = mPasses[i];

      pass.consts->setSafe( pass.modelViewProjConst, modelViewProj );

      if( pass.viewToObj->isValid() || pass.worldViewOnly->isValid() )
      {
         MatrixF worldViewOnly = viewXfm * modelXfm;

         pass.consts->setSafe( pass.worldViewOnly, worldViewOnly );

         if( pass.viewToObj->isValid() )
         {
            worldViewOnly.affineInverse();
            pass.consts->set( pass.viewToObj, worldViewOnly);
         } 
      }

      pass.consts->setSafe( pass.eyePosWorldConst, eyePos );
      pass.consts->setSafe( pass.eyePosConst, objEyePos );
      pass.consts->setSafe( pass.objTransConst, modelXfm );
      pass.consts->setSafe( pass.worldToObjConst, invModelXfm );
      pass.consts->setSafe( pass.vEyeConst, vEye );
   }
}