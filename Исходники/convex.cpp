bool Convex::getCollisionInfo(const MatrixF& mat, const Point3F& scale, CollisionList* cList,F32 tol)
{
   PROFILE_SCOPE( Convex_GetCollisionInfo );

   // Making these static prevents needless Vector resizing that occurs
   // in the ConvexFeature constructor.
   static ConvexFeature fa;
   static ConvexFeature fb;

   for ( CollisionStateList* itr = mList.mNext; 
         itr != &mList; 
         itr = itr->mNext) 
   {

      CollisionState* state = itr->mState;

      if (state->mLista != itr)
         state->swap();

      if (state->dist <= tol) 
      {
         fa.reset();
         fb.reset();
         VectorF v;

         // The idea is that we need to scale the matrix, so we need to
         // make a copy of it, before we can pass it in to getFeatures.
         // This is used to scale us for comparison against the other
         // convex, which is correctly scaled.
         MatrixF omat = mat;
         omat.scale(scale);

         MatrixF imat = omat;
         imat.inverse();
         imat.mulV(-state->v,&v);

         getFeatures(omat,v,&fa);

         imat = state->b->getTransform();
         imat.scale(state->b->getScale());

         MatrixF bxform = imat;
         imat.inverse();
         imat.mulV(state->v,&v);

         state->b->getFeatures(bxform,v,&fb);

         fa.collide(fb,cList,tol);
      }
   }

   return (cList->getCount() != 0);
}