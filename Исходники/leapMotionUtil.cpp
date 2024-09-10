void calculateHandAxisRotation(const MatrixF& handRotation, const F32& maxHandAxisRadius, Point2F& outRotation)
{
   const VectorF& controllerUp = handRotation.getUpVector();
   outRotation.x = controllerUp.x;
   outRotation.y = controllerUp.y;

   // Limit the axis angle to that given to us
   if(outRotation.len() > maxHandAxisRadius)
   {
      outRotation.normalize(maxHandAxisRadius);
   }

   // Renormalize to the range of 0..1
   if(maxHandAxisRadius != 0.0f)
   {
      outRotation /= maxHandAxisRadius;
   }
}