static void calcPeCorrection(float *correctionFac,
                             const float peAct,
                             const float peLast, 
                             const int bitsLast) 
{
  COUNT_sub_start("calcPeCorrection");

  ADD(4); FUNC(1); FUNC(1); MULT(4); LOGIC(4); BRANCH(1);
  if ((bitsLast > 0) && (peAct < (float)1.5f*peLast) && (peAct > (float)0.7f*peLast) &&
      ((float)1.2f*bits2pe((float)bitsLast) > peLast) && 
      ((float)0.65f*bits2pe((float)bitsLast) < peLast))
  {
    float newFac = peLast / bits2pe((float)bitsLast);

    FUNC(1); DIV(1); /* counting previous operation */

    /* dead zone */
    ADD(1); BRANCH(1);
    if (newFac < (float)1.0f) {

      MULT(1); ADD(1); BRANCH(1); MOVE(1);
      newFac = min((float)1.1f*newFac, (float)1.0f);

      ADD(1); BRANCH(1); MOVE(1);
      newFac = max(newFac, (float)0.85f);
    }
    else {
      MULT(1); ADD(1); BRANCH(1); MOVE(1);
      newFac = max((float)0.9f*newFac, (float)1.0f);

      ADD(1); BRANCH(1); MOVE(1);
      newFac = min(newFac, (float)1.15f);
    }
    ADD(4); LOGIC(3); BRANCH(1);
    if (((newFac > (float)1.0f) && (*correctionFac < (float)1.0f)) ||
        ((newFac < (float)1.0f) && (*correctionFac > (float)1.0f))) {

      MOVE(1);
      *correctionFac = (float)1.0f;
    }

    /* faster adaptation towards 1.0, slower in the other direction */
    ADD(3); LOGIC(3); BRANCH(1); /* if() */ MULT(1); MAC(1); STORE(1);
    if ((*correctionFac < (float)1.0f && newFac < *correctionFac) ||
        (*correctionFac > (float)1.0f && newFac > *correctionFac))
      *correctionFac = (float)0.85f * (*correctionFac) + (float)0.15f * newFac;
    else
      *correctionFac = (float)0.7f * (*correctionFac) + (float)0.3f * newFac;

    ADD(2); BRANCH(2); MOVE(2);
    *correctionFac = min(*correctionFac, (float)1.15f);
    *correctionFac = max(*correctionFac, (float)0.85f);
  }
  else {
    MOVE(1);
    *correctionFac = (float)1.0f;
  }

  COUNT_sub_end();
}