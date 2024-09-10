 //-----------------------------------------------------------------------
 Quaternion Quaternion::Squad (Real fT,
     const Quaternion& rkP, const Quaternion& rkA,
     const Quaternion& rkB, const Quaternion& rkQ, bool shortestPath)
 {
     Real fSlerpT = 2.0f*fT*(1.0f-fT);
     Quaternion kSlerpP = Slerp(fT, rkP, rkQ, shortestPath);
     Quaternion kSlerpQ = Slerp(fT, rkA, rkB);
     return Slerp(fSlerpT, kSlerpP ,kSlerpQ);
 }