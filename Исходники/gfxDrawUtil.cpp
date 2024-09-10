void GFXDrawUtil::drawCylinder( const GFXStateBlockDesc &desc, const Point3F &basePnt, const Point3F &tipPnt, F32 radius, const ColorI &color )
{
   VectorF uvec = tipPnt - basePnt;
   F32 height = uvec.len();
   uvec.normalize();
   MatrixF mat( true );
   MathUtils::getMatrixFromUpVector( uvec, &mat );   
   mat.setPosition(basePnt);

   Point3F scale( radius, radius, height * 2 );
   mat.scale(scale);
   GFXTransformSaver saver;

   mDevice->pushWorldMatrix();
   mDevice->multWorld(mat);

   S32 numPoints = sizeof(circlePoints)/sizeof(Point2F);
   GFXVertexBufferHandle<GFXVertexPC> verts(mDevice, numPoints * 4 + 4, GFXBufferTypeVolatile);
   verts.lock();
   for (S32 i=0; i<numPoints + 1; i++)
   {
      S32 imod = i % numPoints;
      verts[i].point = Point3F(circlePoints[imod].x,circlePoints[imod].y, 0.5f);
      verts[i].color = color;
      verts[i + numPoints + 1].point = Point3F(circlePoints[imod].x,circlePoints[imod].y, 0);
      verts[i + numPoints + 1].color = color;

      verts[2*numPoints + 2 + 2 * i].point = Point3F(circlePoints[imod].x,circlePoints[imod].y, 0.5f);
      verts[2*numPoints + 2 + 2 * i].color = color;
      verts[2*numPoints + 2 + 2 * i + 1].point = Point3F(circlePoints[imod].x,circlePoints[imod].y, 0);
      verts[2*numPoints + 2 + 2 * i + 1].color = color;
   }
   verts.unlock();

   mDevice->setStateBlockByDesc( desc );

   mDevice->setVertexBuffer( verts );
   mDevice->setupGenericShaders( GFXDevice::GSModColorTexture );

   mDevice->drawPrimitive( GFXTriangleFan, 0, numPoints );
   mDevice->drawPrimitive( GFXTriangleFan, numPoints + 1, numPoints );
   mDevice->drawPrimitive( GFXTriangleStrip, 2 * numPoints + 2, 2 * numPoints);

   mDevice->popWorldMatrix();
}