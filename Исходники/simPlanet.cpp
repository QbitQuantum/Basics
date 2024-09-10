void PlanetRenderImage::render(TSRenderContext &rc)
{
   // A simple planet culling scheme would be to dot the line of sight
   // with the vector from the camera to the planet.  This would eliminate
   // the length test of v below (after m_cross((Point3F)plane, vpNormal, &v))
   GFXSurface *gfxSurface = rc.getSurface();

   gfxSurface->setHazeSource(GFX_HAZE_NONE);
   gfxSurface->setShadeSource(GFX_SHADE_CONSTANT);
   gfxSurface->setAlphaSource(GFX_ALPHA_NONE);
	gfxSurface->setFillMode(GFX_FILL_TEXTURE);
	gfxSurface->setTransparency(FALSE);
   gfxSurface->setTexturePerspective(FALSE);

   gfxSurface->setConstantShade(1.0f);

   int textureHeight;
   gfxSurface->setTextureMap(texture);
   textureHeight = texture->height;
   
   TSCamera *camera = rc.getCamera();
  
   TS::PointArray *pointArray = rc.getPointArray();
   pointArray->reset();
   pointArray->useIntensities(false);
   pointArray->useTextures(textCoord);
   pointArray->useTextures(true);
	pointArray->setVisibility( TS::ClipMask );

   // find out how high the bitmap is at 100% as projected onto the viewport,
   // texel:pixel will be 1:1 at 640x480
   //const RectF &worldVP  = camera->getWorldViewport();
   //const float h = textureHeight*((worldVP.upperL.y - worldVP.lowerR.y)/480.0f);
   //const float sz = 0.5*distance*(h/camera->getNearDist());

   // find the position of the planet
   Point3F displacement = camera->getTCW().p;
   //displacement.z *= -(distance - visibleDistance)/visibleDistance;
   displacement.z = -displacement.z*(distance/(visibleDistance*1.5f));
   Point3F pos = position;
   pos += displacement;
 
   // find the normal to the view plane in world coords
   Point3F v0(0.0f, 1.0f, 0.0f), vpNormal;
   m_mul(v0, (RMat3F)camera->getTCW(), &vpNormal);
   vpNormal.normalize();

   // construct the plane that the camera, planet pos & celestial NP all
   // lie on
   PlaneF plane(pos, camera->getTCW().p, 
      Point3F(displacement.x, displacement.y, displacement.z + distance));

   // the cross product of the VP normal and the normal to the plane just
   // constructed is the up vector for the planet
   Point3F v;
   m_cross((Point3F)plane, vpNormal, &v);
   if (IsEqual(v.len(), 0.0f))
      // planet is directly to the right or left of camera
      return;
   v.normalize();
   
   // cross the up with the normal and we get the right vector
   Point3F u;
   m_cross(vpNormal, v, &u);
   u *= size;
   v *= size;

   TS::VertexIndexPair V[6];
   Point3F ul = pos;
   ul -= u; ul += v;
   V[0].fVertexIndex   = pointArray->addPoint(ul);
   V[0].fTextureIndex  = 0;
   Point3F ur = pos;
   ur += u; ur += v;
   V[1].fVertexIndex   = pointArray->addPoint(ur);
   V[1].fTextureIndex  = 1;
   Point3F lr = pos;
   lr += u; lr -= v;
   V[2].fVertexIndex   = pointArray->addPoint(lr);
   V[2].fTextureIndex  = 2;
   Point3F ll = pos;
   ll -= u; ll -=v;
   V[3].fVertexIndex   = pointArray->addPoint(ll);
   V[3].fTextureIndex  = 3;
	if (gfxSurface->getCaps() & GFX_DEVCAP_SUPPORTS_CONST_ALPHA)
	   gfxSurface->setZTest(GFX_NO_ZTEST);
   pointArray->drawPoly(4, V, 0);
	if (gfxSurface->getCaps() & GFX_DEVCAP_SUPPORTS_CONST_ALPHA)
	   gfxSurface->setZTest(GFX_ZTEST_AND_WRITE);
   if(lensFlare) {
      TS::TransformedVertex vx;
      camera->transformProject(pos, &vx);
      bool vis = vx.fStatus & TS::TransformedVertex::Projected;
      lensFlare->setSunPos(vis, vx.fPoint, pos);
   }
}