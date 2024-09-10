/*------------------------------------
  destructor of classic shadow object
  C.Wang 0522, 2006
 -------------------------------------*/
FuCShadowModify::~FuCShadowModify()
{
   // delete the associated camera
   FnScene scene;
   FnWorld gw;
   scene.Object(mHost);
   gw.Object(scene.GetWorld());

   gw.DeleteViewport(mViewport);
   mViewport = FAILED_ID;

   gw.DeleteMaterial(mShadowMat);
   mShadowMat = FAILED_MATERIAL_ID;

   gw.DeleteMaterial(mRenderTarget);
   mRenderTarget = FAILED_MATERIAL_ID;

   scene.DeleteCamera( m_lightCam.Object() );
   m_lightCam.Object( FAILED_ID );

   scene.DeleteObject(mSeed);
   mSeed = FAILED_ID;

}