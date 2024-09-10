void PlaneReflector::setGFXMatrices( const MatrixF &camTrans )
{
   if ( objectSpace )
   {
      // set up camera transform relative to object
      MatrixF invObjTrans = mObject->getRenderTransform();
      invObjTrans.inverse();
      MatrixF relCamTrans = invObjTrans * camTrans;

      MatrixF camReflectTrans = getCameraReflection( relCamTrans );
      MatrixF camTrans = mObject->getRenderTransform() * camReflectTrans;
      camTrans.inverse();

      GFX->setWorldMatrix( camTrans );

      // use relative reflect transform for modelview since clip plane is in object space
      camTrans = camReflectTrans;
      camTrans.inverse();

      // set new projection matrix
      gClientSceneGraph->setNonClipProjection( (MatrixF&) GFX->getProjectionMatrix() );
      MatrixF clipProj = getFrustumClipProj( camTrans );
      GFX->setProjectionMatrix( clipProj );
   }    
   else
   {
      // set world mat from new camera view
      MatrixF camReflectTrans = getCameraReflection( camTrans );
      camReflectTrans.inverse();
      GFX->setWorldMatrix( camReflectTrans );

      // set new projection matrix
      gClientSceneGraph->setNonClipProjection( (MatrixF&) GFX->getProjectionMatrix() );
      MatrixF clipProj = getFrustumClipProj( camReflectTrans );
      GFX->setProjectionMatrix( clipProj );
   }   
}