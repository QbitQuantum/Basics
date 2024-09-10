void CloudLayer::_initBuffers()
{      
   // Vertex Buffer...

   Point3F vertScale( 16.0f, 16.0f, mHeight );
   F32 zOffset = -( mCos( mSqrt( 1.0f ) ) + 0.01f );
   
   mVB.set( GFX, smVertCount, GFXBufferTypeStatic );   
   GFXCloudVertex *pVert = mVB.lock(); 
   if(!pVert) return;

   for ( U32 y = 0; y < smVertStride; y++ )
   {
      F32 v = ( (F32)y / (F32)smStrideMinusOne - 0.5f ) * 2.0f;

      for ( U32 x = 0; x < smVertStride; x++ )
      {
         F32 u = ( (F32)x / (F32)smStrideMinusOne - 0.5f ) * 2.0f;

         F32 sx = u;
         F32 sy = v;
         F32 sz = mCos( mSqrt( sx*sx + sy*sy ) ) + zOffset;
         //F32 sz = 1.0f;
         pVert->point.set( sx, sy, sz );
         pVert->point *= vertScale;

         // The vert to our right.
         Point3F rpnt;

         F32 ru = ( (F32)( x + 1 ) / (F32)smStrideMinusOne - 0.5f ) * 2.0f;
         F32 rv = v;

         rpnt.x = ru;
         rpnt.y = rv;
         rpnt.z = mCos( mSqrt( rpnt.x*rpnt.x + rpnt.y*rpnt.y ) ) + zOffset;
         rpnt *= vertScale;

         // The vert to our front.
         Point3F fpnt;

         F32 fu = u;
         F32 fv = ( (F32)( y + 1 ) / (F32)smStrideMinusOne - 0.5f ) * 2.0f;

         fpnt.x = fu;
         fpnt.y = fv;
         fpnt.z = mCos( mSqrt( fpnt.x*fpnt.x + fpnt.y*fpnt.y ) ) + zOffset;
         fpnt *= vertScale;

         Point3F fvec = fpnt - pVert->point;
         fvec.normalize();

         Point3F rvec = rpnt - pVert->point;
         rvec.normalize();

         pVert->normal = mCross( fvec, rvec );
         pVert->normal.normalize();
         pVert->binormal = fvec;
         pVert->tangent = rvec;
         pVert->texCoord.set( u, v );   
         pVert++;
      }
   }

   mVB.unlock();


   // Primitive Buffer...   

   mPB.set( GFX, smTriangleCount * 3, smTriangleCount, GFXBufferTypeStatic );

   U16 *pIdx = NULL;   
   mPB.lock(&pIdx);     
   U32 curIdx = 0; 

   for ( U32 y = 0; y < smStrideMinusOne; y++ )
   {
      for ( U32 x = 0; x < smStrideMinusOne; x++ )
      {
         U32 offset = x + y * smVertStride;

         pIdx[curIdx] = offset;
         curIdx++;
         pIdx[curIdx] = offset + 1;
         curIdx++;
         pIdx[curIdx] = offset + smVertStride + 1;
         curIdx++;

         pIdx[curIdx] = offset;
         curIdx++;
         pIdx[curIdx] = offset + smVertStride + 1;
         curIdx++;
         pIdx[curIdx] = offset + smVertStride;
         curIdx++;
      }
   }

   mPB.unlock();   
}