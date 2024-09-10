void PxCloth::unpackUpdate( NetConnection *conn, BitStream *stream )
{
   Parent::unpackUpdate( conn, stream );

   // TransformMask
   if ( stream->readFlag() )
   {
      MatrixF mat;
      mathRead( *stream, &mat );
      setTransform( mat );
   }

   // MaterialMask
   if ( stream->readFlag() )
   {
      stream->read( &mMaterialName );
      SAFE_DELETE( mMatInst );
   }

   // ClothMask
   if ( stream->readFlag() )
   {
      Point2I patchVerts;
      Point2F patchSize;
      mathRead( *stream, &patchVerts );
      mathRead( *stream, &patchSize );

      if (  patchVerts != mPatchVerts ||
            !patchSize.equal( mPatchSize ) )
      {
         mPatchVerts = patchVerts;
         mPatchSize = patchSize;
         _releaseMesh();
      }

      U32 attachMask;
      stream->read( &attachMask );
      if ( attachMask != mAttachmentMask )
      {
         mAttachmentMask = attachMask;
         _releaseCloth();
      }

      mBendingEnabled = stream->readFlag();
      mDampingEnabled = stream->readFlag();
      mTriangleCollisionEnabled = stream->readFlag();
      mSelfCollisionEnabled = stream->readFlag();
      stream->read( &mThickness );
      stream->read( &mFriction );
      stream->read( &mBendingStiffness );
      stream->read( &mDampingCoefficient );

      F32 density;
      stream->read( &density );
      if ( density != mDensity )
      {
         mDensity = density;
         _releaseCloth();
      }

      if (  isClientObject() && 
            isProperlyAdded() &&
            mWorld &&
            !mCloth )
      {
         _createClothPatch();
      }

      _updateClothProperties();
   }
}