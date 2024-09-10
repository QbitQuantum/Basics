SceneCameraState SceneCameraState::fromGFXWithViewport( const RectI& viewport )
{
   const MatrixF& world = GFX->getWorldMatrix();
   
   MatrixF camera = world;
   camera.inverse();

   Frustum frustum = GFX->getFrustum();
   frustum.setTransform( camera );

   return SceneCameraState(
      viewport,
      frustum,
      world,
      GFX->getProjectionMatrix()
   );
}