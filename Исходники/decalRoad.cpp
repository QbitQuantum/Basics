void DecalRoad::_captureVerts()
{  
   PROFILE_SCOPE( DecalRoad_captureVerts );

   //Con::warnf( "%s - captureVerts", isServerObject() ? "server" : "client" );

   if ( isServerObject() )
   {
      //Con::errorf( "DecalRoad::_captureVerts - called on the server side!" );
      return;
   }

   if ( mEdges.size() == 0 )
      return;

   //
   // Construct ClippedPolyList objects for each pair
   // of roadEdges.
   // Use them to capture Terrain verts.
   //
   SphereF sphere;
   RoadEdge *edge = NULL;
   RoadEdge *nextEdge = NULL;

   mTriangleCount = 0;
   mVertCount = 0;

   Vector<ClippedPolyList> clipperList;

   for ( U32 i = 0; i < mEdges.size() - 1; i++ )
   {      
      Box3F box;
      edge = &mEdges[i];
      nextEdge = &mEdges[i+1];

      box.minExtents = edge->p1;
      box.maxExtents = edge->p1;
      box.extend( edge->p0 );
      box.extend( edge->p2 );
      box.extend( nextEdge->p0 );
      box.extend( nextEdge->p1 );
      box.extend( nextEdge->p2 );
      box.minExtents.z -= 5.0f;
      box.maxExtents.z += 5.0f;

      sphere.center = ( nextEdge->p1 + edge->p1 ) * 0.5f;
      sphere.radius = 100.0f; // NOTE: no idea how to calculate this

      ClippedPolyList clipper;
      clipper.mNormal.set(0.0f, 0.0f, 0.0f);
      VectorF n;
      PlaneF plane0, plane1;

      // Construct Back Plane
      n = edge->p2 - edge->p0;
      n.normalize();
      n = mCross( n, edge->uvec );      
      plane0.set( edge->p0, n );   
      clipper.mPlaneList.push_back( plane0 );

      // Construct Front Plane
      n = nextEdge->p2 - nextEdge->p0;
      n.normalize();
      n = -mCross( edge->uvec, n );
      plane1.set( nextEdge->p0, -n );
      //clipper.mPlaneList.push_back( plane1 );

      // Test if / where the planes intersect.
      bool discardLeft = false;
      bool discardRight = false;
      Point3F iPos; 
      VectorF iDir;

      if ( plane0.intersect( plane1, iPos, iDir ) )
      {                  
         Point2F iPos2F( iPos.x, iPos.y );
         Point2F cPos2F( edge->p1.x, edge->p1.y );
         Point2F rVec2F( edge->rvec.x, edge->rvec.y );

         Point2F iVec2F = iPos2F - cPos2F;
         F32 iLen = iVec2F.len();
         iVec2F.normalize();

         if ( iLen < edge->width * 0.5f )
         {
            F32 dot = mDot( rVec2F, iVec2F );

            // The clipping planes intersected on the right side,
            // discard the right side clipping plane.
            if ( dot > 0.0f )
               discardRight = true;         
            // The clipping planes intersected on the left side,
            // discard the left side clipping plane.
            else
               discardLeft = true;
         }
      }

      // Left Plane
      if ( !discardLeft )
      {
         n = ( nextEdge->p0 - edge->p0 );
         n.normalize();
         n = mCross( edge->uvec, n );
         clipper.mPlaneList.push_back( PlaneF(edge->p0, n) );
      }
      else
      {
         nextEdge->p0 = edge->p0;         
      }

      // Right Plane
      if ( !discardRight )
      {
         n = ( nextEdge->p2 - edge->p2 );
         n.normalize();            
         n = -mCross( n, edge->uvec );
         clipper.mPlaneList.push_back( PlaneF(edge->p2, -n) );
      }
      else
      {
         nextEdge->p2 = edge->p2;         
      }

      n = nextEdge->p2 - nextEdge->p0;
      n.normalize();
      n = -mCross( edge->uvec, n );
      plane1.set( nextEdge->p0, -n );
      clipper.mPlaneList.push_back( plane1 );

      // We have constructed the clipping planes,
      // now grab/clip the terrain geometry
      getContainer()->buildPolyList( PLC_Decal, box, TerrainObjectType, &clipper );         
      clipper.cullUnusedVerts();
      clipper.triangulate();
      clipper.generateNormals();

      // If we got something, add it to the ClippedPolyList Vector
      if ( !clipper.isEmpty() && !( smDiscardAll && ( discardRight || discardLeft ) ) )
      {
         clipperList.push_back( clipper );       
      
         mVertCount += clipper.mVertexList.size();
         mTriangleCount += clipper.mPolyList.size();
      }
   }

   //
   // Set the roadEdge height to be flush with terrain
   // This is not really necessary but makes the debug spline rendering better.
   //
   for ( U32 i = 0; i < mEdges.size() - 1; i++ )
   {            
      edge = &mEdges[i];      
      
      _getTerrainHeight( edge->p0.x, edge->p0.y, edge->p0.z );

      _getTerrainHeight( edge->p2.x, edge->p2.y, edge->p2.z );
   }

   //
   // Allocate the RoadBatch(s)   
   //

   // If we captured no verts, then we can return here without
   // allocating any RoadBatches or the Vert/Index Buffers.
   // PreprenderImage will not allocate a render instance while
   // mBatches.size() is zero.
   U32 numClippers = clipperList.size();
   if ( numClippers == 0 )
      return;

   mBatches.clear();

   // Allocate the VertexBuffer and PrimitiveBuffer
   mVB.set( GFX, mVertCount, GFXBufferTypeStatic );
   mPB.set( GFX, mTriangleCount * 3, 0, GFXBufferTypeStatic );

   // Lock the VertexBuffer
   GFXVertexPNTBT *vertPtr = mVB.lock();
   if(!vertPtr) return;
   U32 vertIdx = 0;

   //
   // Fill the VertexBuffer and vertex data for the RoadBatches
   // Loop through the ClippedPolyList Vector   
   //
   RoadBatch *batch = NULL;
   F32 texStart = 0.0f;
   F32 texEnd;
   
   for ( U32 i = 0; i < clipperList.size(); i++ )
   {   
      ClippedPolyList *clipper = &clipperList[i];
      RoadEdge &edge = mEdges[i];
      RoadEdge &nextEdge = mEdges[i+1];      

      VectorF segFvec = nextEdge.p1 - edge.p1;
      F32 segLen = segFvec.len();
      segFvec.normalize();

      F32 texLen = segLen / mTextureLength;
      texEnd = texStart + texLen;

      BiQuadToSqr quadToSquare(  Point2F( edge.p0.x, edge.p0.y ), 
                                 Point2F( edge.p2.x, edge.p2.y ), 
                                 Point2F( nextEdge.p2.x, nextEdge.p2.y ), 
                                 Point2F( nextEdge.p0.x, nextEdge.p0.y ) );  

      //
      if ( i % mSegmentsPerBatch == 0 )
      {
         mBatches.increment();
         batch = &mBatches.last();

         batch->bounds.minExtents = clipper->mVertexList[0].point;
         batch->bounds.maxExtents = clipper->mVertexList[0].point;
         batch->startVert = vertIdx;
      }

      // Loop through each ClippedPolyList        
      for ( U32 j = 0; j < clipper->mVertexList.size(); j++ )
      {
         // Add each vert to the VertexBuffer
         Point3F pos = clipper->mVertexList[j].point;
         vertPtr[vertIdx].point = pos;
         vertPtr[vertIdx].normal = clipper->mNormalList[j];                     
                  
         Point2F uv = quadToSquare.transform( Point2F(pos.x,pos.y) );
         vertPtr[vertIdx].texCoord.x = uv.x;
         vertPtr[vertIdx].texCoord.y = -(( texEnd - texStart ) * uv.y + texStart);   

         vertPtr[vertIdx].tangent = mCross( segFvec, clipper->mNormalList[j] );
         vertPtr[vertIdx].binormal = segFvec;

         vertIdx++;

         // Expand the RoadBatch bounds to contain this vertex   
         batch->bounds.extend( pos );
      }    

      batch->endVert = vertIdx - 1;

      texStart = texEnd;
   }   

   // Unlock the VertexBuffer, we are done filling it.
   mVB.unlock();

   // Lock the PrimitiveBuffer
   U16 *idxBuff;
   mPB.lock(&idxBuff);     
   U32 curIdx = 0;
   U16 vertOffset = 0;   
   batch = NULL;
   S32 batchIdx = -1;

   // Fill the PrimitiveBuffer   
   // Loop through each ClippedPolyList in the Vector
   for ( U32 i = 0; i < clipperList.size(); i++ )
   {      
      ClippedPolyList *clipper = &clipperList[i];

      if ( i % mSegmentsPerBatch == 0 )
      {
         batchIdx++;
         batch = &mBatches[batchIdx];
         batch->startIndex = curIdx;         
      }        

      for ( U32 j = 0; j < clipper->mPolyList.size(); j++ )
      {
         // Write indices for each Poly
         ClippedPolyList::Poly *poly = &clipper->mPolyList[j];                  

         AssertFatal( poly->vertexCount == 3, "Got non-triangle poly!" );

         idxBuff[curIdx] = clipper->mIndexList[poly->vertexStart] + vertOffset;         
         curIdx++;
         idxBuff[curIdx] = clipper->mIndexList[poly->vertexStart + 1] + vertOffset;            
         curIdx++;
         idxBuff[curIdx] = clipper->mIndexList[poly->vertexStart + 2] + vertOffset;                
         curIdx++;
      } 

      batch->endIndex = curIdx - 1;

      vertOffset += clipper->mVertexList.size();
   }

   // Unlock the PrimitiveBuffer, we are done filling it.
   mPB.unlock();

   // Generate the object/world bounds
   // Is the union of all batch bounding boxes.

   Box3F box;
   for ( U32 i = 0; i < mBatches.size(); i++ )
   {
      const RoadBatch &batch = mBatches[i];

      if ( i == 0 )      
         box = batch.bounds;               
      else      
         box.intersect( batch.bounds );               
   }

   Point3F pos = getPosition();

   mWorldBox = box;
   resetObjectBox();

   // Make sure we are in the correct bins given our world box.
   if( getSceneManager() != NULL )
      getSceneManager()->notifyObjectDirty( this );
}