 //---------------------------------------------------------------------
 void SkeletonSerializer::writeSkeleton(const Skeleton* pSkel)
 {
     // Write each bone
     unsigned short numBones = pSkel->getNumBones();
     unsigned short i;
     for (i = 0; i < numBones; ++i)
     {
         Bone* pBone = pSkel->getBone(i);
         writeBone(pSkel, pBone);
     }
     // Write parents
     for (i = 0; i < numBones; ++i)
     {
         Bone* pBone = pSkel->getBone(i);
         unsigned short handle = pBone->getHandle();
         Bone* pParent = (Bone*)pBone->getParent(); 
         if (pParent != NULL) 
         {
             writeBoneParent(pSkel, handle, pParent->getHandle());             
         }
     }
 }