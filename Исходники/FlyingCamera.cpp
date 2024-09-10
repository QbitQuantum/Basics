bool FlyingCamera::onSimCameraQuery(SimCameraQuery *query)
{
   SimObjectTransformQuery tquery;

   query->cameraInfo.fov       = g_rDefaultFOV;
   query->cameraInfo.nearPlane = DEFAULT_NEAR_PLANE;
   query->cameraInfo.farPlane  = getFarPlane();

   if (objFollow && objFollow->processQuery(&tquery))
   {
      Point3F  objPos = tquery.tmat.p;
      Vector3F x, y, z;
      RMat3F   rmat(EulerF(rotation.x - M_PI / 2, rotation.y, -rotation.z));

      tquery.tmat.p   += m_mul(Vector3F(0.0f, rDistance, 0.0f), rmat, &y);
      tquery.tmat.p.z += 2.0f;

      y.neg();
      y.normalize();
      m_cross(y, Vector3F(0.0f, 0.0f, 1.0f), &x);
      x.normalize();
      m_cross(x, y, &z);

      tquery.tmat.setRow(0, x);
      tquery.tmat.setRow(1, y);
      tquery.tmat.setRow(2, z);

      // Set our position
      findLOSPosition(tquery.tmat, objPos);
   }

   query->cameraInfo.tmat = getTransform();
   return (true);
}