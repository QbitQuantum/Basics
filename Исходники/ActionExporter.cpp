Matrix3 CActionExporter::get_bone_tm(CSkeletonExporter* pSkeleton,int boneIndex,unsigned int iMaxTime)
{
         sMaxBoneNode_t bone = pSkeleton->m_MaxBones[boneIndex];
         Matrix3        boneInitMTInv;
         if(G_MaxEnv().m_bUseBeforeSkeletonPose)
             boneInitMTInv = bone.m_SkinInitMT;
         else
             boneInitMTInv = bone.m_InitNodeTM0;

         boneInitMTInv.Invert();
         INode* pNode = bone.m_pNode;

         Matrix3 BoneTM = boneInitMTInv * pNode->GetNodeTM(iMaxTime); //>GetNodeTM(iMaxTime);
         Point3 Trans = BoneTM.GetTrans();
         BoneTM.NoTrans();
         //对骨骼进行缩放
         Trans.x *= pSkeleton->m_fScale;
         Trans.y *= pSkeleton->m_fScale;
         Trans.z *= pSkeleton->m_fScale;
         BoneTM.SetTrans(Trans);

         return BoneTM;

}