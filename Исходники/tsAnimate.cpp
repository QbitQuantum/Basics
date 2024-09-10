void TSShapeInstance::addPath(TSThread *gt, F32 start, F32 end, MatrixF *mat)
{
   // never get here while in transition...
   AssertFatal(!gt->transitionData.inTransition,"TSShapeInstance::addPath");

   if (!mat)
      mat = &mGroundTransform;

   MatrixF startInvM;
   gt->getGround(start,&startInvM);
   startInvM.inverse();

   MatrixF endM;
   gt->getGround(end,&endM);

   MatrixF addM;
   addM.mul(startInvM,endM);
   endM.mul(*mat,addM);
   *mat = endM;
}